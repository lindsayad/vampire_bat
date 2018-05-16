//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "VampireBatTestApp.h"
#include "VampireBatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<VampireBatTestApp>()
{
  InputParameters params = validParams<VampireBatApp>();
  return params;
}

VampireBatTestApp::VampireBatTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  VampireBatApp::registerObjectDepends(_factory);
  VampireBatApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  VampireBatApp::associateSyntaxDepends(_syntax, _action_factory);
  VampireBatApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  VampireBatApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    VampireBatTestApp::registerObjects(_factory);
    VampireBatTestApp::associateSyntax(_syntax, _action_factory);
    VampireBatTestApp::registerExecFlags(_factory);
  }
}

VampireBatTestApp::~VampireBatTestApp() {}

void
VampireBatTestApp::registerApps()
{
  registerApp(VampireBatApp);
  registerApp(VampireBatTestApp);
}

void
VampireBatTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
VampireBatTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
VampireBatTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
VampireBatTestApp__registerApps()
{
  VampireBatTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
VampireBatTestApp__registerObjects(Factory & factory)
{
  VampireBatTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
VampireBatTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  VampireBatTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
VampireBatTestApp__registerExecFlags(Factory & factory)
{
  VampireBatTestApp::registerExecFlags(factory);
}
