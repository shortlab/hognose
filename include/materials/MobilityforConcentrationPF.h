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


#ifndef MOBILITYFORCONCENTRATIONPF_H
#define MOBILITYFORCONCENTRATIONPF_H

#include "Material.h"

//Forward Declarations
class MobilityforConcentrationPF;

template<>
InputParameters validParams<MobilityforConcentrationPF>();

class MobilityforConcentrationPF : public Material
{
public:
  MobilityforConcentrationPF(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  virtual Real computeOxideDiffusivity(const Real & conc, const Real & temp, const Real & D1, const Real & T1, const Real & D2, const Real & T2);
  virtual Real computeMetalSplineDiffusivity(const Real & conc, const Real & temp);
  virtual Real computeHFunction(const Real & phi);
  virtual void computeDebugOutput();

private:

  MaterialProperty<Real> & _h_value;
  MaterialProperty<Real> & _diffusivity;
  MaterialProperty<Real> & _diffusivity_out;
  MaterialProperty<Real> & _zr_conductivity;
  MaterialProperty<Real> & _zr_mass_density;
  MaterialProperty<Real> & _zr_molar_density;
  MaterialProperty<Real> & _zr_specific_heat;
  MaterialProperty<Real> & _oxygen_density;
  MaterialProperty<Real> & _oxygen_vacancy;
  MaterialProperty<Real> & _o_ion_mobility;
  const VariableValue & _Oxygen_conc;
  const VariableValue & _phase;
  const VariableValue & _coupled_temperature;
  Real _scaling_factor;
  Real _charge_value;
  Real _delta_c;
  Real _stoich_fraction;
  Real _Oxide_stoich;
  Real _oxide_baseline;
  const MaterialProperty<Real> & _total_diffusivity_factor;
  MooseEnum _energy_units;
  Real _constant_temp;
  const VariableValue & _oxide_phase;
  Real _curvature_value_k;
  Real _D1;
  Real _T1;
  Real _D2;
  Real _T2;
  Real _doping_max_factor;
  Real _charge_constant_initial;
  const VariableValue & _charge_density;
  Real _doping_effect_on;
  MaterialProperty<Real> & _doping_factor;
  Real _doping_power;
  const PostprocessorValue & _transition_count;

};

#endif //MOBILITYFORCONCENTRATIONPF_H
