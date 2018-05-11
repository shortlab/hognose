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


#ifndef BULKSWITCHPF_H
#define BULKSWITCHPF_H

#include "GeneralPostprocessor.h"

class BulkSwitchPF;

template<>
InputParameters validParams<BulkSwitchPF>();


class BulkSwitchPF : public GeneralPostprocessor
{
public:
  BulkSwitchPF(const InputParameters & parameters);
  virtual ~BulkSwitchPF();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();

protected:

  Real _value;

  const PostprocessorValue & _oxide_front;
  MooseEnum _oxide_front_units;
  const PostprocessorValue & _bulk_switch_signal_old;
  Real _transition_thickness;
  MooseEnum _transition_thickness_units;

};

#endif /* BULKSWITCHPF_H */
