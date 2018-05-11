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


#ifndef ELECTRICFIELDAUX_H
#define ELECTRICFIELDAUX_H

#include "AuxKernel.h"
  
class ElectricFieldAux;

template<>
InputParameters validParams<ElectricFieldAux>();


class ElectricFieldAux : public AuxKernel
{
public:

  ElectricFieldAux(const InputParameters & parameters);

  virtual ~ElectricFieldAux() {}
  
protected:
  virtual Real computeValue();

  std::vector<Point> _normal;
  const VariableGradient & _grad_potential;

};

#endif //ELECTRICFIELDAUX_H
