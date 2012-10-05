/**
 * @file gp/CovSEiso.h
 * Defines the bayes::gp::CovSEiso class.
 * This provides an implementation of an isotropic squared exponential covariance
 * function.
 */
#ifndef BAYES_GP_COVSEISO
#define BAYES_GP_COVSEISO

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
 * Provides an implementation of an isotropic squared exponential covariance
 * function.
 */
class CovSEiso
{
private:

   /**
    * The log covariance scale of the covariance function.
    */
   double logScale_i;

   /**
    * The length scale of the covariance function.
    */
   double length_i;

public:

   /**
    * Constructs a new Isotropic Squared Exponential Covariance function.
    * @param[in] scale the covariance scale hyperparameter.
    * @param[in] length the length scale of the covariance function.
    */
   CovSEiso(double scale=1.0, double length=1.0)
      : logScale_i(std::log(scale)), length_i(length) {}

   /**
    * Sets the scale of this covariance function.
    */
   void scale(double scale) { logScale_i = std::log(scale); }

   /**
    * Sets the length scale of this covariance function.
    */
   void length(double length) { length_i = length; }

   /**
    * Gets the scale of this covariance function.
    */
   double scale() { return std::exp(logScale_i); }

   /**
    * Gets the length scale of this covariance function.
    */
   double length() { return length_i; }

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

}; // class CovSEiso

} // namespace gp
} // namespace bayes

#endif // BAYES_GP_COVSEISO
