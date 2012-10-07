/**
 * @file sandbox.cpp
 * Place for trying things out.
 */
#include <exception>
#include <iostream>
#include <Eigen/Dense>
#include "gp/sqdist.h"
#include "gp/CovSEiso.h"
#include "gp/CovNoise.h"
#include "gp/CovSum.h"
#include <boost/proto/proto.hpp>
#include <boost/typeof/std/ostream.hpp>
#include <boost/math/distributions.hpp>
using namespace boost;

/**
 * Module namespace.
 */
namespace {

/**
 * Maximum error allowed when comparing real numbers for equality.
 */
const double EPSILON = 1e-8;

/**
 * Wrapper for lazy distributions expressions.
 */
template<typename Expr> struct DistMixture;

/**
 * Domain for probability distributions.
 */
struct DistDomain : proto::domain< proto::generator<DistMixture> >
{
};

/**
 * Wrapper for distribution expressions.
 */
template<typename Expr>
struct DistMixture
  : proto::extends<Expr, DistMixture<Expr>, DistDomain>
{
   typedef proto::extends<Expr, DistMixture<Expr>, DistDomain> base_type;

   DistMixture(Expr const &expr = Expr()) : base_type(expr) {}

   typedef double result_type;
};

/**
 * Test stream terminal.
 */
proto::terminal< std::ostream & >::type cout_ = { std::cout };

/**
 * Test evaluation function.
 */
template< typename Expr >
void evaluate( Expr const & expr )
{
   proto::default_context ctx;
   proto::eval(expr, ctx);
}

} // module namespace

/**
 * Main function.
 */
int main()
{
   std::cout << "Hello world! " << std::endl;
   using namespace Eigen;

   try
   {
      //************************************************************************
      // Do stuff
      //************************************************************************
      evaluate( cout_ << "hello" << ',' << " world\n" );

      MatrixXd result;
      std::cout << "result (" << result.rows() << "x" << result.cols()
         << ") is:\n" << result << std::endl;
      Matrix4d A;
      A << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;
      Vector4d x; 
      x << 1, 2, 3, 4;
      result = A*x;
      std::cout << "result (" << result.rows() << "x" << result.cols()
         << ") is:\n" << result << std::endl;

      std::cout << A.rowwise().replicate(2) << std::endl;

   }
   catch(std::exception& e)
   {
      std::cout << "Caught error: " << e.what() << std::endl;
      return EXIT_FAILURE;
   }

   //***************************************************************************
   // Return sucessfully
   //***************************************************************************
   return EXIT_SUCCESS;
}

