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


#include "MultiAppBCPP.h"

template<>
InputParameters validParams<MultiAppBCPP>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  params.addParam<Real>("initial_value", "Value for the boundary for the first cycle.");
  params.addParam<Real>("layer_T_drop",0,"Temperature drop across a layer of oxide.");
  params.addParam<PostprocessorName>("transition_counter",0,"The PP providing the number of oxide layers.");


  return params;
}

MultiAppBCPP::MultiAppBCPP(const InputParameters & parameters) :
    GeneralPostprocessor(parameters),
    _value(0),
    _initial_value(getParam<Real>("initial_value")),
    _layer_T_drop(getParam<Real>("layer_T_drop")),
    _transition_counter(getPostprocessorValue("transition_counter"))
{
}

MultiAppBCPP::~MultiAppBCPP()
{
}

void
MultiAppBCPP::initialize()
{
}

void
MultiAppBCPP::execute()
{
  
  _value = (_initial_value + (_layer_T_drop * _transition_counter));
  
}

Real
MultiAppBCPP::getValue()
{
  return _value;
}
