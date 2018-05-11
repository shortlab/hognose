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

#include "MobilityforConcentrationPF.h"


template<>
InputParameters validParams<MobilityforConcentrationPF>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredCoupledVar("Oxygen_conc","This concentration will be used in the calculation of the diffusivity.");
  params.addRequiredCoupledVar("phase","The phase (oxide = 1, metal = 0) of the element.");
  params.addRequiredCoupledVar("coupled_temperature","This temperature is used to calculate diffusivity values.");
  params.addParam<Real>("scaling_factor", 1, "The scaling factor to use throughout the simulation");
  params.addParam<Real>("charge_value", 1, "The number of elementary charges to use with oxygen density.");
  params.addParam<Real>("delta_c",0.013333333333333333,"The concentration offset for the oxygen vacancy calculation.");
  params.addParam<Real>("stoich_fraction",0.0075,"The fraction of off-stoichiometry at the O/M interface, as a fraction (not %).");
  params.addRequiredParam<Real>("Oxide_stoichiometry","The user-specified oxygen diffusivity in the oxide that is used in splines to get D_oxide, unless the oxide diffusivity is specified");
  params.addRequiredParam<Real>("oxide_baseline","The baseline value for oxide diffusivity.");
  MooseEnum energy_units("J eV");
  params.addRequiredParam<MooseEnum>("energy_units",energy_units,"Determines the scaling of the curvature_value_k.");
  params.addParam<Real>("constant_temp",633,"The temperature to use in the diffusivity calculations.");
  params.addCoupledVar("oxide_phase","The structure (protective vs. O-transparent).");
  params.addParam<Real>("curvature_value_k",1e5,"The value of the curvature, used to converte diffusivity to mobility.");
  params.addParam<Real>("D1",1e-17,"D_O in the oxide at T1.");
  params.addParam<Real>("T1",633,"T1 for the D_O calculation.");
  params.addParam<Real>("D2",0.25e-17,"D_O in the oxide at T2.");
  params.addParam<Real>("T2",603,"T2 for the D_O calculation.");  
  params.addParam<Real>("doping_max_factor",1,"The maximum multiplier for the oxide diffusivity prefactor when space charge is fully compensated by doping.");  
  params.addParam<Real>("charge_constant_initial",100,"The initial or maximum charge density value.");  
  params.addCoupledVar("charge_density","The effective charge density variable, rho.");
  params.addParam<Real>("doping_effect_on",0,"Turn on to include doping effects on the oxide diffusivity prefactor.");
  params.addParam<Real>("doping_power",1,"The exponent for determing the oxygen diffusivity increase as a function of rho.");
  params.addParam<PostprocessorName>("transition_count", 0.0, "Transition count postprocessor.");
  return params;
}

MobilityforConcentrationPF::MobilityforConcentrationPF(const InputParameters & parameters) :
    Material(parameters),

    _h_value(declareProperty<Real>("h_value")),
    _diffusivity(declareProperty<Real>("diffusivity")),
    _diffusivity_out(declareProperty<Real>("diffusivity_out")),
    _zr_conductivity(declareProperty<Real>("zr_conductivity")),
    _zr_mass_density(declareProperty<Real>("zr_mass_density")),
    _zr_molar_density(declareProperty<Real>("zr_molar_density")),
    _zr_specific_heat(declareProperty<Real>("zr_specific_heat")),
    _oxygen_density(declareProperty<Real>("oxygen_density")),
    _oxygen_vacancy(declareProperty<Real>("oxygen_vacancy")),
    _o_ion_mobility(declareProperty<Real>("o_ion_mobility")),
    _Oxygen_conc(coupledValue("Oxygen_conc")),
    _phase(coupledValue("phase")),
    _coupled_temperature(coupledValue("coupled_temperature")),
    _scaling_factor(getParam<Real>("scaling_factor")),
    _charge_value(getParam<Real>("charge_value")),
    _delta_c(getParam<Real>("delta_c")),
    _stoich_fraction(getParam<Real>("stoich_fraction")),
    _Oxide_stoich(getParam<Real>("Oxide_stoichiometry")),
    _oxide_baseline(getParam<Real>("oxide_baseline")),
    _total_diffusivity_factor(getMaterialProperty<Real>("total_diffusivity_factor")),
    _energy_units(getParam<MooseEnum>("energy_units")),
    _constant_temp(getParam<Real>("constant_temp")),
    _oxide_phase(coupledValue("oxide_phase")),
    _curvature_value_k(getParam<Real>("curvature_value_k")),
    _D1(getParam<Real>("D1")),
    _T1(getParam<Real>("T1")),
    _D2(getParam<Real>("D2")),
    _T2(getParam<Real>("T2")),
    _doping_max_factor(getParam<Real>("doping_max_factor")),
    _charge_constant_initial(getParam<Real>("charge_constant_initial")),
    _charge_density(coupledValue("charge_density")),
    _doping_effect_on(getParam<Real>("doping_effect_on")),
    _doping_factor(declareProperty<Real>("doping_factor")),
    _doping_power(getParam<Real>("doping_power")),
    _transition_count(getPostprocessorValue("transition_count"))

