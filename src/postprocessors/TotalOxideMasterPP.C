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


#include "TotalOxideMasterPP.h"

template<>
InputParameters validParams<TotalOxideMasterPP>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  params.addParam<Real>("transition_thickness",2.0,"The thickness at which the oxide transitions.");
  params.addParam<std::string>("current_oxide", "The postprocessor providing the oxide thickness.");
  params.addParam<std::string>("num_complete_cycles","The postprocessor providing the number of transitions.");


  return params;
}

TotalOxideMasterPP::TotalOxideMasterPP(const InputParameters & parameters) :
    GeneralPostprocessor(parameters),
    _value(0),
    _transition_thickness(getParam<Real>("transition_thickness")),
    _current_oxide(getPostprocessorValueByName(getParam<std::string>("current_oxide"))),
    _num_complete_cycles(getPostprocessorValueByName(getParam<std::string>("num_complete_cycles"))),
    _num_complete_cycles_old(getPostprocessorValueOldByName(getParam<std::string>("num_complete_cycles")))
{
}

TotalOxideMasterPP::~TotalOxideMasterPP()
{
}

void
TotalOxideMasterPP::initialize()
{
}

void
TotalOxideMasterPP::execute()
{
  
  _value = _current_oxide + (_num_complete_cycles * _transition_thickness);

  if (_num_complete_cycles != _num_complete_cycles_old)
  {
	_value = _current_oxide + (_num_complete_cycles_old * _transition_thickness);
  }
  
}

Real
TotalOxideMasterPP::getValue()
{
  return _value;
}
