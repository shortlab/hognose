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


#include "TransitionFluencePP.h"

template<>
InputParameters validParams<TransitionFluencePP>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  params.addParam<std::string>("num_complete_cycles","The postprocessor providing the number of transitions.");
  params.addParam<std::string>("fluence", "The postprocessor providing the max value of fluence.");
  params.addParam<std::string>("transition_fluence_old", "The name of this postprocessor.");

  return params;
}

TransitionFluencePP::TransitionFluencePP(const InputParameters & parameters) :
    GeneralPostprocessor(parameters),
    _value(0),
    _num_complete_cycles(getPostprocessorValueByName(getParam<std::string>("num_complete_cycles"))),
    _num_complete_cycles_old(getPostprocessorValueOldByName(getParam<std::string>("num_complete_cycles"))),
    _fluence(getPostprocessorValueByName(getParam<std::string>("fluence"))),
    _transition_fluence_old(getPostprocessorValueOldByName(getParam<std::string>("transition_fluence_old")))
{
}

TransitionFluencePP::~TransitionFluencePP()
{
}

void
TransitionFluencePP::initialize()
{
}

void
TransitionFluencePP::execute()
{
  
  if (_num_complete_cycles < 1)
  {
	_value = 0; // no offset in the first cycle
  }

  if (_num_complete_cycles != _num_complete_cycles_old)
  {
	_value = _fluence + _transition_fluence_old; // return the fluence when the transition occurred
  }
  else
  {
	_value = _transition_fluence_old; // if it's not a transition, no change in offset
  }
  
}

Real
TransitionFluencePP::getValue()
{
  return _value;
}