{}

void MobilityforConcentrationPF::computeQpProperties()
{
  // Compute the doping factor:
  _doping_factor[_qp] = 1.;

  if (_doping_effect_on > 0.5)
  {
	_doping_factor[_qp] = 1 + ((_doping_max_factor - 1) * 
				std::pow((_charge_constant_initial - _charge_density[_qp]),_doping_power) / 
				std::pow(_charge_constant_initial,_doping_power));

	if (_phase[_qp] < 0.99) _doping_factor[_qp] = 1.;
	if (_transition_count < 1) _doping_factor[_qp] = 1.;
  }

  // Calculate diffusivity in the oxide:
  Real D_oxide = computeOxideDiffusivity(_Oxygen_conc[_qp], _coupled_temperature[_qp], _D1*_doping_factor[_qp], _T1, _D2*_doping_factor[_qp], _T2);

  // Calculate diffusivity in the metal (up to saturation, where it defaults to ZrO_0.5 value):
  Real D_metal = computeMetalSplineDiffusivity(_Oxygen_conc[_qp], _coupled_temperature[_qp]);

  // Calculate the interpolation function, h(eta):
  Real h_value = computeHFunction(_phase[_qp]);

  _h_value[_qp] = h_value;

  // Scale diffusivity to the proper units:
  D_oxide /= std::pow(_scaling_factor, 2);
  D_metal /= std::pow(_scaling_factor, 2);

  // Scale curvature value (k) into the proper length and energy units:
  Real k_value = _curvature_value_k * std::pow(_scaling_factor, 3);
  if (_energy_units == "eV")
  {
	k_value = k_value / (1.602e-19); // convert from J to eV
  }
  // if (energy_units == "J") then there is no conversion necessary.  

  // Calculate oxygen mobility using the diffusivity:
  _o_ion_mobility[_qp] = 2 * D_oxide / (_coupled_temperature[_qp] * 8.6173324e-5); 

  // Modify the diffusivity in the OXIDE ONLY for various effects (DiffusivityFactorMaterial.C/.h):
  D_oxide *= _total_diffusivity_factor[_qp];

  // Average the metal and oxide values using the interpolation function:
  _diffusivity[_qp] = h_value * D_oxide / k_value + (1 - h_value) * D_metal / k_value;

  // Average the metal and oxide values without /k_value to return diffusivity,
  // not mobility:
  _diffusivity_out[_qp] = h_value * D_oxide + (1 - h_value) * D_metal;

  computeDebugOutput(); // std::cout statements if the values are wonky


/////////////////////////////////////////////////////////
/////   Calculate additional material properties:   /////
/////////////////////////////////////////////////////////

  Real mP; // metal property value
  Real oxP; // oxide property value

///////////////////////////////////////////////////////////////////////////////
                     // PHASE FIELD THERMAL CONDUCTIVITY

  // We will compute the diffusivity based on the temperature dependent equation from
  // Fink and Leibowitz ("Thermal conductivity of zirconium")
  // J. K. Fink and L. Leibowitz. J. Nucl. Mater., 226:44–50, 1995.
  mP = 8.8527
    + (0.0070820*_coupled_temperature[_qp])
    + (0.0000025329*(_coupled_temperature[_qp]*_coupled_temperature[_qp]))
    + (2991.8/pow(_coupled_temperature[_qp],3));

  //mP = 14.35; // above correlation evaluated at 633 K

  // Dua1980 gives the thermal conductivity of bulk zirconium oxide as 1.96 W/m-K
  // A. K. Dua, V. C. George, and R. P. Agarwala. Thin Solid Films, 69:L1–L3, 1980.
  oxP = 1.96; // W/m-K

  // Function call to average the above values:
  _zr_conductivity[_qp] = h_value*oxP + (1 - h_value)*mP;




///////////////////////////////////////////////////////////////////////////////
                     // PHASE FIELD DENSITY

  // Zr density (http://www.hbcpnetbase.com/): 6.52 g/cm^3
  mP = (6.52 - (3.9351e-4) * (_coupled_temperature[_qp] - 293.0)) * 1000.0;

  // ZrO2 density (wikipedia): 5.68 g/cm^3 (http://www.hbcpnetbase.com/)
  oxP = 5.68 * 1000.0;

  // Function call to average the above values:
  _zr_mass_density[_qp] = h_value*oxP + (1 - h_value)*mP;





///////////////////////////////////////////////////////////////////////////////
                     // OXYGEN DENSITY/OXYGEN VACANCIES

  // Zr density (http://www.hbcpnetbase.com/): 6.52 g/cm^3
  mP = (6.52 - (3.9351e-4) * (_coupled_temperature[_qp] - 293.0)) / 91.224 * (6.02e23);
	// Atomic weight (91.224) from wikipedia.

  // ZrO2 density (wikipedia): 5.68 g/cm^3 (http://www.hbcpnetbase.com/)
  oxP = 5.68 / 123.218 * (6.02e23); // molecular weight (123.218) from wikipedia.

  // Function call to average the above values:
  _oxygen_density[_qp] = h_value*oxP + (1 - h_value)*mP;

  // Currently in particles/cm^3 still, so convert to particles/m^3:
  _oxygen_density[_qp] *= 1e6;

  // Include the charge:
  _oxygen_density[_qp] *= _charge_value * (_Oxygen_conc[_qp] / (1 - _Oxygen_conc[_qp]));

  // Compute oxygen vacancies everywhere; restriction to oxide only will take place in
  // ChargeDensityMaterial.
  double theta = (_Oxygen_conc[_qp] - _delta_c) / (1.0 - (_Oxygen_conc[_qp] - _delta_c));

  _oxygen_vacancy[_qp] = _stoich_fraction * _oxygen_density[_qp] * (2.0 - theta);

  if (_oxygen_vacancy[_qp] < 0.0) _oxygen_vacancy[_qp] = 0.0;



///////////////////////////////////////////////////////////////////////////////
                     // PHASE FIELD MOLAR DENSITY

  _zr_molar_density[_qp] = (6.52 - (3.9351e-4) * (_coupled_temperature[_qp] - 293.0))
	* 1.0e6 / 91.224; // computes density in g/cm^3, then converts to g/m^3, then mol/m^3
  	// based on a linear interpolation of density from room temperature to the melting point,
	// using data from the CRC Handbook 2015 (internet version, pages 4-130 and 12-207).





///////////////////////////////////////////////////////////////////////////////
                     // PHASE FIELD SPECIFIC HEAT

  // Zr c_p = 0.278 J/g-K (http://www.hbcpnetbase.com/)
  mP = 278.0; // J/kg-K

  oxP = 592.0; // J/kg-K (Source: Swain 1986).

  // Function call to average the above values:
  _zr_specific_heat[_qp] = h_value*oxP + (1 - h_value)*mP;



///////////////////////////////////////////////////////////////////////////////

// Finally apply the correct scaling so material properties are returned with scaled units

  _zr_mass_density[_qp] *= std::pow(_scaling_factor, 3); 
	// Scale the volumetric density three times: kg/m^3

  _zr_specific_heat[_qp] /= std::pow(_scaling_factor, 2);
  	// Scale twice: J/kg-K = kg-m/s^2 * m * 1/kg-K = m^2/s^2-K

  _zr_conductivity[_qp] /= std::pow(_scaling_factor, 1); 
  	// Scale inverse once for m (W/mK = kg*m/s^2 * m/s * 1/mK = kg*m/s^3-K)

  _oxygen_density[_qp] *= std::pow(_scaling_factor, 3);
	// Scale the volumetric density three times: #/m^3

  _oxygen_vacancy[_qp] *= std::pow(_scaling_factor, 3);
	// Scale the volumetric density three times: #/m^3

  _zr_molar_density[_qp] *= std::pow(_scaling_factor, 3);
	// Scale thrice for a 1/,^3

///////////////////////////////////////////////////

}

