[GlobalParams]
  gravity = '0 0 0'
  pspg = true
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1.0
  ymin = 0
  ymax = 1.0
  nx = 40
  ny = 40
[]

[MeshModifiers]
  [./corner_node]
    type = AddExtraNodeset
    new_boundary = 'pinned_node'
    nodes = '0'
  [../]
[]

[Variables]
  [./vel_x]
  [../]
  [./vel_y]
  [../]
  [./p]
  [../]
  [./ca]
  [../]
  [./cb]
  [../]
[]

[Kernels]
  # mass
  [./mass]
    type = INSMass
    variable = p
    u = vel_x
    v = vel_y
    p = p
  [../]

  # x-momentum, time
  [./x_momentum_time]
    type = INSMomentumTimeDerivative
    variable = vel_x
  [../]

  # x-momentum, space
  [./x_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_x
    u = vel_x
    v = vel_y
    p = p
    component = 0
  [../]

  # y-momentum, time
  [./y_momentum_time]
    type = INSMomentumTimeDerivative
    variable = vel_y
  [../]

  # y-momentum, space
  [./y_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_y
    u = vel_x
    v = vel_y
    p = p
    component = 1
  [../]

  [diffa]
    type = MatDiffusion
    D_name = diffa
    variable = ca
  []
  [diffb]
    type = MatDiffusion
    D_name = diffb
    variable = cb
  []
  [rxna]
    type = CoefReaction
    coefficient = 2
    variable = ca
  []
  [prodb]
    type = CoupledForce
    coef = 4
    v = 'ca'
    variable = cb
  []
  [adva]
    type = ScalarAdvection
    variable = ca
    u = vel_x
    v = vel_y
  []
  [advb]
    type = ScalarAdvection
    variable = cb
    u = vel_x
    v = vel_y
  []
  [timea]
    type = TimeDerivative
    variable = ca
  []
  [timeb]
    type = TimeDerivative
    variable = cb
  []
[]

[BCs]
  [./x_no_slip]
    type = DirichletBC
    variable = vel_x
    boundary = 'bottom right left'
    value = 0.0
  [../]

  [./lid]
    type = FunctionDirichletBC
    variable = vel_x
    boundary = 'top'
    function = 'lid_function'
  [../]

  [./y_no_slip]
    type = DirichletBC
    variable = vel_y
    boundary = 'bottom right top left'
    value = 0.0
  [../]

  [./pressure_pin]
    type = DirichletBC
    variable = p
    boundary = 'pinned_node'
    value = 0
  [../]

  [./diri_a]
    type = DirichletBC
    variable = ca
    value = 1
    boundary = 'top'
  [../]
  [./diri_b]
    type = DirichletBC
    variable = cb
    value = 1
    boundary = 'top'
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    block = 0
    prop_names = 'rho mu diffa diffb'
    prop_values = '1  1  .003     .004'
  [../]
[]

[Functions]
  [./lid_function]
    # We pick a function that is exactly represented in the velocity
    # space so that the Dirichlet conditions are the same regardless
    # of the mesh spacing.
    type = ParsedFunction
    value = '4*x*(1-x)'
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
    solve_type = 'NEWTON'
  [../]
[]

[Executioner]
  type = Transient
  # Run for 100+ timesteps to reach steady state.
  num_steps = 1000
  dtmin = .5
  petsc_options_iname = '-pc_type -pc_asm_overlap -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = 'asm      2               ilu          4'
  line_search = 'none'
  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-13
  nl_max_its = 6
  l_tol = 1e-6
  l_max_its = 500
  steady_state_detection = true
  [./TimeStepper]
    dt = .5
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    growth_factor = 1.5
    optimal_iterations = 6
  [../]
[]

[Outputs]
  file_base = lid_driven_out
  exodus = true
  checkpoint = true
[]
