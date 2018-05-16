//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef VAMPIRE_BATTESTAPP_H
#define VAMPIRE_BATTESTAPP_H

#include "MooseApp.h"

class VampireBatTestApp;

template <>
InputParameters validParams<VampireBatTestApp>();

class VampireBatTestApp : public MooseApp
{
public:
  VampireBatTestApp(InputParameters parameters);
  virtual ~VampireBatTestApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
};

#endif /* VAMPIRE_BATTESTAPP_H */
