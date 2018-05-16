#include "VampireBatApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<VampireBatApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

VampireBatApp::VampireBatApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  VampireBatApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  VampireBatApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  VampireBatApp::registerExecFlags(_factory);
}

VampireBatApp::~VampireBatApp() {}

void
VampireBatApp::registerApps()
{
  registerApp(VampireBatApp);
}

void
VampireBatApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"VampireBatApp"});
}

void
VampireBatApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"VampireBatApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
VampireBatApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
VampireBatApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
VampireBatApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
VampireBatApp__registerApps()
{
  VampireBatApp::registerApps();
}

extern "C" void
VampireBatApp__registerObjects(Factory & factory)
{
  VampireBatApp::registerObjects(factory);
}

extern "C" void
VampireBatApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  VampireBatApp::associateSyntax(syntax, action_factory);
}

extern "C" void
VampireBatApp__registerExecFlags(Factory & factory)
{
  VampireBatApp::registerExecFlags(factory);
}
