//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef COUPLEDREACTIONNODAL_H
#define COUPLEDREACTIONNODAL_H

#include "NodalKernel.h"

// Forward Declarations
class CoupledReactionNodal;

template <>
InputParameters validParams<CoupledReactionNodal>();

/**
 * Represents the rate in a simple ODE of du/dt = rate
 */
class CoupledReactionNodal : public NodalKernel
{
public:
  /**
   * Constructor initializes the rate
   */
  CoupledReactionNodal(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned jvar) override;

  const VariableValue & _v;
  unsigned _v_id;
  const Real _coeff;
};

#endif
