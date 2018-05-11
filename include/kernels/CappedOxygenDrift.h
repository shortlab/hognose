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


#ifndef CAPPEDOXYGENDRIFT_H
#define CAPPEDOXYGENDRIFT_H


#include "Kernel.h"

class CappedOxygenDrift;

template<>
InputParameters validParams<CappedOxygenDrift>();

class CappedOxygenDrift : public Kernel
{
public:

  CappedOxygenDrift(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const VariableGradient & _grad_potential;
  unsigned int _v_var;
  const MaterialProperty<Real> & _total_diffusivity_factor;
  const MaterialProperty<Real> & _h_value;
  const MaterialProperty<Real> & _o_ion_mobility;
  Real _drift_conc;

private:

};

#endif //CAPPEDOXYGENDRIFT_H
