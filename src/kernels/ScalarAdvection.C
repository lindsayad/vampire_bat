//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ScalarAdvection.h"
#include "MooseMesh.h"

registerMooseObject("NavierStokesApp", ScalarAdvection);

template <>
InputParameters
validParams<ScalarAdvection>()
{
  InputParameters params = validParams<Kernel>();

  params.addClassDescription("This class advects a scalar variable according to velocity "
                             "components coming from a Navier-Stokes simulation.");
  // Coupled variables
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", "y-velocity"); // only required in 2D and 3D
  params.addCoupledVar("w", "z-velocity"); // only required in 3D

  return params;
}

ScalarAdvection::ScalarAdvection(const InputParameters & parameters)
  : Kernel(parameters),

    // Coupled variables
    _u_vel(coupledValue("u")),
    _v_vel(_mesh.dimension() >= 2 ? coupledValue("v") : _zero),
    _w_vel(_mesh.dimension() == 3 ? coupledValue("w") : _zero),

    // Variable numberings
    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(_mesh.dimension() >= 2 ? coupled("v") : libMesh::invalid_uint),
    _w_vel_var_number(_mesh.dimension() == 3 ? coupled("w") : libMesh::invalid_uint)
{
}

Real
ScalarAdvection::computeQpResidual()
{
  RealVectorValue velocity(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);

  return -_grad_test[_i][_qp] * velocity * _u[_qp];
}

Real
ScalarAdvection::computeQpJacobian()
{
  RealVectorValue velocity(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);

  return -_grad_test[_i][_qp] * velocity * _phi[_j][_qp];
}

Real
ScalarAdvection::computeQpOffDiagJacobian(unsigned jvar)
{
  RealVectorValue velocity(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);

  if (jvar == _u_vel_var_number)
    return -_grad_test[_i][_qp](0) * _phi[_j][_qp] * _u[_qp];

  else if (jvar == _v_vel_var_number)
    return -_grad_test[_i][_qp](1) * _phi[_j][_qp] * _u[_qp];

  else if (jvar == _w_vel_var_number)
    return -_grad_test[_i][_qp](2) * _phi[_j][_qp] * _u[_qp];

  else
    return 0;
}
