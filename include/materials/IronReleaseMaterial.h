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


#ifndef IRONRELEASEMATERIAL_H
#define IRONRELEASEMATERIAL_H

#include "Material.h"
#include "Function.h"

class IronReleaseMaterial;

template<>
InputParameters validParams<IronReleaseMaterial>();

class IronReleaseMaterial : public Material
{
public:
  IronReleaseMaterial(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;

  virtual void computeQpProperties();

private:

  Function & _n_flux;
  const PostprocessorValue & _time_offset;
  const PostprocessorValue & _fluence_offset;
  MaterialProperty<Real> & _fluence;
  const MaterialProperty<Real> & _fluence_old;
  MaterialProperty<Real> & _test_fluence;
  MaterialProperty<Real> & _test_fluence_old;
  MaterialProperty<Real> & _test_diff;

};

#endif //IRONRELEASEMATERIAL_H
