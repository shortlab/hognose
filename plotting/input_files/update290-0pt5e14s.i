#energy in eV, length in micron
[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 400
  xmin = -0.05
  xmax = 3.0
[]

[Variables]
  [./c]
    order = THIRD
    family = HERMITE
    [./InitialCondition]
      type = FunctionIC
      variable = c
      function = 'if(x<0,0.68,(0.45-0.23*tanh(30*x-2.5)))'
    [../]
  [../]

  [./eta]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      variable = eta
      function = 'if(x<0,1,(-0.5*tanh(30*x-3)+0.5))'
    [../]
  [../]

  [./temp]
    order = FIRST
    family = LAGRANGE
    initial_condition = 630
    scaling = 1e-12
  [../]

  [./potential]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0
    scaling = 1e-2
  [../]
[]

[Kernels]
  [./detadt]
    type = TimeDerivative
    variable = eta
  [../]
  [./ACBulk]
    type = AllenCahn
    variable = eta
    args = 'c potential'
    f_name = F
  [../]
  [./ACInterface]
    type = ACInterface
    variable = eta
    kappa_name = kappa_eta
  [../]
  
  [./c_dot]
    type = TimeDerivative
    variable = c
  [../]
  [./CH_Parsed]
    type = CahnHilliard
    variable = c
    f_name = F
    mob_name = diffusivity
    args = 'eta potential'
  [../]
  [./CHint]
    type = CHInterface
    variable = c
    mob_name = diffusivity
    kappa_name = kappa_c
  [../]

  [./c_drift]
    type = CappedOxygenDrift
    variable = c
    potential = potential
    drift_conc = 0.001675
  [../]

  [./conduction]
    type = Conduction
    variable = temp
  [../]

  [./conduction-dt]
    type = TimeDerivativeConduction
    variable = temp
  [../]

  [./V_diffusion]
    type = Diffusion
    variable = potential
  [../]

  [./potential]
    type = ElectricPotentialKernel
    variable = potential
    charge_density = charge_density
    dielectric_constant = 15e-6
  [../]

  [./dVdt]
    type = TimeDerivative
    variable = potential
  [../]
[]

[AuxVariables]
   [./oxide_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./oxygen_density_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./O_vacancies]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./oxide_phase]
     order = CONSTANT
     family = MONOMIAL
     initial_condition = 1
   [../]

   [./charge_density]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./rho_density_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./electric_field_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./old_factor_value_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./dummy_temp]
     order = CONSTANT
     family = MONOMIAL
     initial_condition = 633
   [../]

   [./fluence_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./amorphous_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./s1_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./s2_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./s3_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./t1_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./t2_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]

   [./t3_aux]
     order = CONSTANT
     family = MONOMIAL
   [../]
[]



[AuxKernels] 
   active = 'electric_field_aux oxide_aux irradiation_charge_density_aux fluence_aux amorphous_aux s1_aux s2_aux s3_aux t1_aux t2_aux t3_aux'

   [./electric_field_aux]
     type = ElectricFieldAux
     variable = electric_field_aux
     normal = '1 0 0'
     potential = potential
   [../]

   [./oxide_aux]
    type = PFPhase
    variable = oxide_aux
    minimum = 0.99
    maximum = 1.01
    value = eta
  [../]

  [./irradiation_charge_density_aux]
    type = IrradiationChargeDensityAux
    variable = charge_density
    charge_constant = 100
    charge_constant_var = charge_constant_aux
    old_phase = eta
    phase = eta
    rho_function = '1'
    use_PP = 1
    charge_constant_PP = rho_PP
    transition_count = transition_count
    #n_flux = 
    fluence = fluence
    fluence_offset = fluence_offset
    n_flux_time_offset = flux_time_offset 
  [../]

  [./fluence_aux]
    type = MaterialRealAux
    variable = fluence_aux
    property = fluence
  [../]

  [./amorphous_aux]
    type = MaterialRealAux
    variable = amorphous_aux
    property = amorphous_width
  [../]

  [./s1_aux]
    type = MaterialRealAux
    variable = s1_aux
    property = s1_iron
  [../]

  [./s2_aux]
    type = MaterialRealAux
    variable = s2_aux
    property = s2_iron
  [../]

  [./s3_aux]
    type = MaterialRealAux
    variable = s3_aux
    property = s3_iron
  [../]

  [./t1_aux]
    type = MaterialRealAux
    variable = t1_aux
    property = amorphous_t1
  [../]

  [./t2_aux]
    type = MaterialRealAux
    variable = t2_aux
    property = amorphous_t2
  [../]

  [./t3_aux]
    type = MaterialRealAux
    variable = t3_aux
    property = amorphous_t3
  [../]

