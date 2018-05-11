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


#ifndef PFPHASE_H
#define PFPHASE_H

#include "AuxKernel.h"
  

class PFPhase;

template<>
InputParameters validParams<PFPhase>();

class PFPhase : public AuxKernel
{
public:

  PFPhase(const InputParameters & parameters);

  virtual ~PFPhase() {}
  
protected:
  virtual Real computeValue();

 const VariableValue & _value;
 Real _min;
 Real _max;

};

#endif //PFPHASE_H
