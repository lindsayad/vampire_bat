//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoupledReactionNodal.h"

registerMooseObject("MooseApp", CoupledReactionNodal);

template <>
InputParameters
validParams<CoupledReactionNodal>()
{
  InputParameters params = validParams<NodalKernel>();
  params.addRequiredCoupledVar("v", "The coupled variabled.");
  params.addRequiredParam<Real>("coefficient", "The reaction coefficient.");
  return params;
}

CoupledReactionNodal::CoupledReactionNodal(const InputParameters & parameters)
  : NodalKernel(parameters),
    _v(coupledNodalValue("v")),
    _v_id(coupled("v")),
    _coeff(getParam<Real>("coefficient"))
{
}

Real
CoupledReactionNodal::computeQpResidual()
{
  return _coeff * _v[_qp];
}

Real
CoupledReactionNodal::computeQpJacobian()
{
  return 0;
}

Real
CoupledReactionNodal::computeQpOffDiagJacobian(unsigned jvar)
{
  if (_v_id == jvar)
    return _coeff;

  else
    return 0;
}
