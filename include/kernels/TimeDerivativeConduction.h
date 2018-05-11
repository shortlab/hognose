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


#ifndef TIMEDERIVATIVECONDUCTION_H
#define TIMEDERIVATIVECONDUCTION_H

#include "TimeDerivative.h"

class TimeDerivativeConduction;

template<>
InputParameters validParams<TimeDerivativeConduction>();

class TimeDerivativeConduction : public TimeDerivative
{
public:

  TimeDerivativeConduction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  Real _time_coeff;
  const MaterialProperty<Real> & _zr_mass_density;
  const MaterialProperty<Real> & _zr_specific_heat;

};

#endif //TIMEDERIVATIVECONDUCTION_H
