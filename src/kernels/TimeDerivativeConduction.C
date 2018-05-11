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


#include "TimeDerivativeConduction.h"

#include "Material.h"

template<>
InputParameters validParams<TimeDerivativeConduction>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<Real>("time_coeff", 1.0, "Time Coefficient");
  return params;
}

TimeDerivativeConduction::TimeDerivativeConduction(const InputParameters & parameters) :
    TimeDerivative(parameters),
    _time_coeff(getParam<Real>("time_coeff")),
    _zr_mass_density(getMaterialProperty<Real>("zr_mass_density")),
    _zr_specific_heat(getMaterialProperty<Real>("zr_specific_heat"))
{}

Real
TimeDerivativeConduction::computeQpResidual()
{
  return _time_coeff*_zr_mass_density[_qp]*_zr_specific_heat[_qp]*TimeDerivative::computeQpResidual();
}

Real
TimeDerivativeConduction::computeQpJacobian()
{
  return _time_coeff*_zr_mass_density[_qp]*_zr_specific_heat[_qp]*TimeDerivative::computeQpJacobian();
}
