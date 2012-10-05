/**
 * @file gp/sqdist.h
 * Defines the bayes::gp::sqdist function.
 */
#ifndef BAYES_GP_SQDIST
#define BAYES_GP_SQDIST

#include <boost/utility/enable_if.hpp>
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
 * Trait class used to validate parameters passed to sqdist function at
 * compile time. In particular, the compile size of the result parameter
 * must be dynamic, or fixed to the correct size at compile time.
 */
template<class M1, class M2, class MR> struct isResultSizeValid
{
   /**
    * Check that both input matrix types have compatible row sizes.
    */
   static const bool consistent =
      (M1::RowsAtCompileTime==Eigen::Dynamic) ||
      (M2::RowsAtCompileTime==Eigen::Dynamic) ||
      (M1::RowsAtCompileTime==M2::RowsAtCompileTime);

   /**
    * True iff result row size is Dynamic, or fixed to correct value at
    * compile time.
    */
   static const bool rowsOK = (MR::RowsAtCompileTime==Eigen::Dynamic) ||
                              (MR::RowsAtCompileTime==M1::ColsAtCompileTime);

   /**
    * True iff result col size is Dynamic, or fixed to correct value at
    * compile time.
    */
   static const bool colsOK = (MR::ColsAtCompileTime==Eigen::Dynamic) ||
                              (MR::ColsAtCompileTime==M2::ColsAtCompileTime);

   /**
    * True iff \c M1 and \c M2 have same column size, and the result size is
    * dynamic, or fixed to correct value at compile time.
    */
   static const bool value = rowsOK && colsOK && consistent;
};

/**
 * Calculates the squared distance between vectors.
 * @param[in] m1 first input matrix
 * @param[in] m2 second input matrix
 * @param[out] result a matrix or array that will contain the squared distance
 * between each pair of columns in \c m1 and \c m2. The size of the result will
 * be m1.cols() x m2.cols().
 * @pre The size of result must be dynamic (and therefore resizable at 
 * runtime) or fixed to correct size at compile time. If this is not the case,
 * a compile time error will occur.
 */
template<class M1, class M2, class MR>
typename boost::enable_if< isResultSizeValid<M1,M2,MR> >::type
sqdist(const M1& m1, const M2& m2, MR& result)
{
   //**************************************************************************
   // Ensure that result has correct number of rows and columns. This only
   // applies to dynamic result classes. For fixed sized results, the size
   // must be correct at compile time.
   //**************************************************************************
   result.resize(m1.cols(),m2.cols());

   //**************************************************************************
   // Calculate the squared distance between each pair of columns.
   //**************************************************************************
   Eigen::Matrix<typename MR::Scalar,M1::RowsAtCompileTime,1>
      dist(m1.rows(),1); // distance between current pair of columns

   for(int i=0; i<m1.cols(); ++i)
   {
      for(int j=0; j<m2.cols(); ++j)
      {
         dist = m1.col(i)-m2.col(j);
         result(i,j) = dist.squaredNorm();

      } // inner for loop

   } // out for loop

} // sqdist

/**
 * Calculates the squared distance between each pair of columns in a matrix.
 * @param[in] m1 input matrix
 * @param[out] result a matrix or array that will contain the squared distance
 * between each pair of columns in \c m1. The size of the result will
 * be m1.cols() x m1.cols().
 * @pre The size of result must be dynamic (and therefore resizable at 
 * runtime) or fixed to correct size at compile time. If this is not the case,
 * a compile time error will occur.
 */
template<class M1, class MR> void sqdist(const M1& m1, MR& result)
{
   return sqdist(m1,m1,result);
} 

} // namespace gp
} // namespace bayes

#endif // BAYES_GP_SQDIST