[]



[Functions]

  [./Hillner-T]
    type = PiecewiseConstant
    data_file = Hillner2000-fig8-high-flux-T.csv     #Hillnerbaseline
    #data_file = Hillner2000-fig8-high-low-flux-T.csv #Hillnerhilo
    direction = left
    format = columns
  [../]

  [./Hillner-n]
    type = PiecewiseConstant
    data_file = Hillner2000-fig8-high-flux-n.csv      #Hillnerbaseline
    #data_file = Hillner2000-fig8-high-low-flux-n.csv #Hillnerhilo
    direction = left
    format = columns
  [../]
[]

[BCs]
  active = 'c-left potential-left temp' 
 
  [./c-left]
    type = DirichletBC
    variable = c
    boundary = 'left'
    value = 0.68
  [../]

  [./temp]
    type = DirichletBC
    variable = temp
    boundary = 'right left'
    value = 563
  [../]

  [./function-T-left]
    type = FunctionDirichletBC
    variable = temp
    boundary = 'left'
    function = Hillner2000-fig9-temp-downshift-T
  [../]

  [./potential-left]
    type = DirichletBC
    variable = potential
    boundary = 'left'
    value = 0
  [../] 
[]






[Materials]
  active = 'consts free_energy free_energy_sum electrostatic new-mobility iron taylor'

  [./consts]
    type = GenericConstantMaterial
    block = 0
    prop_names  = 'L kappa_eta kappa_c total_diffusivity_factor'
    prop_values = '9e-7 4.45e4 4.45e4 1.0' 
  [../]

  [./free_energy]
    type = DerivativeParsedMaterial
    block = 0
    f_name = Fa
    args = 'c eta'
    function = '(3*eta^2-2*eta^3)*0.5*6.24e5*(c-0.66)^2 + (1-3*eta^2+2*eta^3)*0.5*6.24e5*(c-0.24)^2+1.54e8*(eta^2-2*eta^3+eta^4)'
    derivative_order = 2
    enable_jit = true
    outputs = '' #exodus
  [../]  

  [./free_energy_sum]
    type = DerivativeSumMaterial
    block = 0
    f_name = F
    sum_materials = 'Fa Fb'
    args = 'c eta potential'
    outputs = '' #exodus
  [../]

  [./electrostatic]
    type = ElectrostaticFreeEnergy
    block = 0
    f_name = Fb
    potential = potential
    c = c
    outputs = '' #exodus
  [../]

  [./new-mobility]
    type = MobilityforConcentrationPF
    block = 0
    Oxygen_conc = c
    coupled_temperature = temp #dummy_temp
    oxide_amount = eta
    phase = eta
    scaling_factor = 1e-6
    charge_value = 1
    # The delta_c parameter uses the default of 0.01333...
    stoich_fraction = 0.015
    Oxide_stoichiometry = 1.999
    oxide_baseline = 0.91e-17
    energy_units = 'eV'
    curvature_value_k = 1e5
    D1 = 4e-17
    T1 = 688
    D2 = 0.85e-17
    T2 = 633
    oxide_phase = oxide_phase
    doping_max_factor = 3.5
    charge_constant_initial = 100
    charge_density = charge_density
    doping_effect_on = 1
    doping_power = 5
    transition_count = transition_count
    outputs = exodus
  [../]

  [./iron]
    type = IronReleaseMaterial
    block = 0
    coupled_temperature = temp #dummy_temp
    #n_flux = 
    flux_time_offset = flux_time_offset
    fluence_offset = fluence_offset
    outputs = exodus
  [../]

  [./taylor]
    type = AmorphousWidthMaterial
    coupled_temperature = temp
    #n_flux = 
    transition_count = transition_count
    flux_time_offset = flux_time_offset
    transferred_delta_old = transferred_delta_old
    SPP_sizes = '100 225 350'
    SPP_number_fractions = '0.25 0.55 0.2'
    outputs = 'exodus'
    s1_PP = s1_PP
    s2_PP = s2_PP
    s3_PP = s3_PP
    t1_PP = t1_PP
    t2_PP = t2_PP
    t3_PP = t3_PP
  [../]
