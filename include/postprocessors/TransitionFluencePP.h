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


#ifndef TRANSITIONFLUENCEPP_H
#define TRANSITIONFLUENCEPP_H

#include "GeneralPostprocessor.h"

class TransitionFluencePP;

template<>
InputParameters validParams<TransitionFluencePP>();


class TransitionFluencePP : public GeneralPostprocessor
{
public:
  TransitionFluencePP(const InputParameters & parameters);
  virtual ~TransitionFluencePP();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();

protected:

  Real _value;

  const PostprocessorValue & _num_complete_cycles;
  const PostprocessorValue & _num_complete_cycles_old;
  const PostprocessorValue & _fluence;
  const PostprocessorValue & _transition_fluence_old;

};

#endif /* TRANSITIONFLUENCEPP_H */
