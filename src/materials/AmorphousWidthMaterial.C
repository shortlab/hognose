/*******************************************************************/
/*                    DO NOT MODIFY THIS HEADER                    */
/*                                                                 */
/*                             HOGNOSE                             */
/*            High-speed Oxide Growth in a Numerically             */
/*                Optimized Simulation Environment                 */
/*                                                                 */
/*         (c) 2017 Massachusetts Institute of Technology          */
/*                      ALL RIGHTS RESERVED                        */
/*                                                                 */
/*                                                                 */
/*  Prepared by Andrew Dykhuis and Michael P. Short as a part of   */
/*  the United States Department of Energy's Consortium for the    */
/*  Advanced Simulation of Light-Water Reactors (CASL).            */
/*            					                   */
/*******************************************************************/


#include "AmorphousWidthMaterial.h"


template<>
InputParameters validParams<AmorphousWidthMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("scaling_factor",1e-6,"To scale the units of the simulation.");
  params.addRequiredCoupledVar("coupled_temperature","This temperature is used to calculate diffusivity values.");
  params.addParam<FunctionName>("n_flux", "0", "Function for the neutron flux.");
  params.addParam<PostprocessorName>("transition_count", 0.0, "Transition count postprocessor.");
  params.addParam<PostprocessorName>("flux_time_offset",0,"Postprocessor providing the time "
				     "to use with the neutron flux function.");
  params.addParam<PostprocessorName>("transferred_delta_old", "Postprocessor providing the old amorphous width after " 
				     "transition.");
  params.addParam<std::vector<Real>>("SPP_sizes","The different SPP diameters, in nm.");
  params.addParam<std::vector<Real>>("SPP_number_fractions","The different SPP number fractions.");
  params.addParam<PostprocessorName>("s1_PP", "Postprocessor remaining_iron value after " 
				     "transition.");
  params.addParam<PostprocessorName>("s2_PP", "Postprocessor remaining_iron value after " 
				     "transition.");
  params.addParam<PostprocessorName>("s3_PP", "Postprocessor remaining_iron value after " 
				     "transition.");
  params.addParam<PostprocessorName>("t1_PP", "Postprocessor amorphous_t1 value after " 
				     "transition.");
  params.addParam<PostprocessorName>("t2_PP", "Postprocessor amorphous_t2 value after " 
				     "transition.");
  params.addParam<PostprocessorName>("t3_PP", "Postprocessor amorphous_t3 value after " 
				     "transition.");

  return params;
}

AmorphousWidthMaterial::AmorphousWidthMaterial(const InputParameters & parameters) :
    Material(parameters),

    _amorphous_width(declareProperty<Real>("amorphous_width")),
    _amorphous_width_old(getMaterialPropertyOld<Real>("amorphous_width")),
    _net_iron_change(declareProperty<Real>("net_iron_change")),
    _overall_iron_change(declareProperty<Real>("overall_iron_change")),
    _overall_iron_change_old(getMaterialPropertyOld<Real>("overall_iron_change")),
    _iron_release_density(declareProperty<Real>("iron_release_density")),
    _SPP_Zr_density(declareProperty<Real>("SPP_Zr_density")),
    _avg_SPP_diameter(declareProperty<Real>("avg_SPP_diameter")),
    _scaling_factor(getParam<Real>("scaling_factor")),
    _zr_molar_density(getMaterialProperty<Real>("zr_molar_density")),
    _coupled_temperature(coupledValue("coupled_temperature")),
    _n_flux(getFunction("n_flux")),
    _transition_count(getPostprocessorValue("transition_count")),
    _time_offset(getPostprocessorValue("flux_time_offset")),
    _transferred_delta_old(getPostprocessorValue("transferred_delta_old")),
    _SPP_sizes(getParam<std::vector<Real>>("SPP_sizes")),
    _SPP_number_fractions(getParam<std::vector<Real>>("SPP_number_fractions")),
    _amorphous_fraction(declareProperty<Real>("amorphous_fraction")),
    _new_iron_release(declareProperty<Real>("new_iron_release")),
    _s1_iron(declareProperty<Real>("s1_iron")),
    _s2_iron(declareProperty<Real>("s2_iron")),
    _s3_iron(declareProperty<Real>("s3_iron")),
    _s1_iron_old(getMaterialPropertyOld<Real>("s1_iron")),
    _s2_iron_old(getMaterialPropertyOld<Real>("s2_iron")),
    _s3_iron_old(getMaterialPropertyOld<Real>("s3_iron")),
    _amorphous_t1(declareProperty<Real>("amorphous_t1")),
    _amorphous_t2(declareProperty<Real>("amorphous_t2")),
    _amorphous_t3(declareProperty<Real>("amorphous_t3")),
    _amorphous_t1_old(getMaterialPropertyOld<Real>("amorphous_t1")),
    _amorphous_t2_old(getMaterialPropertyOld<Real>("amorphous_t2")),
    _amorphous_t3_old(getMaterialPropertyOld<Real>("amorphous_t3")),
    _s1_PP(getPostprocessorValue("s1_PP")),
    _s2_PP(getPostprocessorValue("s2_PP")),
    _s3_PP(getPostprocessorValue("s3_PP")),
    _t1_PP(getPostprocessorValue("t1_PP")),
    _t2_PP(getPostprocessorValue("t2_PP")),
    _t3_PP(getPostprocessorValue("t3_PP"))

