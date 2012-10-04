/**
 * @file gp/sqdist.h
 * Defines the bayes::gp::sqdist function.
 */
#ifndef BAYES_GP_SQDIST
#define BAYES_GP_SQDIST

#include <boost/type_traits/common_type.hpp>
#include <Eigen/Dense>

/**
 * Namespace for all public functions and types in the bayes-cpp library.
 */
namespace bayes {

/**
 * Namespace for functions and types used for Gaussian Process inference.
 */
namespace gp {

/**
 * Calculates the squared distance between vectors.
 */
template<class M1, class M2> typename boost::common_type
   <typename Eigen::internal::traits<M1>::Scalar,
    typename Eigen::internal::traits<M2>::Scalar>::type
sqdist(M1 m1, M2 m2)
{
   //**************************************************************************
   // Ensure operands have same number of rows
   //**************************************************************************

   //**************************************************************************
   // Calculate the squared distance between each pair of columns
   //**************************************************************************
   return 0.0;

} // sqdist

} // namespace gp
} // namespace bayes

#endif // BAYES_GP_SQDIST
