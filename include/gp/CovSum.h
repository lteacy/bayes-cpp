/**
 * @file gp/CovSum.h
 * Defines the bayes::gp::CovSum class.
 * Provides an implementation of covariance function, composed by
 * summing other covariance functions.
 */
#ifndef BAYES_GP_COVSUM_H
#define BAYES_GP_COVSUM_H

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
 * Provides an implementation of covariance function, composed by
 * summing other covariance functions.
 */
template<class C1, class C2> class CovSum
{
private:

   /**
    * First covariance function.
    */
   C1 cov1_i;

   /**
    * Second covariance function.
    */
   C2 cov2_i;

public:

   /**
    * Constructs a new Independent Noise Covariance function.
    */
   CovSum(const C1& c1, const C2& c2)
      : cov1_i(c1), cov2_i(c2) {}

   /**
    * Returns reference to first covariance function.
    */
   C1& cov1() { return cov1_i; }

   /**
    * Returns reference to first covariance function.
    */
   C2& cov2() { return cov2_i; }

   /**
    * Returns the covariance between points.
    */
   template<class M1, class M2, class MR>
      void operator()(const M1& m1, const M2& m2, MR& result)
   {
      MR part1;
      cov1_i(m1,m2,part1);
      cov2_i(m1,m2,result);
      result += part1;
   } 

   /**
    * Returns the covariance between each pair of columns in a matrix.
    */
   template<class M1, class MR> void operator()(const M1& m1, MR& result)
   {
      return (*this)(m1,m1,result);
   }

}; // class CovSum

/**
 * Adds two covariance functions together.
 */
template<class C1,class C2> CovSum<C1,C2> operator+(const C1& c1, const C2& c2)
{
   return CovSum<C1,C2>(c1,c2);
}

} // namespace gp
} // namespace bayes

#endif // BAYES_GP_COVSUM_H
