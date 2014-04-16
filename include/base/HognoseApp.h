#ifndef HOGNOSEAPP_H
#define HOGNOSEAPP_H

#include "MooseApp.h"

class HognoseApp;

template<>
InputParameters validParams<HognoseApp>();

class HognoseApp : public MooseApp
{
public:
  HognoseApp(const std::string & name, InputParameters parameters);
  virtual ~HognoseApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* HOGNOSEAPP_H */
