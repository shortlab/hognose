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


#include "NodalBC.h"

#ifndef MULTIAPPINCREMENTBC_H
#define MULTIAPPINCREMENTBC_H

class MultiAppIncrementBC;

template<>
InputParameters validParams<MultiAppIncrementBC>();

class MultiAppIncrementBC : public NodalBC
{
public:

  MultiAppIncrementBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

private:

  Real _initial_value;
  Real _layer_T_drop;
  const PostprocessorValue & _transition_counter;
  
};

#endif //MULTIAPPINCREMENTBC_H