[]



[Postprocessors]

  [./num_lin_its]
    type = NumLinearIterations
    outputs = 'console csv'
  [../]

  [./total_oxide]
    type = OneDElementIntegralVariablePostprocessor
    variable = oxide_aux
    desired_units = um
    universal_scaling_factor = 1e-6
    outputs = 'console csv'
    execute_on = timestep_begin
  [../]

  [./min_charge_density]
    type = ElementExtremeValue
    variable = charge_density
    value_type = min
    outputs = 'console csv'
  [../]

  [./min_amorphous_width]
    type = ElementExtremeValue
    variable = amorphous_aux
    value_type = min
    outputs = 'console csv'
  [../]

  [./max_s1_aux]
    type = ElementExtremeValue
    variable = s1_aux
    value_type = max
    outputs = 'console csv'
  [../]

  [./max_s2_aux]
    type = ElementExtremeValue
    variable = s2_aux
    value_type = max
    outputs = 'console csv'
  [../]

  [./max_s3_aux]
    type = ElementExtremeValue
    variable = s3_aux
    value_type = max
    outputs = 'console csv'
  [../]

  [./max_t1_aux]
    type = ElementExtremeValue
    variable = t1_aux
    value_type = max
    outputs = 'console csv'
   [../]

  [./max_t2_aux]
    type = ElementExtremeValue
    variable = t2_aux
    value_type = max
    outputs = 'console csv'
   [../]

  [./max_t3_aux]
    type = ElementExtremeValue
    variable = t3_aux
    value_type = max
    outputs = 'console csv'
   [../]

  [./transferred_delta_old]
    type = Receiver
    outputs = 'console csv'
    execute_on = timestep_begin
  [../]

  [./rho_PP]
    type = Receiver
    outputs = 'console csv'
    execute_on = timestep_begin
  [../]

  [./transition_count]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./flux_time_offset]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./temp_BC]
    type = MultiAppBCPP
    initial_value = 633
    layer_T_drop = 1
    transition_counter = transition_count
    outputs = 'console csv'
  [../] 

  [./fluence_out]
    type = ElementExtremeValue
    value_type = max
    variable = fluence_aux
    outputs = 'console csv'
  [../] 

  [./fluence_offset]
    type = Receiver
    outputs = 'console csv'
  [../]  

  [./dt]
    type = TimestepSize
    outputs = 'console csv'
  [../]

  [./s1_PP]
    type = Receiver
    outputs = 'console csv'
  [../] 

  [./s2_PP]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./s3_PP]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./t1_PP]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./t2_PP]
    type = Receiver
    outputs = 'console csv'
  [../]

  [./t3_PP]
    type = Receiver
    outputs = 'console csv'
  [../]
[]



[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]



[Executioner]
  type = Transient
  solve_type = NEWTON
  l_max_its = 50
  l_tol = 1e-6
  nl_max_its = 50
  nl_abs_tol = 1e-12
  end_time = 8.64e8
  petsc_options_iname = '-pc_type -ksp_gmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  petsc_options_value = 'asm      31                  preonly      ilu          1'

  [./Predictor]
    type = SimplePredictor
    scale = 0.8
  [../]

  ss_check_tol = 1e-20

  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = 1e-6
    percent_change = 0.213
  [../]
[]



[Outputs]
  print_linear_residuals = true

  [./exodus]
    type = Exodus
    interval = 5000
  [../]

  [./console]
    type = Console
    perf_log = true
    interval = 500
    output_file = false
    all_variable_norms = true
  [../]

  [./csv]
    type = CSV
    interval = 500
    delimiter = ','
    additional_execute_on = final 
  [../]
[]

[GlobalParams]
   n_flux = '0.5e14'
[]
