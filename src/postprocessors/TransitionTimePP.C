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


#include "TransitionTimePP.h"

template<>
InputParameters validParams<TransitionTimePP>()
{
  InputParameters params = validParams<GeneralPostprocessor>();


  params.addParam<std::string>("transition_time_old", "The name of this postprocessor.");
  params.addParam<std::string>("num_complete_cycles","The postprocessor providing the number of transitions.");


  return params;
}

TransitionTimePP::TransitionTimePP(const InputParameters & parameters) :
    GeneralPostprocessor(parameters),
    _value(0),
    _transition_time_old(getPostprocessorValueByName(getParam<std::string>("transition_time_old"))),
    _num_complete_cycles(getPostprocessorValueByName(getParam<std::string>("num_complete_cycles"))),
    _num_complete_cycles_old(getPostprocessorValueOldByName(getParam<std::string>("num_complete_cycles")))
{
}

TransitionTimePP::~TransitionTimePP()
{
}

void
TransitionTimePP::initialize()
{
}

void
TransitionTimePP::execute()
{
  
  if (_num_complete_cycles < 1)
  {
	_value = 0; // no offset in the first cycle
  }

  if (_num_complete_cycles != _num_complete_cycles_old)
  {
	_value = _t; // return the time when the transition occurred
  }
  else
  {
	_value = _transition_time_old; // if it's not a transition, no change in offset
  }
  
}

Real
TransitionTimePP::getValue()
{
  return _value;
}
