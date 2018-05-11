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


#include "IronReleaseMaterial.h"


template<>
InputParameters validParams<IronReleaseMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addParam<FunctionName>("n_flux", "0", "Function for the neutron flux.");
  params.addParam<PostprocessorName>("flux_time_offset",0,"Postprocessor providing the time "
				     "to use with the neutron flux function.");
  params.addParam<PostprocessorName>("fluence_offset",0,"Postprocessor providing the fluence "
				     "from the last cycle.");
  return params;
}

IronReleaseMaterial::IronReleaseMaterial(const InputParameters & parameters) :
    Material(parameters),

    _n_flux(getFunction("n_flux")),
    _time_offset(getPostprocessorValue("flux_time_offset")),
    _fluence_offset(getPostprocessorValue("fluence_offset")),
    _fluence(declareProperty<Real>("fluence")),
    _fluence_old(getMaterialPropertyOld<Real>("fluence")),
    _test_fluence(declareProperty<Real>("test_fluence")),
    _test_fluence_old(declareProperty<Real>("test_fluence_old")),
    _test_diff(declareProperty<Real>("test_diff"))

{}

void
IronReleaseMaterial::initQpStatefulProperties()
{
  computeQpProperties();
}


void IronReleaseMaterial::computeQpProperties()
{

  _fluence[_qp] = (_dt * _n_flux.value(_t, _q_point[_qp])) + _fluence_old[_qp];

  // Debugging:
  _test_fluence[_qp] = (_fluence[_qp] + _fluence_offset) / 1e21;
  _test_fluence_old[_qp] = (_fluence_old[_qp] + _fluence_offset) / 1e21;
  _test_diff[_qp] = _test_fluence[_qp] - _test_fluence_old[_qp];


}