Real
MobilityforConcentrationPF::computeOxideDiffusivity(const Real & conc, const Real & temp, const Real & D1, const Real & T1, const Real & D2, const Real & T2)
{
  // Diffusivity in the oxide:
  double Doxide;

  double kB = 8.6173324e-5;

  // D1/T1-D2/T2 method of D_O temperature dependence:
  double Eaoxide = 8.6173324e-5 * T1 * T2 / (T2 - T1) * log(D2 / D1);
  double D0oxide = D1 * exp(Eaoxide / (kB * T1));

  Doxide=D0oxide*exp(-Eaoxide/(kB*temp));

  return Doxide;
}

Real
MobilityforConcentrationPF::computeMetalSplineDiffusivity(const Real & conc, const Real & temp)
{
  double oxygen_mole_fraction = conc; // [atom%] = [mole%]

  if (oxygen_mole_fraction > 0.33333)
  {
  	oxygen_mole_fraction = 0.33333;
  }

  if (oxygen_mole_fraction < 0) oxygen_mole_fraction = 0;

// Declare variable used for spline coefficients:
  double a;
  double b;
  double c;
  double d;
  double aa;
  double bb;
  double cc;
  double dd;
  double diffusivity_600K;
  double diffusivity_800K;

// Oxygen diffusivity splines:
	  // The piecewise functions defined below are based on data provided in
	  // a pdf from Anton Van der Ven (University of Michigan). 

{
          // The piecewise function for the diffusion coefficient at 600 K: 
	  if (oxygen_mole_fraction <= 0.02468) // 0.0253
	  {
		if (oxygen_mole_fraction < 0)
		{
			a=0;
			b=0;
			c=0;
			d=4.25e-23;
		}
		else
		{
			a = 6.1616850e-19;
			b = 2.9786378E-21;
			c = -1.45e-21;
			d = 4.25e-23;
		}
	  }
	  else if ((0.02468 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.09116)) //0.0253, 0.1003
	  {
	        a = -5.1800296e-21;
		b = 1.2803909e-21;
		c = -1.7091172e-22;
		d = 2.1288388e-23;
	  }
	  else if ((0.09116 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.15096)) // 0.1003, 0.1778
	  {
		a = -5.7767186e-21;
		b = 3.2108427e-21;
		c = -5.401521e-22;
		d = 3.9504760e-23;
	  }
	  else if ((0.15096 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.17232)) // 0.1778, 0.2082
	  {
		a = -1.6523717e-19;
		b = 8.9985350e-20;
		c = -1.6274172e-20;
		d = 9.9011450e-22;
	  }
	  else if ((0.17232 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.18281)) // 0.2082, 0.2237
	  {
		a = 1.1344452e-19;
		b = -6.5473280e-20;
		c = 1.2218550e-20;
		d = -7.1844160e-22;
	  }
	  else if ((0.18281 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.22112)) // 0.2237, 0.2839
	  {
		a = 3.3443127e-21;
		b = -2.3992833e-21;
		c = 5.2804860e-22;
		d = -2.7107599e-23;
	  }
	  else if ((0.22112 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.23442)) // 0.2839, 0.3062
	  {
		a = 3.3600750e-19;
		b = -2.9053098e-19;
		c = 8.3692060e-20;
		d = -8.0262204e-21;
	  }
	  else if ((0.23442 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.29189)) // 0.3062, 0.4122
	  {
		a = 7.2982210e-21;
		b = -9.7898790e-21;
		c = 4.2240125e-21;
		d = -5.7809220e-22;
	  }
	  else if ((0.29189 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.3224500747)) // 0.4122, 0.475906
	  {
		a = 8.481470906426100E-021;
		b = -1.043344688619260E-020;
		c = 4.151436008284200E-021;
		d = -5.216988890751000E-022;
	  }
	  else if ((0.3224500747 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.32560)) // 0.475906, 0.4828
	  {
		a = 9.1381020e-19;
		b = -1.2881546e-18;
		c = 6.0516750e-19;
		d = -9.4744260e-20;
	  }
	  //else if ((0.32560 < oxygen_mole_fraction) && (oxygen_mole_fraction <= (0.33333333))) // 0.4828, 0.5000
	  else // if ((0.32560 < oxygen_mole_fraction) && (oxygen_mole_fraction <= (0.33333333))) // 0.4828, 0.5000
	  {
		a = -2.0839046e-19;
		b = 3.1234032e-19;
		c = -1.5552958e-19;
		d = 2.5742517e-20;
	  }

	  // The piecewise function for the diffusion coefficient at 800 K: 
	  if (oxygen_mole_fraction <= 0.01903) // 0.0194
	  {
		if (oxygen_mole_fraction < 0)
		{
			aa=0;
			bb=0;
			cc=0;
			dd=5.81e-19;
		}
		else
		{
			aa = 2.9144310e-14;
			bb = -2.1467159e-16;
			cc = -2.5e-17;
			dd = 5.81e-19;
		}
	  }
	  else if ((0.01903 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.05312)) // 0.0194, 0.0561
	  {
		aa = 9.5709440e-17;
		bb = -1.3890865e-17;
		cc = 7.9019412e-21;
		dd = 2.3237586e-19;
	  }
	  else if ((0.05312 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.08484)) // 0.0561, 0.0927
	  {
		aa = -2.4531743e-16;
		bb = 5.8238460e-17;
		cc = -4.8651586e-18;
		dd = 3.3895960e-19;
	  }
	  else if ((0.08484 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.10145)) // 0.0927, 0.1129
	  {
		aa = -4.9643745e-15;
		bb = 1.9120032e-15;
		cc = -2.2689646e-16;
		dd = 8.7505149e-18;
	  }
	  else if ((0.10145 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.13465)) // 0.1129, 0.1556
	  {
		aa = -3.1573260e-15;
		bb = 1.1830885e-15;
		cc = -1.3140767e-16;
		dd = 4.660465e-18;
	  }
	  else if ((0.13465 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.15433)) // 0.1556, 0.1825
	  {
		aa = -4.0905793e-15;
		bb = 1.7429388e-15;
		cc = -2.3784707e-16;
		dd = 1.1183476e-17;
	  }
	  else if ((0.15433 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.16937)) // 0.1825, 0.2039
	  {
		aa = 4.4086102e-15;
		bb = -2.6864931e-15;
		cc = 5.2966720e-16;
		dd = -3.3021500e-17;
	  }
	  else if ((0.16937  < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.21223)) // 0.2039, 0.2694
	  {
		aa = -1.6296425e-15;
		bb = 1.3089140e-15;
		cc = -3.4905780e-16;
		dd = 3.1233835e-17;
	  }
	  else if ((0.21223 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.23471)) // 0.2694, 0.3067
	  {
		aa = 8.7058500e-15;
		bb = -7.1522800e-15;
		cc = 1.9595000e-15;
		dd = -1.7868800e-16;  
	  }
	  else if ((0.23471 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.24840)) // 0.3067, 0.3305
	  {
		aa = -1.3040400e-14;
		bb = 1.2480200e-14;
		cc = -3.9463700e-15;
		dd = 4.1329000e-16;  
	  }
	  else if ((0.24840 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.25457)) // 0.3305, 0.3415
	  {
		aa = -3.6806910e-13;
		bb = 3.6826370e-13;
		cc = -1.2277960e-13;
		dd = 1.3642114e-14;  
	  }
	  else if ((0.25457 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.27730)) // 0.3415, 0.3837
	  {
		aa = -2.4418917e-15;
		bb = 2.7207448e-15;
		cc = -1.0346320e-15;
		dd = 1.3497944e-16;  
	  } 
	  else if ((0.27730 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.29810)) // 0.3837, 0.4247
	  {
		aa = -5.8841282e-15;
		bb = 7.4104597e-15;
		cc = -3.1131623e-15;
		dd = 4.3651870e-16;  
	  }
	  else if ((0.29810 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.32001)) // 0.4247, 0.4706
	  {
		aa = -7.0525523e-18;
		bb = 2.4503905e-17;
		cc = -1.9677408e-17;
		dd = 4.7184717e-18;  
	  }
	  else if ((0.32001 < oxygen_mole_fraction) && (oxygen_mole_fraction <= 0.32917)) // 0.4706, 0.4907
	  {
		aa = 7.4091810e-14;
		bb = -1.0486404e-13;
		cc = 4.9470650e-14;
		dd = -7.7790233e-15;  
	  }
	  //else if ((0.32917 < oxygen_mole_fraction) && (oxygen_mole_fraction <= (0.33333333))) // 0.4907, 0.5000
	  else // if ((0.32917 < oxygen_mole_fraction) && (oxygen_mole_fraction <= (0.33333333))) // 0.4907, 0.5000
	  {
		aa = -9.7933700e-13;
		bb = 1.4585665e-12;
		cc = -7.2392580e-13;
		dd = 1.1974041e-13;  
	  }
}

// Now to use the spline values:

  // Need to convert from mole fraction to x concentration (ZrO_x) because the splines
  // use that x as the argument:
  //xconc = oxygen_mole_fraction / (1 - oxygen_mole_fraction);
  double xconc; // = conc;

  xconc = conc / (1 - conc);

  if (xconc < 0) xconc = 0; // to address possible numerical fluctuations early on

  // If we're in the oxide, then it's ZrO_2, or close to it, so
  // x is definitely > 0.5, so...
  if (xconc > 0.5) xconc = 0.5;
  // ...because h_value will use the oxide value for diffusivity, so we can use the
  // spline value at ZrO_0.5.

  if (xconc != xconc) xconc = 0.5;

  // Finally calculating the diffusivity at 600 K using the appropriate coefficients:
  diffusivity_600K = (a * xconc * xconc * xconc
	+ b * xconc * xconc 
	+ c * xconc + d);

  // Finally calculating the diffusivity at 800 K using the appropriate coefficients:
  diffusivity_800K = (aa * xconc * xconc * xconc
	+ bb * xconc * xconc
	+ cc * xconc + dd);  

  double Dratio = (aa * xconc * xconc * xconc
	+ bb * xconc * xconc
	+ cc * xconc + dd) / (a * xconc * xconc * xconc
	+ b * xconc * xconc
	+ c * xconc + d);	
  // NOTE:
  // _diffusivity[_qp] is calculated using an Arrhenius relation. Piecewise functions
  // for diffusivity at 600 and 800 K are used to calculate the activation energy
  // and prefactor for a given concentration. The diffusivity is then calculated using
  // the prefactor, activation energy, and the temperature (coupled). Therefore,
  // this calculation is both concentration and temperature dependent. All of the data
  // from 0 to the solubility of 0.5 (8-9-13) and from 600 K and 800 K is
  // available - no interpolating necessary. The functions are continuous in value and 
  // derivative.
	  
  double kB = 8.6173324e-5;
  double Ea;
  double prefactor;
  
  Ea = kB * 600. * 800. * log(Dratio) / 200.;
  
  prefactor = (exp(Ea / (kB*600.))) * (a * xconc * xconc * xconc 
		+ b * xconc * xconc
		+ c * xconc + d);


  double ratio = ((diffusivity_800K) / (diffusivity_600K));
  if (ratio != ratio) std::cout << "ratio is NaN" << std::endl;

  double metal_diffusivity = prefactor * exp(-Ea / (kB * temp));

  if (Ea != Ea)
  {
        std::cout << "Ea is NaN" << std::endl;
       	std::cout << "600 = " << diffusivity_600K << std::endl;
  	std::cout << "800 = " << diffusivity_800K << std::endl;
        std::cout << "xconc = " << xconc << std::endl;
  }
  if (prefactor != prefactor) std::cout << "prefactor is NaN" << std::endl;
  if (diffusivity_600K != diffusivity_600K) std::cout << "600 is NaN " << std::endl;
  if (diffusivity_800K != diffusivity_800K) std::cout << "800 is NaN" << std::endl;

  if (_t < 30) metal_diffusivity = 1e-20;

  return metal_diffusivity;
}

Real
MobilityforConcentrationPF::computeHFunction(const Real & phi)
{
  Real value = phi * phi * (3 - 2*phi);

  return value;	
}

void MobilityforConcentrationPF::computeDebugOutput()
{
	if (_diffusivity[_qp] < 0)
	{
		std::cout << "D < 0" << std::endl;
		std::cout << "	D = " << _diffusivity[_qp] << std::endl;
	}

	if (_diffusivity[_qp] != _diffusivity[_qp])
	{
		std::cout << "D is nan" << std::endl;
	}

}
