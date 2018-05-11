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


#include "ElectricFieldAux.h"

// Moose
#include "MooseTypes.h"
#include "FEProblem.h"

// libMesh
#include "libmesh/meshfree_interpolation.h"
#include "libmesh/system.h"

template<>
InputParameters validParams<ElectricFieldAux>()
{
     InputParameters params = validParams<AuxKernel>();
     params.addRequiredParam<std::vector<Point> >("normal", "The normal to be used with the gradient.");
     params.addRequiredCoupledVar("potential","The variable providing the electric potential.");

     return params;
}

ElectricFieldAux::ElectricFieldAux(const InputParameters & parameters)
  :AuxKernel(parameters),
    _normal(getParam<std::vector<Point> >("normal")),
    _grad_potential(coupledGradient("potential"))

{}

Real
ElectricFieldAux::computeValue()
{

  return - _grad_potential[_qp] * _normal[0];

}
