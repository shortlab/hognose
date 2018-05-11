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


#include "PFPhase.h"

template<>
InputParameters validParams<PFPhase>()
{
     InputParameters params = validParams<AuxKernel>();
     params.addRequiredCoupledVar("value", "The phase field non-conserved order parameter.");
     params.addRequiredParam<Real>("minimum", "The lower bound of a given phase variable.");
     params.addRequiredParam<Real>("maximum", "The upper bound of a given phase variable.");
     return params;
}

PFPhase::PFPhase(const InputParameters & parameters)
  :AuxKernel(parameters),
   _value(coupledValue("value")),
   _min(getParam<Real>("minimum")),
   _max(getParam<Real>("maximum"))

{}

Real
PFPhase::computeValue()
{
  double phase=0.0;

  if ((_value[_qp] > _min) && (_value[_qp] < _max))
  {
	phase = 1.0;
  }

  return phase;
 
}
