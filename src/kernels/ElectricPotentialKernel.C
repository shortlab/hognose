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


#include "ElectricPotentialKernel.h"

template<>
InputParameters validParams<ElectricPotentialKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("charge_density","The variable providing the charge density.");
  params.addParam<Real>("dielectric_constant",1.0,"The value of the dielectric constant");
  return params;
}

ElectricPotentialKernel::ElectricPotentialKernel(const InputParameters & parameters) :
    Kernel(parameters),
    _charge_density(coupledValue("charge_density")),
    _h_value(getMaterialProperty<Real>("h_value")),
    _dielectric_constant(getParam<Real>("dielectric_constant"))

{}

ElectricPotentialKernel::~ElectricPotentialKernel()
{}

Real
ElectricPotentialKernel::computeQpResidual()
{
  Real dielectric_constant = _dielectric_constant * 8.854187817620e-12;

  Real charge = 1.602e-19; // C

  return _test[_i][_qp] * _charge_density[_qp] * _h_value[_qp] * charge / dielectric_constant;
}