{}

void
AmorphousWidthMaterial::initQpStatefulProperties()
{
  computeQpProperties();
}

void
AmorphousWidthMaterial::initialSetup()
{
 int vector_length = _SPP_sizes.size();

 for (unsigned int i = 0; i < vector_length; ++i)
 {
	_remaining_iron.push_back(0.);
 }

}

void AmorphousWidthMaterial::computeQpProperties()
{
  // Constants used in the the Taylor et al. (1999) model:
  Real flux_n = _n_flux.value((_t + _time_offset), _q_point[_qp]); // n/cm^2-s
  Real beta = 2.37e-3; // 1/nm
  Real D = 2.34e-20; // nm-cm^2/n
  Real activation_energy = 11600.; // K
  Real k_phi = 9.6e-22; // cm^2/n
  Real k_chi = 27.; // 1/s

  // Compute alpha_0 for this interval (time step) n:
  Real alpha_0_n = k_phi * flux_n / (k_chi * exp(-activation_energy / _coupled_temperature[_qp]) + k_phi * flux_n);

  Real t_n = _dt;
  
  // Compute "delta" for the current time step, with an exception if it's right after a transition:
  if ((_transition_count > 0) && (_t_step < 3)) // after transition on the first step, use the PP value
  {
	_amorphous_width[_qp] = alpha_0_n / beta * (1. - exp(-beta*D*flux_n*t_n)) +
			 _transferred_delta_old * (exp(-beta*D*flux_n*t_n));
  }
  else
  {
  	_amorphous_width[_qp] = alpha_0_n / beta * (1. - exp(-beta*D*flux_n*t_n)) +
			 _amorphous_width_old[_qp] * (exp(-beta*D*flux_n*t_n));
  }

  Real delta_n = _amorphous_width[_qp];
  Real delta_n_old = _amorphous_width_old[_qp];


  // Assumed/estimated parameters for the model:
  Real initial_FeCr = 2.0; // based on alloy composition
  Real amorphous_FeCr = 0.39; // based on average of literature measurements
  

  // Calculate SPP atom densities:
  Real constant_zr_molar_density = (6.52) / 91.224; // to replace calling _zr_molar_density[_qp] below:
  long double Zr_atom_density = constant_zr_molar_density * (6.02e23); // Zr atoms/cm^3
  _SPP_Zr_density[_qp] = Zr_atom_density;
  long double initial_Fe_atom_density = Zr_atom_density / 9. * 2. * initial_FeCr; // Fe atoms/cm^3
  long double initial_Cr_atom_density = initial_Fe_atom_density / initial_FeCr; // Cr atoms/cm^3
  
  long double amorphous_Fe_atom_density = amorphous_FeCr * initial_Cr_atom_density; // Fe atoms/cm^3

  // This is the estimate for the number of iron atoms 
  // released from the state of the SPP at beginning of
  // life to the amorphized state:
  long double Fe_release_density = initial_Fe_atom_density - amorphous_Fe_atom_density; // Fe atoms/cm^3
  Fe_release_density /= 1.0e21; // Fe atoms/nm^3
  _iron_release_density[_qp] = Fe_release_density;

  // Need to determine the SPP density, which conserves Fe in the SPPs:
  long double bulk_average_Fe_density = 0.047444071; // [Fe/nm^3] using room temp Zr density and 0.18 wt% Fe to get Fe at%=0.1103

  // Average SPP volume:
  long double SPP_average_volume = 0.0;

  int num_SPPs = _SPP_sizes.size();
  for (unsigned int i = 0; i < num_SPPs; ++i)
  	SPP_average_volume += std::pow(_SPP_sizes[i]/2,3) * 4. / 3. * 3.1415926535 * _SPP_number_fractions[i];
  
  // Solve for the average SPP diameter:
  long double avg_diameter_SPP = 2. * std::pow((SPP_average_volume / 4. * 3. / 3.1415926535),(1./3.));
  _avg_SPP_diameter[_qp] = avg_diameter_SPP;

  // Iron in an SPP is the average SPP's volume times the density of Fe in the SPP available for release:
  Real SPP_max_iron_contribution = Fe_release_density; // Fe atoms/nm^3
  Real iron_in_SPP = SPP_max_iron_contribution * SPP_average_volume; // Fe/SPP

  // Solve for the required effective SPP number density to conserve
  // iron that can be released during amorphization:
  Real SPP_number_density = bulk_average_Fe_density / iron_in_SPP; // SPP/nm^3

  Real volume_change = 0.0;

  // Compute the fraction of SPPs that are fully amorphized:
  Real function_fraction = 0.;
  for (unsigned int i = 0; i < num_SPPs; ++i)
  	function_fraction += computeAmorphousBool(_SPP_sizes[i],delta_n) * _SPP_number_fractions[i];

  _amorphous_fraction[_qp] = function_fraction;


 int vector_length = _SPP_sizes.size();
 std::vector<Real> new_remaining_iron;

 for (unsigned int i = 0; i < vector_length; ++i)
 {
	new_remaining_iron.push_back(0.);
 }


  Real amorphous_Fe = amorphous_Fe_atom_density / 1.0e21; // convert from Fe/cm^3 to Fe/nm^3
  Real crystalline_Fe = initial_Fe_atom_density / 1.0e21; // convert from Fe/cm^3 to Fe/nm^3

  Real iron_atoms_released = 0.;
  bool fully_amorphous_bool = false;

  // Loop over all SPP sizes and determine 
  // (1) fully amorphous or not
  // (2) if not fully amorphous, how much iron to release
  // (3) if fully amorphous, determine the lump iron amount to release 
  //	(if it wasn't fully amorphous on the previous time step)

  // Set the proper amorphous time:
  if ((_t_step < 2) && (_transition_count < 1)) _amorphous_t1[_qp] = 1e10; // set the very first value
  else if ((_t_step < 3) && (_transition_count > 0)) _amorphous_t1[_qp] = _t1_PP; // use the PP for first step value
  else if (_amorphous_t1_old[_qp] < 1e9) _amorphous_t1[_qp] = _amorphous_t1_old[_qp]; // keep the value set once an SPP size fully amorphizes
  else _amorphous_t1[_qp] = 1e10;

  // Check if the particle is fully amorphous:
  if (computeAmorphousBool(_SPP_sizes[0],delta_n) > 0) fully_amorphous_bool = true;

  if ((fully_amorphous_bool) && ((_t + _time_offset) > _amorphous_t1[_qp])) // SPP is fully amorphous and has been for >1 step
  {
	// Implement the _s1_PP coupling logic here for after transition
	if ((_t_step < 3) && (_transition_count > 0)) new_remaining_iron[0] = _s1_PP;
	//else if (_t_step < 2) new_remaining_iron[0] = 0.;
	else new_remaining_iron[0] = _s1_iron_old[_qp];

	// Release iron with the x^2 = 4Dt diffusion approximation method:

	// Compute the rate at which iron leaves the SPP (approximately):
	//Real diffusion_time = (225./2.)*(225./2.) / (4. * computeDiffusivity(flux_n));
	Real diffusion_time = (_SPP_sizes[0]/2.)*(_SPP_sizes[0]/2.) / (4. * computeDiffusivity(flux_n));
	Real iron_released = 0.;

	if (diffusion_time < _dt)
	{
		// Release all of the iron if it needs less than the time step to diffuse:
		iron_released = new_remaining_iron[0];
	}
	else
	{
		// Release the iron linearly:
		iron_released = (new_remaining_iron[0] / diffusion_time) * _dt;
	}

	// Release some iron:
	iron_atoms_released += iron_released;

	// Update the amount of iron remaining in the SPP:
	new_remaining_iron[0] -= iron_released;

	if (new_remaining_iron[0] < 0.) new_remaining_iron[0] = 0.;

  }
  else if (fully_amorphous_bool)
  {
	// call integral function to compute the amount of remaining iron:
	new_remaining_iron[0] = computeIronIntegral(amorphous_Fe,crystalline_Fe,
					0., (_SPP_sizes[0]/2.)) * _SPP_number_fractions[0];

  	// set the value of amorphous time:
	_amorphous_t1[_qp] = _t + _time_offset;

	// Release iron with the x^2 = 4Dt diffusion approximation method:

	// Compute the rate at which iron leaves the SPP (approximately):
	Real diffusion_time = (_SPP_sizes[0]/2.)*(_SPP_sizes[0]/2.) / (4. * computeDiffusivity(flux_n));
	Real iron_released = 0.;

	if (diffusion_time < _dt)
	{
		// Release all of the iron if it needs less than the time step to diffuse:
		iron_released = new_remaining_iron[0];
	}
	else
	{
		// Release the iron linearly:
		iron_released = (new_remaining_iron[0] / diffusion_time) * _dt;
	}

	// Release some iron:
	iron_atoms_released += iron_released;

	// Update the amount of iron remaining in the SPP:
	new_remaining_iron[0] -= iron_released;

	if (new_remaining_iron[0] < 0.) new_remaining_iron[0] = 0.;

  }
  else 
  {
	// The SPP is not fully amorphous, so iron is incrementally released
	// due to a change in the width of the amorphous zone:

	iron_atoms_released += computeIntegralIronRelease(_SPP_sizes[0], delta_n, 
				delta_n_old, crystalline_Fe, amorphous_Fe) * _SPP_number_fractions[0];
  }

  // Reset fully_amorphous_bool before the next particle size:
  fully_amorphous_bool = false;

// 2nd SPP size:
  // Set the proper amorphous time:
  if ((_t_step < 2) && (_transition_count < 1)) _amorphous_t2[_qp] = 1e10; // set the very first value
  else if ((_t_step < 3) && (_transition_count > 0)) _amorphous_t2[_qp] = _t2_PP; // use the PP for first step value
  else if (_amorphous_t2_old[_qp] < 1e9) _amorphous_t2[_qp] = _amorphous_t2_old[_qp]; // keep the value set once an SPP size fully amorphizes
  else _amorphous_t2[_qp] = 1e10;



  // Check if the particle is fully amorphous:
  if (computeAmorphousBool(_SPP_sizes[1],delta_n) > 0) fully_amorphous_bool = true;

  if ((fully_amorphous_bool) && ((_t + _time_offset) > _amorphous_t2[_qp])) // SPP is fully amorphous and has been for >1 step
  {
	// Implement the _s2_PP coupling logic here for after transition
	if ((_t_step < 3) && (_transition_count > 0)) new_remaining_iron[1] = _s2_PP;
	//else if (_t_step < 2) new_remaining_iron[1] = 0.;
	else new_remaining_iron[1] = _s2_iron_old[_qp];

	// Release iron with the x^2 = 4Dt diffusion approximation method:

	// Compute the rate at which iron leaves the SPP (approximately):
	Real diffusion_time = (_SPP_sizes[1]/2.)*(_SPP_sizes[1]/2.) / (4. * computeDiffusivity(flux_n));
	Real iron_released = 0.;

	if (diffusion_time < _dt)
	{
		// Release all of the iron if it needs less than the time step to diffuse:
		iron_released = new_remaining_iron[1];
	}
	else
	{
		// Release the iron linearly:
		iron_released = (new_remaining_iron[1] / diffusion_time) * _dt;
	}

	// Release some iron:
	iron_atoms_released += iron_released;

	// Update the amount of iron remaining in the SPP:
	new_remaining_iron[1] -= iron_released;

	if (new_remaining_iron[1] < 0.) new_remaining_iron[1] = 0.;

  }
  else if (fully_amorphous_bool)
  {
	// call integral function to compute the amount of remaining iron:
	new_remaining_iron[1] = computeIronIntegral(amorphous_Fe,crystalline_Fe,
					0., (_SPP_sizes[1]/2.)) * _SPP_number_fractions[1];

  	// set the value of amorphous time:
	_amorphous_t2[_qp] = _t + _time_offset;

	// Release iron with the x^2 = 4Dt diffusion approximation method:

	// Compute the rate at which iron leaves the SPP (approximately):
	Real diffusion_time = (_SPP_sizes[1]/2.)*(_SPP_sizes[1]/2.) / (4. * computeDiffusivity(flux_n));
	Real iron_released = 0.;

	if (diffusion_time < _dt)
	{
		// Release all of the iron if it needs less than the time step to diffuse:
		iron_released = new_remaining_iron[1];
	}
	else
	{
		// Release the iron linearly:
		iron_released = (new_remaining_iron[1] / diffusion_time) * _dt;
	}

	// Release some iron:
	iron_atoms_released += iron_released;

	// Update the amount of iron remaining in the SPP:
	new_remaining_iron[1] -= iron_released;

	if (new_remaining_iron[1] < 0.) new_remaining_iron[1] = 0.;

  }
  else 
  {
	// The SPP is not fully amorphous, so iron is incrementally released
	// due to a change in the width of the amorphous zone:

	iron_atoms_released += computeIntegralIronRelease(_SPP_sizes[1], delta_n, 
				delta_n_old, crystalline_Fe, amorphous_Fe) * _SPP_number_fractions[1];
  }

  // Reset fully_amorphous_bool before the next particle size:
  fully_amorphous_bool = false;

// 3rd SPP size:
  // Set the proper amorphous time:
  if ((_t_step < 2) && (_transition_count < 1)) _amorphous_t3[_qp] = 1e10; // set the very first value
  else if ((_t_step < 3) && (_transition_count > 0)) _amorphous_t3[_qp] = _t3_PP; // use the PP for first step value
  else if (_amorphous_t3_old[_qp] < 1e9) _amorphous_t3[_qp] = _amorphous_t3_old[_qp]; // keep the value set once an SPP size fully amorphizes
  else _amorphous_t3[_qp] = 1e10;



  // Check if the particle is fully amorphous:
  if (computeAmorphousBool(_SPP_sizes[2],delta_n) > 0) fully_amorphous_bool = true;

  if ((fully_amorphous_bool) && ((_t + _time_offset) > _amorphous_t3[_qp])) // SPP is fully amorphous and has been for >1 step
  {
	// Implement the _s3_PP coupling logic here for after transition
	if ((_t_step < 3) && (_transition_count > 0)) new_remaining_iron[2] = _s3_PP;
	else new_remaining_iron[2] = _s3_iron_old[_qp];

	// Release iron with the x^2 = 4Dt diffusion approximation method:

	// Compute the rate at which iron leaves the SPP (approximately):
	Real diffusion_time = (_SPP_sizes[2]/2.)*(_SPP_sizes[2]/2.) / (4. * computeDiffusivity(flux_n));
	Real iron_released = 0.;

	if (diffusion_time < _dt)
	{
		// Release all of the iron if it needs less than the time step to diffuse:
		iron_released = new_remaining_iron[2];
	}
	else
	{
		// Release the iron linearly:
		iron_released = (new_remaining_iron[2] / diffusion_time) * _dt;
	}

	// Release some iron:
	iron_atoms_released += iron_released;

	// Update the amount of iron remaining in the SPP:
	new_remaining_iron[2] -= iron_released;

	if (new_remaining_iron[2] < 0.) new_remaining_iron[2] = 0.;

  }
  else if (fully_amorphous_bool)
  {
	// call integral function to compute the amount of remaining iron:
	new_remaining_iron[2] = computeIronIntegral(amorphous_Fe,crystalline_Fe,
					0., (_SPP_sizes[2]/2.)) * _SPP_number_fractions[2];

  	// set the value of amorphous time:
	_amorphous_t3[_qp] = _t + _time_offset;

	// Release iron with the x^2 = 4Dt diffusion approximation method:

	// Compute the rate at which iron leaves the SPP (approximately):
	Real diffusion_time = (_SPP_sizes[2]/2.)*(_SPP_sizes[2]/2.) / (4. * computeDiffusivity(flux_n));
	Real iron_released = 0.;

	if (diffusion_time < _dt)
	{
		// Release all of the iron if it needs less than the time step to diffuse:
		iron_released = new_remaining_iron[2];
	}
	else
	{
		// Release the iron linearly:
		iron_released = (new_remaining_iron[2] / diffusion_time) * _dt;
	}

	// Release some iron:
	iron_atoms_released += iron_released;

	// Update the amount of iron remaining in the SPP:
	new_remaining_iron[2] -= iron_released;

	if (new_remaining_iron[2] < 0.) new_remaining_iron[2] = 0.;

  }
  else 
  {
	// The SPP is not fully amorphous, so iron is incrementally released
	// due to a change in the width of the amorphous zone:

	iron_atoms_released += computeIntegralIronRelease(_SPP_sizes[2], delta_n, 
				delta_n_old, crystalline_Fe, amorphous_Fe) * _SPP_number_fractions[2];
  }

  // Reset fully_amorphous_bool before the next particle size:
  fully_amorphous_bool = false;
  
  _new_iron_release[_qp] = iron_atoms_released * SPP_number_density / bulk_average_Fe_density;

  if (_new_iron_release[_qp] < 0) _new_iron_release[_qp] = 0;

  if (_t < 0.01) _new_iron_release[_qp] = 0;

  _net_iron_change[_qp] = _new_iron_release[_qp];



  // Update fully amorphous SPP iron contents using the new_remaining_iron vector:
  _s1_iron[_qp] = new_remaining_iron[0];

  _s2_iron[_qp] = new_remaining_iron[1];

  _s3_iron[_qp] = new_remaining_iron[2];

}

