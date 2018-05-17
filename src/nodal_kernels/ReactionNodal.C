//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ReactionNodal.h"

registerMooseObject("MooseApp", ReactionNodal);

template <>
InputParameters
validParams<ReactionNodal>()
{
  InputParameters params = validParams<NodalKernel>();
  return params;
}

ReactionNodal::ReactionNodal(const InputParameters & parameters) : NodalKernel(parameters) {}

Real
ReactionNodal::computeQpResidual()
{
  return _u[_qp];
}

Real
ReactionNodal::computeQpJacobian()
{
  return 1;
}
