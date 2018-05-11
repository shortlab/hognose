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


#ifndef ONEDELEMENTINTEGRALVARIABLEPOSTPROCESSOR_H
#define ONEDELEMENTINTEGRALVARIABLEPOSTPROCESSOR_H

#include "ElementIntegralVariablePostprocessor.h"

class OneDElementIntegralVariablePostprocessor;

template<>
InputParameters validParams<OneDElementIntegralVariablePostprocessor>();

class OneDElementIntegralVariablePostprocessor :
  public ElementIntegralVariablePostprocessor

{
public:
  OneDElementIntegralVariablePostprocessor(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral();

  // Desired units on oxide thickess:
  MooseEnum _desired_units;

  // Universal unit scaling factor:
  Real _universal_scaling_factor;

  // Mesh width for solid mechanics (at least 2D) simulations:
  Real _mesh_width;

};

#endif /* ONEDELEMENTINTEGRALVARIABLEPOSTPROCESSOR_H */
