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

#ifndef ELECTROSTATICFREEENERGY_H
#define ELECTROSTATICFREEENERGY_H

#include "DerivativeFunctionMaterialBase.h"

class ElectrostaticFreeEnergy;

template<>
InputParameters validParams<ElectrostaticFreeEnergy>();

class ElectrostaticFreeEnergy : public DerivativeFunctionMaterialBase
{
public:
  ElectrostaticFreeEnergy(const InputParameters & parameters);

protected:
  virtual Real computeF();
  virtual Real computeDF(unsigned int j_var);
  virtual Real computeD2F(unsigned int j_var, unsigned int k_var);
  virtual Real computeD3F(unsigned int j_var, unsigned int k_var, unsigned int l_var);

private:

  Real _relative_permittivity;
  Real _metal_permittivity;
  const VariableGradient & _grad_potential;
  const MaterialProperty<Real> & _h_value;
  unsigned int _potential_var;
};

#endif //ELECTROSTATICFREEENERGY_H
