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


#ifndef AMORPHOUSWIDTHMATERIAL_H
#define AMORPHOUSWIDTHMATERIAL_H

#include "Material.h"
#include "Function.h"

//Forward Declarations
class AmorphousWidthMaterial;

template<>
InputParameters validParams<AmorphousWidthMaterial>();

class AmorphousWidthMaterial : public Material
{
public:
  AmorphousWidthMaterial(const InputParameters & parameters);

  virtual void initialSetup() override;

protected:
  virtual void initQpStatefulProperties() override;

  virtual void computeQpProperties();

  virtual Real computeWeightedVolumeChange(const Real & diameter, const Real & delta,
		const Real & delta_old, const Real & number_fraction);

  virtual Real computeAmorphousBool(const Real & diameter, const Real & delta);

  virtual Real computeIntegralIronRelease(const Real & diameter, const Real & delta,
		const Real & delta_old,	const Real & crystal_Fe_density, 
		const Real & amorphous_Fe_density);

  virtual Real computeIronIntegral(const Real & rho_a, const Real & rho_c,
		const Real & r_c, const Real & r_a);

  virtual Real computeDiffusivity(const Real & flux);
private:

  MaterialProperty<Real> & _amorphous_width;
  const MaterialProperty<Real> & _amorphous_width_old;
  MaterialProperty<Real> & _net_iron_change;
  MaterialProperty<Real> & _overall_iron_change;
  const MaterialProperty<Real> & _overall_iron_change_old;
  MaterialProperty<Real> & _iron_release_density;
  MaterialProperty<Real> & _SPP_Zr_density;
  MaterialProperty<Real> & _avg_SPP_diameter;
  Real _scaling_factor;
  const MaterialProperty<Real> & _zr_molar_density;
  const VariableValue & _coupled_temperature;
  Function & _n_flux;
  const PostprocessorValue & _transition_count;
  const PostprocessorValue & _time_offset;
  const PostprocessorValue & _transferred_delta_old;
  std::vector<Real> _SPP_sizes;
  std::vector<Real> _SPP_number_fractions;
  MaterialProperty<Real> & _amorphous_fraction;
  MaterialProperty<Real> & _new_iron_release;
  std::vector<Real> _remaining_iron;
  MaterialProperty<Real> & _s1_iron;
  MaterialProperty<Real> & _s2_iron;
  MaterialProperty<Real> & _s3_iron;
  const MaterialProperty<Real> & _s1_iron_old;
  const MaterialProperty<Real> & _s2_iron_old;
  const MaterialProperty<Real> & _s3_iron_old;
  MaterialProperty<Real> & _amorphous_t1;
  MaterialProperty<Real> & _amorphous_t2;
  MaterialProperty<Real> & _amorphous_t3;
  const MaterialProperty<Real> & _amorphous_t1_old;
  const MaterialProperty<Real> & _amorphous_t2_old;
  const MaterialProperty<Real> & _amorphous_t3_old;
  const PostprocessorValue & _s1_PP;
  const PostprocessorValue & _s2_PP;
  const PostprocessorValue & _s3_PP;
  const PostprocessorValue & _t1_PP;
  const PostprocessorValue & _t2_PP;
  const PostprocessorValue & _t3_PP;
  


};

#endif //AMORPHOUSWIDTHMATERIAL_H
