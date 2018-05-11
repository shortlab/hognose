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


#include "Conduction.h"


template<>
InputParameters validParams<Conduction>()
{
  InputParameters params = validParams<Diffusion>();
  return params;
}

Conduction::Conduction(const InputParameters & parameters) :
    Diffusion(parameters),
    _zr_conductivity(getMaterialProperty<Real>("zr_conductivity"))
{}

Real Conduction::computeQpResidual()
{
  return _zr_conductivity[_qp]*Diffusion::computeQpResidual();
}

Real Conduction::computeQpJacobian()
{
  return _zr_conductivity[_qp]*Diffusion::computeQpJacobian();
}
