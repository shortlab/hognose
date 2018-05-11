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


#ifndef TOTALOXIDEMASTERPP_H
#define TOTALOXIDEMASTERPP_H

#include "GeneralPostprocessor.h"

class TotalOxideMasterPP;

template<>
InputParameters validParams<TotalOxideMasterPP>();


class TotalOxideMasterPP : public GeneralPostprocessor
{
public:
  TotalOxideMasterPP(const InputParameters & parameters);
  virtual ~TotalOxideMasterPP();

  virtual void initialize();
  virtual void execute();
  virtual Real getValue();

protected:

  Real _value;

  Real _transition_thickness;
  const PostprocessorValue & _current_oxide;
  const PostprocessorValue & _num_complete_cycles;
  const PostprocessorValue & _num_complete_cycles_old;

};

#endif /* TOTALOXIDEMASTERPP_H */
