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


#include "ElectrostaticFreeEnergy.h"

template<>
InputParameters validParams<ElectrostaticFreeEnergy>()
{
  InputParameters params = validParams<DerivativeFunctionMaterialBase>();
  params.addParam<Real>("relative_permittivity",15,"Relative permittivity of the oxide.");
  params.addParam<Real>("metal_permittivity",1e-6,"Relative permittivity of the metal.");
  params.addRequiredCoupledVar("potential","The variable providing the electrostatic potential.");
  params.addClassDescription("Material that implements the addition of electrostatic energy density to the free energy calculation.");
  params.addRequiredCoupledVar("c","Concentration variable");
  return params;
}

ElectrostaticFreeEnergy::ElectrostaticFreeEnergy(const InputParameters & parameters) :
    DerivativeFunctionMaterialBase(parameters),
    _relative_permittivity(getParam<Real>("relative_permittivity")),
    _metal_permittivity(getParam<Real>("metal_permittivity")),
    _grad_potential(coupledGradient("potential")),
    _h_value(getMaterialProperty<Real>("h_value")),
    _potential_var(coupled("potential"))
{
}

Real
ElectrostaticFreeEnergy::computeF()
{

  // Calculate the permittivity:
  Real eps_0 = 8.854187817620e-12; // C/V-m
  Real mP = _metal_permittivity * eps_0 / 1e6;
  Real oxP = _relative_permittivity * eps_0 / 1e6;
  Real eps = _h_value[_qp] * oxP + (1 - _h_value[_qp]) * mP;

  // Return the electrostatic energy density (including scaling from J to eV):
  return 0.5 * eps * std::abs(_grad_potential[_qp] * _grad_potential[_qp]) / (1.602e-19);
}

Real
ElectrostaticFreeEnergy::computeDF(unsigned int j_var)
{
  return 0.0;
}

Real
ElectrostaticFreeEnergy::computeD2F(unsigned int j_var, unsigned int k_var)
{
  return 0.0;
}

Real
ElectrostaticFreeEnergy::computeD3F(unsigned int j_var, unsigned int k_var, unsigned int l_var)
{
  return 0.0;
}

