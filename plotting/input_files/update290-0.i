[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 325
  xmin = -0.05
  xmax = 3.0
[]

[Variables]
  [./u]
  [../]
[]

[AuxVariables]
  [./c_master]
    order = THIRD
    family = HERMITE
    [./InitialCondition]
      type = FunctionIC
      variable = c_master
      function = 'if(x<0,0.68,(0.45-0.23*tanh(30*x-2.5)))'
    [../]
  [../]

  [./eta_master]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      variable = eta_master
      function = 'if(x<0,1,(-0.5*tanh(30*x-3)+0.5))'
    [../]
  [../]

   [./master_oxide_aux]
     order = CONSTANT
     family = MONOMIAL
     initial_condition = 0
   [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
  [./td]
    type = TimeDerivative
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 1
  [../]
[]



[Executioner]
  type = Transient
  #num_steps = 10
  #dt = 500
  end_time = 864000000 #1296000 #(150 days)
  #start_time = 0

  nl_abs_tol = 1e-12

  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'

  verbose = 1

  [./TimeStepper]
    type = ConstantDT
    dt = 1e5 #1e6
    growth_factor = 2.123
  [../]
[]

[Outputs]

  [./console]
    type = Console
    perf_log = true
    interval = 1
    output_file = false
    all_variable_norms = true
  [../]

  [./csv]
    type = CSV
    interval = 1
    delimiter = ','
    additional_execute_on = final 
  [../]
[]

[MultiApps]
  [./sub_app]
    type = ResetTransientMultiApp
    input_files = 'update290-0s.i'
    app_type = HognoseApp
    sub_cycling = true
    output_sub_cycles = true
    max_failures = 100000000
    thickness_pp = master_oxide
    #transition_thickness = 0.2?
    reset_apps = 0
  [../]
[]



[Transfers]
active = 'oxide_out rho_out rho_in transition_counter_in flux_time_offset_in fluence_out fluence_in amorphous_width_out amorphous_width_in s1_out s2_out s3_out s1_in s2_in s3_in t1_out t1_in t2_out t2_in t3_out t3_in'
 
  [./oxide_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = total_oxide
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_oxide
  [../]

  [./rho_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = min_charge_density
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_charge_density
  [../]

  [./rho_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_charge_density
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = rho_PP
    execute_on = timestep_begin
  [../]

  [./transition_counter_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = transition_counter
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = transition_count
    execute_on = timestep_begin
  [../]

  [./flux_time_offset_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = transition_time 
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = flux_time_offset
    execute_on = timestep_begin
  [../]

  [./fluence_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = fluence_out
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = fluence_out
  [../]

  [./fluence_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = transition_fluence
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = fluence_offset
  [../]

  [./amorphous_width_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = min_amorphous_width
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_amorphous_width
  [../]

  [./amorphous_width_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_amorphous_width
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = transferred_delta_old
    execute_on = timestep_begin
  [../]

  [./s1_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = max_s1_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_s1_aux
  [../]

  [./s2_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = max_s2_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_s2_aux
  [../]

  [./s3_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = max_s3_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_s3_aux
  [../]

  [./s1_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_s1_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = s1_PP
    execute_on = timestep_begin
  [../]

  [./s2_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_s2_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = s2_PP
    execute_on = timestep_begin
  [../]

  [./s3_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_s3_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = s3_PP
    execute_on = timestep_begin
  [../]

 [./t1_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = max_t1_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_t1_aux
  [../]

  [./t1_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_t1_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = t1_PP
    execute_on = timestep_begin
  [../]

 [./t2_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = max_t2_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_t2_aux
  [../]

  [./t2_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_t2_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = t2_PP
    execute_on = timestep_begin
  [../]

 [./t3_out]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    from_postprocessor = max_t3_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = master_t3_aux
  [../]

  [./t3_in]
    type = MultiAppPostprocessorTransfer
    direction = to_multiapp
    from_postprocessor = master_t3_aux
    multi_app = sub_app
    reduction_type = maximum
    to_postprocessor = t3_PP
    execute_on = timestep_begin
  [../]
 
[]

[Postprocessors]

  [./master_oxide]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_charge_density]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_amorphous_width]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./transition_counter]
    type = BulkSwitchPF
    outputs = 'console csv'
    oxide_front = master_oxide
    oxide_front_units = um
    bulk_switch_signal_old = transition_counter
    #transition_thickness = 0.2?
    transition_thickness_units = um
  [../]

  [./TOTAL_oxide]
    type = TotalOxideMasterPP
    #transition_thickness = 0.2?
    current_oxide = master_oxide
    num_complete_cycles = transition_counter
    outputs = 'console csv'
  [../]

  [./transition_time]
    type = TransitionTimePP
    transition_time_old = transition_time
    num_complete_cycles = transition_counter
  [../]

  [./fluence_out]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./transition_fluence]
    type = TransitionFluencePP
    num_complete_cycles = transition_counter
    fluence = fluence_out
    transition_fluence_old = transition_fluence
  [../]

  [./master_s1_aux]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_s2_aux]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_s3_aux]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_t1_aux]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_t2_aux]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./master_t3_aux]
    type = Receiver
    outputs = 'console csv'
  [../]
[]


[UserObjects]
active = 'arnold'

  [./arnold]
    type = Terminator
    expression = 'TOTAL_oxide > 2'
  [../]
[]

[GlobalParams]
  transition_thickness = 2
[]





