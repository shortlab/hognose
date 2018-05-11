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


#include "OneDElementIntegralVariablePostprocessor.h"

template<>
InputParameters validParams<OneDElementIntegralVariablePostprocessor>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  MooseEnum desired_units("um m cm mm nm"); // No default supplied
  params.addRequiredParam<MooseEnum>("desired_units",desired_units,"This string specifies the units for the oxide volume integral output.");
  params.addRequiredParam<Real>("universal_scaling_factor","The scaling factor for the entire simulation (ex. 1e-3 to get millimeters).");
  params.addParam<Real>("mesh_width",1.0,"The mesh width required for 2D or 3D simulations.");
  return params;
}

OneDElementIntegralVariablePostprocessor::OneDElementIntegralVariablePostprocessor(const InputParameters & parameters) :
    ElementIntegralVariablePostprocessor(parameters),
   _desired_units(getParam<MooseEnum>("desired_units")),
   _universal_scaling_factor(getParam<Real>("universal_scaling_factor")),
   _mesh_width(getParam<Real>("mesh_width"))
{
  addMooseVariableDependency(mooseVariable());
}

Real
OneDElementIntegralVariablePostprocessor::computeQpIntegral()
{   

  Real uqp;

  // Dividing by the mesh width to get the proper length:
  uqp = _u[_qp] / _mesh_width;

  // For flexibility, this PP needs to work regardless of what the overall scaling of the simulation is.
  // By scaling to mm, the if/else if statements below work regardless of the universal scaling factor value.
  uqp = (_universal_scaling_factor / (1e-3)) * uqp;
  
  // The value is now in millimeters, regardless of the scaling factor:
  if (_desired_units == "um") uqp = uqp / (1e-3);
  else if (_desired_units == "m") uqp = uqp / (1e3);
  else if (_desired_units == "cm") uqp = uqp / (1e1);
  else if (_desired_units == "mm") uqp = uqp; // / (1e0);
  else if (_desired_units == "nm") uqp = uqp / (1e-6);

  return uqp;
}
