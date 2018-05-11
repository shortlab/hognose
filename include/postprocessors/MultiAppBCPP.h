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


#ifndef MULTIAPPBCPP_H
#define MULTIAPPBCPP_H

#include "GeneralPostprocessor.h"

class MultiAppBCPP;

template<>
InputParameters validParams<MultiAppBCPP>();


class MultiAppBCPP : public GeneralPostprocessor
{
public:
  MultiAppBCPP(const InputParameters & parameters);
  virtual ~MultiAppBCPP();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();

protected:

  Real _value;

  Real _initial_value;
  Real _layer_T_drop;
  const PostprocessorValue & _transition_counter;

};

#endif /* MULTIAPPBCPP_H */
