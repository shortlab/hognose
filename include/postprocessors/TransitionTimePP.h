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


#ifndef TRANSITIONTIMEPP_H
#define TRANSITIONTIMEPP_H

#include "GeneralPostprocessor.h"

class TransitionTimePP;

template<>
InputParameters validParams<TransitionTimePP>();


class TransitionTimePP : public GeneralPostprocessor
{
public:
  TransitionTimePP(const InputParameters & parameters);
  virtual ~TransitionTimePP();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();

protected:

  Real _value;

  const PostprocessorValue & _transition_time_old;
  const PostprocessorValue & _num_complete_cycles;
  const PostprocessorValue & _num_complete_cycles_old;

};

#endif /* TRANSITIONTIMEPP_H */
