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


#include "BulkSwitchPF.h"

template<>
InputParameters validParams<BulkSwitchPF>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  params.addParam<std::string>("oxide_front", "The name of the postprocessor providing the oxide front location.");
  MooseEnum oxide_front_units("um m cm mm nm");
  params.addRequiredParam<MooseEnum>("oxide_front_units",oxide_front_units,"This string specifies the incoming units for this thickness.");
  params.addParam<std::string>("bulk_switch_signal_old","The name of this PP to provide the old value of this PP.");
  params.addRequiredParam<Real>("transition_thickness","Specifies the allowed thickness of the understressed oxide.");
  MooseEnum understressed_thickness_units("um m cm mm nm");
  params.addRequiredParam<MooseEnum>("transition_thickness_units",understressed_thickness_units,"This string specifies the incoming units for this thickness.");

  return params;
}

BulkSwitchPF::BulkSwitchPF(const InputParameters & parameters) :
    GeneralPostprocessor(parameters),
    _value(0),
    _oxide_front(getPostprocessorValueByName(getParam<std::string>("oxide_front"))),
    _oxide_front_units(getParam<MooseEnum>("oxide_front_units")),
    _bulk_switch_signal_old(getPostprocessorValueOldByName(getParam<std::string>("bulk_switch_signal_old"))),
    _transition_thickness(getParam<Real>("transition_thickness")),
    _transition_thickness_units(getParam<MooseEnum>("transition_thickness_units"))
{
}

BulkSwitchPF::~BulkSwitchPF()
{
}

void
BulkSwitchPF::initialize()
{
}

void
BulkSwitchPF::execute()
{
  // Convert the incoming postprocessors into the same length scale:

  Real oxide_front;
  if (_oxide_front_units == "um")
  {
	oxide_front = _oxide_front / (1e6);
  }
  else if (_oxide_front_units == "m")
  {
	oxide_front = _oxide_front;
  }
  else if (_oxide_front_units == "cm")
  {
	oxide_front = _oxide_front / (1e2);
  }
  else if (_oxide_front_units == "mm")
  {
	oxide_front = _oxide_front / (1e3);
  }
  else if (_oxide_front_units == "nm")
  {
	oxide_front = _oxide_front / (1e9);
  }



  Real transition_thickness;
  if (_transition_thickness_units == "um")
  {
	transition_thickness = _transition_thickness / (1e6);
  }
  else if (_transition_thickness_units == "m")
  {
	transition_thickness = _transition_thickness;
  }
  else if (_transition_thickness_units == "cm")
  {
	transition_thickness = _transition_thickness / (1e2);
  }
  else if (_transition_thickness_units == "mm")
  {
	transition_thickness = _transition_thickness / (1e3);
  }
  else if (_transition_thickness_units == "nm")
  {
	transition_thickness = _transition_thickness / (1e9);
  }

  
  if (oxide_front > transition_thickness)
  {
	_value = 1 + _bulk_switch_signal_old; // increment the transition counter
  }
  else
  {
	_value = _bulk_switch_signal_old; 
  }


  
}

Real
BulkSwitchPF::getValue()
{
  return _value;
}
