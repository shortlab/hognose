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
#include "HognoseApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ActionFactory.h"
#include "MooseSyntax.h"


#include "PhaseFieldApp.h"




/////////////////////////////////////////////////
//           Hognose Include Files             //
/////////////////////////////////////////////////

#include "CappedOxygenDrift.h"
#include "Conduction.h"
#include "ElectricPotentialKernel.h"
#include "TimeDerivativeConduction.h"


#include "AmorphousWidthMaterial.h"
#include "ElectrostaticFreeEnergy.h"
#include "IronReleaseMaterial.h"
#include "MobilityforConcentrationPF.h"


#include "ElectricFieldAux.h"
#include "IrradiationChargeDensityAux.h"
#include "PFPhase.h"


#include "MultiAppIncrementBC.h"


#include "BulkSwitchPF.h"
#include "MultiAppBCPP.h"
#include "OneDElementIntegralVariablePostprocessor.h"
#include "TotalOxideMasterPP.h"
#include "TransitionFluencePP.h"
#include "TransitionTimePP.h"

#include "ResetTransientMultiApp.h"


template<>
InputParameters validParams<HognoseApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("use_legacy_output_syntax") = false;
  return params;
}

HognoseApp::HognoseApp(const InputParameters & parameters) :
    MooseApp(parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);

  HognoseApp::registerObjects(_factory);

  PhaseFieldApp::registerObjects(_factory);


  Moose::associateSyntax(_syntax, _action_factory);


  HognoseApp::associateSyntax(_syntax, _action_factory);

  PhaseFieldApp::associateSyntax(_syntax, _action_factory);

}

HognoseApp::~HognoseApp()
{
}

void
HognoseApp::registerApps()
{
  registerApp(HognoseApp);

}

void
HognoseApp::registerObjects(Factory & factory)
{
//////////////////////////////////////////////////////
//           Hognose Object Registration            //
//////////////////////////////////////////////////////

  // Register kernels:
  registerKernel(CappedOxygenDrift);
  registerKernel(Conduction);
  registerKernel(ElectricPotentialKernel);
  registerKernel(TimeDerivativeConduction);


  // Register materials:
  registerMaterial(AmorphousWidthMaterial);
  registerMaterial(ElectrostaticFreeEnergy);
  registerMaterial(IronReleaseMaterial);
  registerMaterial(MobilityforConcentrationPF);


  // Register auxkernels:
  registerAux(ElectricFieldAux);
  registerAux(IrradiationChargeDensityAux);
  registerAux(PFPhase);


  // Register Boundary Conditions:
  registerBoundaryCondition(MultiAppIncrementBC);


  // Register postprocessors:
  registerPostprocessor(BulkSwitchPF);
  registerPostprocessor(MultiAppBCPP);
  registerPostprocessor(OneDElementIntegralVariablePostprocessor);
  registerPostprocessor(TotalOxideMasterPP);
  registerPostprocessor(TransitionFluencePP);
  registerPostprocessor(TransitionTimePP);


  // Register multiapps:
  registerMultiApp(ResetTransientMultiApp);

}

void
HognoseApp::associateSyntax(Syntax &, ActionFactory &)
{
}
