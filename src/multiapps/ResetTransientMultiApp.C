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


// MOOSE includes
#include "ResetTransientMultiApp.h"
#include "PostprocessorInterface.h"



template <>
InputParameters
validParams<ResetTransientMultiApp>()
{
  InputParameters params = validParams<TransientMultiApp>();

  params.addParam<PostprocessorName>("thickness_pp", 2.1, "Oxide thickness postprocessor.");
  params.addRequiredParam<Real>("transition_thickness","Specifies the transition thickness of "
				"the oxide.");

  return params;
}

ResetTransientMultiApp::ResetTransientMultiApp(const InputParameters & parameters)
  : TransientMultiApp(parameters),
    PostprocessorInterface(this),
    //_oxide_thickness(getParam<PostprocessorName>("thickness_pp")),
   _oxide_thickness(getPostprocessorValue("thickness_pp")),
    _transition_thickness(getParam<Real>("transition_thickness"))
    
{
 
}

void
ResetTransientMultiApp::preTransfer(Real /*dt*/, Real target_time)
{
  // First, see if any Apps need to be Reset
  if (!_reset_happened && target_time + 1e-14 >= _reset_time)
  {
    _reset_happened = true;
    for (auto & app : _reset_apps)
      resetApp(app, 0.0); // change this time to something variable and real? see original source code for a note.
  }

  // Next, reset the Apps based on the oxide thickness criterion:
  //FEProblemBase & from_problem = _multi_app->problemBase();

  //Real pp_value = from_problem.getPostprocessorValue(_oxide_thickness);

  if (_oxide_thickness > _transition_thickness)
  {
    _reset_happened = true;
    for (auto & app : _reset_apps)
      resetApp(app, 0.0); // change this time to something variable and real? see original source code for a note.
  }
  
  //{
  //for (auto & app : _reset_apps)
  //  resetApp(app, 0.0);
  //}

  // Now move any apps that should be moved
  if (_use_positions && !_move_happened && target_time + 1e-14 >= _move_time)
  {
    _move_happened = true;
    for (unsigned int i = 0; i < _move_apps.size(); i++)
      moveApp(_move_apps[i], _move_positions[i]);
  }
}
