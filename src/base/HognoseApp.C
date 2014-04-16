#include "HognoseApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<HognoseApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

HognoseApp::HognoseApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(libMesh::processor_id());
  
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  HognoseApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  HognoseApp::associateSyntax(_syntax, _action_factory);
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
}

void
HognoseApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
