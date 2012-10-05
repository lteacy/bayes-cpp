/**
 * @file gp/CovNoise.h
 * Defines the bayes::gp::CovNoise class.
 * This provides an implementation of independent noise covariance
 * function.
 */
#ifndef BAYES_GP_COVNOISE_H
#define BAYES_GP_COVNOISE_H

#include<cmath>
#include<gp/sqdist.h>

/**
 * Namespace for all public functions and types in the bayes-cpp library.
 */
namespace bayes {

/**
 * Namespace for functions and types used for Gaussian Process inference.
 */
namespace gp {

/**
 * Provides an implementation of an independent noise covariance
 * function.
 */
class CovNoise
{
private:

   /**
    * The noise variance.
    */
   double var_i;

public:

   /**
    * Constructs a new Independent Noise Covariance function.
    */
   CovNoise(double var=1.0) : var_i(var) {}

   /**
    * Sets the noise variance for this covariance function.
    */
   void var(double v) { var_i = v; }

   /**
    * Gets the noise variance for this covariance function.
    */
   double var() { return var_i; }

   /**
    * Returns the covariance between points.
    */
   template<class M1, class M2, class MR>
      void operator()(const M1& m1, const M2& m2, MR& result)
   {
      //************************************************************************
      // Calculate the squared distance between the inputs
      //************************************************************************
      MR dist(m1.cols(),m2.cols());
      sqdist(m1,m2,dist);

      //************************************************************************
      // From this, calculate the covariance.
      //************************************************************************
      result = logScale_i-dist.array()/length_i;
      result = result.exp();

   } // operator ()

   /**
    * Returns the covariance between each pair of columns in a matrix.
    */
   template<class M1, class MR> void operator()(const M1& m1, MR& result)
   {
      return (*this)(m1,m1,result);
   }

}; // class CovNoise

} // namespace gp
} // namespace bayes

#endif // BAYES_GP_COVNOISE_H
