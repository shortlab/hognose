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


#ifndef ELECTRICPOTENTIALKERNEL_H
#define ELECTRICPOTENTIALKERNEL_H


#include "Kernel.h"

class ElectricPotentialKernel;

template<>
InputParameters validParams<ElectricPotentialKernel>();

class ElectricPotentialKernel : public Kernel
{
public:

  ElectricPotentialKernel(const InputParameters & parameters);
  virtual ~ElectricPotentialKernel();

protected:

  virtual Real computeQpResidual();

  const VariableValue & _charge_density;
  const MaterialProperty<Real> & _h_value;
  Real _dielectric_constant;

private:

};

#endif //ELECTRICPOTENTIALKERNEL_H
