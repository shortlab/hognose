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

#ifndef RESETTRANSIENTMULTIAPP_H
#define RESETTRANSIENTMULTIAPP_H

#include "TransientMultiApp.h"
#include "PostprocessorInterface.h"

// Forward declarations
class ResetTransientMultiApp;
//class Transient;

template <>
InputParameters validParams<ResetTransientMultiApp>();

class ResetTransientMultiApp : public TransientMultiApp,
			       public PostprocessorInterface
{
public:
  ResetTransientMultiApp(const InputParameters & parameters);



  virtual void preTransfer(Real dt, Real target_time) override;

private:

  const PostprocessorValue & _oxide_thickness;

  Real _transition_thickness;

};


#endif // RESETTRANSIENTMULTIAPP_H
