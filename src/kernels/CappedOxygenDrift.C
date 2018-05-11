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


#include "CappedOxygenDrift.h"


template<>
InputParameters validParams<CappedOxygenDrift>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential","The variable providing the electric potential.");
  params.addParam<Real>("drift_conc",0.01,"The concentration of oxygen the is available to drift.");
  return params;
}

CappedOxygenDrift::CappedOxygenDrift(const InputParameters & parameters) :
    Kernel(parameters),
    _grad_potential(coupledGradient("potential")),
    _v_var(coupled("potential")),
    _total_diffusivity_factor(getMaterialProperty<Real>("total_diffusivity_factor")),
    _h_value(getMaterialProperty<Real>("h_value")),
    _o_ion_mobility(getMaterialProperty<Real>("o_ion_mobility")),
    _drift_conc(getParam<Real>("drift_conc"))

{}

Real
CappedOxygenDrift::computeQpResidual()
{
  Real drift_conc = _h_value[_qp] * _drift_conc;

  return - (_o_ion_mobility[_qp] / _total_diffusivity_factor[_qp]) * drift_conc * _grad_potential[_qp] * _grad_test[_i][_qp];
}

Real
CappedOxygenDrift::computeQpJacobian()
{
  Real drift_conc = _h_value[_qp] * _drift_conc;

  return - (_o_ion_mobility[_qp] / _total_diffusivity_factor[_qp]) * _phi[_i][_qp] * _grad_potential[_qp] * _grad_test[_i][_qp];
}

Real
CappedOxygenDrift::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
  {
	Real drift_conc = _h_value[_qp] * _drift_conc;

	return - (_o_ion_mobility[_qp] / _total_diffusivity_factor[_qp]) * drift_conc * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
  }
  return 0.0;
}
