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


#ifndef IRRADIATIONCHARGEDENSITYAUX_H
#define IRRADIATIONCHARGEDENSITYAUX_H

#include "AuxKernel.h"
#include "Function.h"

class IrradiationChargeDensityAux;

template<>
InputParameters validParams<IrradiationChargeDensityAux>();

class IrradiationChargeDensityAux : public AuxKernel
{
public:

  IrradiationChargeDensityAux(const InputParameters & parameters);

  virtual ~IrradiationChargeDensityAux() {}
  
protected:
  virtual Real computeValue();

  Real _charge_constant;
  const MaterialProperty<Real> & _h_value;
  const MaterialProperty<Real> & _net_iron_change;
  const VariableValue & _old_phase;
  const VariableValue & _phase;
  Real _time_to_full_rho;
  Function & _rho_function;
  Real _use_PP;
  const PostprocessorValue & _charge_constant_PP;
  const PostprocessorValue & _transition_count;

  Function & _n_flux;
  const MaterialProperty<Real> & _fluence;
  const PostprocessorValue & _fluence_offset;
  const PostprocessorValue & _time_offset;
  Real _rho_Fe_value;
  Real _small_SPP;
  Real _delayed_Fe;

};

#endif //IRRADIATIONCHARGEDENSITYAUX_H