Real
AmorphousWidthMaterial::computeWeightedVolumeChange(const Real & diameter, const Real & delta,
		const Real & delta_old, const Real & number_fraction)
{
  long double volume = 0.;
  long double pi = 3.1415926535;

  // Compute the SPP radii at the current and old time steps:
  long double r1 = (diameter/2.) - delta;
  long double r2 = (diameter/2.) - delta_old;
  // r2 is the old radius value and should be larger than r1.

  // Check for negative values:
  if (r1 < 0) r1 = 0.;
  if (r2 < 0) r2 = 0.;
  
  // Compute different in volumes for r1 and r2:
  volume = (4./3.*pi*r2*r2*r2) - (4./3.*pi*r1*r1*r1);

  // Can't have negative volume change
  // since not treating reprecipitation/recrystallization
  if (volume < 0.) volume = 0.; 

  // Weight the volume change by particle number fraction:
  volume *= number_fraction;

  return volume;	
}

Real
AmorphousWidthMaterial::computeAmorphousBool(const Real & diameter, const Real & delta)
{

  // Compute the SPP radii at the current and old time steps:
  Real fraction = 0.;

  // Compare amorphous rim width to SPP radius:
  if (delta > (diameter / 2.)) fraction = 1.;

  return fraction;	
}

Real
AmorphousWidthMaterial::computeIntegralIronRelease(const Real & diameter, const Real & delta,
		const Real & delta_old, const Real & crystal_Fe_density, 
		const Real & amorphous_Fe_density)
{

  // Determine the crystalline radii using the amorphous width values:
  long double r_c_old = (diameter / 2.) - delta_old;
  if (r_c_old < 0) r_c_old = 0;

  long double r_c = (diameter / 2.) - delta;
  if (r_c < 0) r_c = 0;

  // Amorphous radii are simply the outer radius of the SPP:
  Real r_a_old = (diameter / 2.);
  Real r_a = (diameter / 2.);

  // Call integral function to determine the amount of iron in the SPP during
  // the previous time step and the current time step:
  long double iron_content_old = computeIronIntegral(amorphous_Fe_density,crystal_Fe_density,
				r_c_old,r_a_old);

  long double iron_content = computeIronIntegral(amorphous_Fe_density,crystal_Fe_density,
				r_c,r_a);

  long double iron_loss = iron_content_old - iron_content;

  return iron_loss;

}

Real
AmorphousWidthMaterial::computeIronIntegral(const Real & rho_a, const Real & rho_c,
		const Real & r_c, const Real & r_a)
{
  // Calculate the slope, m:
  Real m = (rho_a - rho_c) / (r_a - r_c);

  // Evaluate the integral of iron in the SPP, term by term:
  Real value = (rho_c / 3 * std::pow(r_c,3)) +
	       (m / 4 * std::pow(r_a,4)) +
	       (std::pow(r_a,3) / 3 * (rho_c - m * r_c)) -
	       (m / 4 * std::pow(r_c,4)) -
	       (std::pow(r_c,3) / 3 * (rho_c - m * r_c));

  // Include the factor of 4*pi for spherical coordinate integration:
  value = value * 4 * 3.1415926535;

  return value;
}

Real
AmorphousWidthMaterial::computeDiffusivity(const Real & flux)
{
  // Diffusivity is in m^2/s, and flux is in n/cm^2-s

  Real diffusivity = (5.23077e-36)*flux - (3.92308e-23);

  diffusivity *= 1.e18; // Convert to nm^2/s

  return diffusivity;
}
