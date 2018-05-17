[Kernels]
  [diffu]
    type = MatDiffusion
    D_name = diffu
    variable = u
  []
  [diffv]
    type = MatDiffusion
    D_name = diffv
    variable = v
  []
  [rxnu]
    type = CoefReaction
    coefficient = 2
    variable = u
  []
  [prodv]
    type = CoupledForce
    coef = 4
    v = 'u'
    variable = v
  []
[]

[Mesh]
  type = GeneratedMesh
  nx = 10
  dim = 2
[]

[BCs]
  [leftu]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 1
  []
  [rightu]
    type = DirichletBC
    variable = u
    boundary = 'right'
    value = 0
  []
  [leftv]
    type = DirichletBC
    variable = v
    boundary = 'left'
    value = 0
  []
  [rightv]
    type = DirichletBC
    variable = v
    boundary = 'right'
    value = 1
  []
[]

[Variables]
  [u]
  []
  [v]
  []
[]

[Materials]
  [const_mat]
    type = GenericConstantMaterial
    prop_values = '3 4'
    prop_names = 'diffu diffv'
  []
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
[]

[Outputs]
  exodus = true
[]
