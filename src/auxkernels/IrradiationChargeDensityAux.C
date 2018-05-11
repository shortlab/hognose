/*******************************************************************/
/*                    DO NOT MODIFY THIS HEADER                    */
/*                                                                 */
/*                             HOGNOSE                             */
/*            High-speed Oxide Growth in a Numerically             */
/*                Optimized Simulation Environment                 */
/*                                                                 */
/*         (c) 2017 Massachusetts Institute of Technology          */
/*                      ALL RIGHTS RESERVED                        */
/*                                                                 */
/*                                                                 */
/*  Prepared by Andrew Dykhuis and Michael P. Short as a part of   */
/*  the United States Department of Energy's Consortium for the    */
/*  Advanced Simulation of Light-Water Reactors (CASL).            */
/*            					                   */
/*******************************************************************/


#include "IrradiationChargeDensityAux.h"

template<>
InputParameters validParams<IrradiationChargeDensityAux>()
{
     InputParameters params = validParams<AuxKernel>();
     params.addParam<Real>("charge_constant",0.0,"The constant charge value in cubic microns.");
     params.addRequiredCoupledVar("old_phase","Provides the old value of the phase.");
     params.addRequiredCoupledVar("phase","Provides the value of the phase.");
     params.addParam<Real>("time_to_full_rho",0.0,"The time at which the charge is fully present. "
			          "A linear ramp occurs from 0 to charge_constant if "
			          "t<time_to_full_rho.");
     params.addParam<FunctionName>("rho_function", "0", "Function for the rho multiplier as a "
			          "function of time.");
     params.addParam<Real>("use_PP",0,"Turn on coupling to the PP provided value.");
     params.addParam<PostprocessorName>("charge_constant_PP",100,"The charge constant postprocessor.");
     params.addParam<PostprocessorName>("transition_count", 0.0, "The transition count postprocessor.");

     params.addParam<FunctionName>("n_flux", "0", "Function for the neutron flux.");
     params.addParam<PostprocessorName>("fluence_offset",0,"Postprocessor for fluence offset.");
     params.addParam<PostprocessorName>("n_flux_time_offset",0,"Postprocessor providing the time "
				     "to use with the neutron flux function.");
     params.addParam<Real>("rho_Fe_value",47444071,"Number of iron atoms that can be released to the matrix.");
     params.addParam<Real>("small_SPP",0,"Choice of small SPPs or typical Zircaloy-4 SPPs.");
     params.addParam<Real>("delayed_Fe",0,"Choice of delayed Fe release or other options.");

     return params;
}

IrradiationChargeDensityAux::IrradiationChargeDensityAux(const InputParameters & parameters)
  :AuxKernel(parameters),
   _charge_constant(getParam<Real>("charge_constant")),
   _h_value(getMaterialProperty<Real>("h_value")),
   _net_iron_change(getMaterialProperty<Real>("net_iron_change")),
   _old_phase(coupledValueOld("old_phase")),
   _phase(coupledValueOld("phase")),
   _time_to_full_rho(getParam<Real>("time_to_full_rho")),
   _rho_function(getFunction("rho_function")),
   _use_PP(getParam<Real>("use_PP")),
   _charge_constant_PP(getPostprocessorValue("charge_constant_PP")),
   _transition_count(getPostprocessorValue("transition_count")),
   _n_flux(getFunction("n_flux")),
   _fluence(getMaterialProperty<Real>("fluence")),
   _fluence_offset(getPostprocessorValue("fluence_offset")),
   _time_offset(getPostprocessorValue("n_flux_time_offset")),
   _rho_Fe_value(getParam<Real>("rho_Fe_value")),
   _small_SPP(getParam<Real>("small_SPP")),
   _delayed_Fe(getParam<Real>("delayed_Fe"))

{}

Real
IrradiationChargeDensityAux::computeValue()
{



 Real value;

 Real flux = _n_flux.value(_t + _time_offset, _q_point[_qp]);

 Real delta_rho = value;
 
 // Couple to the AmorphousWidthMaterial to determine the value of delta_rho:
 delta_rho = _net_iron_change[_qp] * _charge_constant;
  
  if (_old_phase[_qp] < 0.05) // Reduce rho proportional to the iron released
  {
	// if it's after the first transition and on the first time step, use
	// the PP value to initialize it and subtract delta_rho, otherwise
	// use the old value and subtract delta_rho
	if ((_transition_count < 1) && (_t_step < 2))
	{
		value = _charge_constant - delta_rho;
	}
	else if ((_transition_count > 0) && (_t_step < 2)) 
	{
		value = _charge_constant_PP - delta_rho;
	}
	else
	{
		value = _u_old[_qp] - delta_rho; 
	}
  }
  else // If the _qp was in the oxide before, rho shouldn't change
  {
	if ((_transition_count > 0) && (_t_step < 2)) // after transition on the first step, use the PP value
        {
		value = _charge_constant_PP;
        }
	else if ((_transition_count < 1) && (_t_step < 2))
        {
		value = _charge_constant;
        }
	else
	{
		value = _u_old[_qp]; 
	}
  }	

  if ((_transition_count > 0) && (_t_step < 3)) // after transition on the first step, use the PP value
  {
	value = _charge_constant_PP;
  }
  
  // Avoid negative values:
  if (value < 0.)
  {
	value = 0.;
  }

  Real factor = 1.0;

  if (isNodal())
    factor = _rho_function.value(_t, *_current_node);
  else
    factor = _rho_function.value(_t, _q_point[_qp]);

  value = value * factor; // ramp up the charge at the beginning of the simulation.

  return value;
 
}
