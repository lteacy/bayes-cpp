/**
 * @file mdpHarness.cpp
 * Test harness. 
 */
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/utility.hpp>
#include <exception>
#include <iostream>
#include <Eigen/Dense>
#include "gp/cov.h"

/**
 * Module namespace.
 */
namespace {

/**
 * Maximum error allowed when comparing real numbers for equality.
 */
const double EPSILON = 1e-8;

/**
 * Test the noise and sum variance.
 */
int testNoise()
{
   using namespace Eigen;
   using namespace bayes::gp;

   //***************************************************************************
   // Create test matrices
   //***************************************************************************
   Matrix<double, 10, 2> m1(Matrix<double, 10, 2>::Identity()*7.2);
   Matrix<double, 10, 7> m2(Matrix<double, 10, 7>::Identity()*7.2);
   std::cout << "Matrix 1: " << std::endl;
   std::cout << m1 << std::endl;
   std::cout << "Matrix 2: " << std::endl;
   std::cout << m2 << std::endl;

   //***************************************************************************
   // Create covariance function.
   //***************************************************************************
   bayes::gp::CovNoise kernel(3.52);
   bayes::gp::CovSEiso iso(1,500);
   bayes::gp::CovSum<CovNoise,CovSEiso> sum(kernel,iso);
   BOOST_AUTO(sum2,kernel+iso+iso);

   //***************************************************************************
   // Calculate covariance between m1 and m2
   //***************************************************************************
   Array<double,Dynamic,Dynamic> cov;
   kernel(m1,m2,cov);
   std::cout << "Covariance:\n" << cov << std::endl;

   //***************************************************************************
   // Self covariance for m1 and m2
   //***************************************************************************
   sum(m1,m2,cov);
   std::cout << "Sum Covariance:\n" << cov << std::endl;
   sum2(m1,m2,cov);
   std::cout << "Sum2 Covariance:\n" << cov << std::endl;

   //***************************************************************************
   // Self covariance for m1
   //***************************************************************************
   kernel(m1,cov);
   std::cout << "Covariance:\n" << cov << std::endl;

   //***************************************************************************
   // Self covariance for m2
   //***************************************************************************
   kernel.var(23.5);
   kernel(m2,m2,cov);
   std::cout << "Covariance:\n" << cov << std::endl;

   return EXIT_SUCCESS;

} // function testNoise

/**
 * Test the Isotropic squared distance.
 */
int testSEiso()
{
   using namespace Eigen;

   //***************************************************************************
   // Create test matrices
   //***************************************************************************
   Matrix<double, 4, 3> m1(Matrix<double, 4, 3>::Identity());
   Matrix<double, 4, 1> m2(Matrix<double, 4, 1>::Identity()*2.5);
   std::cout << "Matrix 1: " << std::endl;
   std::cout << m1 << std::endl;
   std::cout << "Matrix 2: " << std::endl;
   std::cout << m2 << std::endl;

   //***************************************************************************
   // Create covariance function.
   //***************************************************************************
   bayes::gp::CovSEiso kernel(2.1,3.2);

   //***************************************************************************
   // Calculate covariance between m1 and m2
   //***************************************************************************
   Array<double,Dynamic,Dynamic> cov;
   kernel(m1,m2,cov);
   std::cout << "Covariance:\n" << cov << std::endl;

   //***************************************************************************
   // Self covariance for m1
   //***************************************************************************
   kernel.scale(1);
   kernel.length(3);
   kernel(m1,cov);
   std::cout << "Covariance:\n" << cov << std::endl;

   //***************************************************************************
   // Self covariance for m2
   //***************************************************************************
   kernel.scale(2);
   kernel(m2,m2,cov);
   std::cout << "Covariance: " << cov << std::endl;

   return EXIT_SUCCESS;

} // function testSEiso

/**
 * Test that the squared distance is working.
 */
int testSquaredDistance()
{
   using namespace Eigen;

   //***************************************************************************
   // Create test matrices
   //***************************************************************************
   Matrix<double, 5, 3> m1(Matrix<double, 5, 3>::Identity());
   Matrix<double, 5, 4> m2(Matrix<double, 5, 4>::Identity()*2.1);
   std::cout << "Matrix 1: " << std::endl;
   std::cout << m1 << std::endl;
   std::cout << "Matrix 2: " << std::endl;
   std::cout << m2 << std::endl;

   //***************************************************************************
   // Calculate the squared distance between them
   //***************************************************************************
   Matrix<double,Dynamic,4> dist;
   bayes::gp::sqdist(m2,dist);
   std::cout << "Squared distance m2,m2:\n" << dist << std::endl;
   bayes::gp::sqdist(m1,m2,dist);
   std::cout << "Squared distance m1,m2:\n" << dist << std::endl;

   //***************************************************************************
   // Correct result
   //***************************************************************************
   Matrix<double,3,4> correctDist;
   correctDist << 1.21, 5.41, 5.41, 5.41,
                  5.41, 1.21, 5.41, 5.41,
                  5.41, 5.41, 1.21, 5.41;

   //***************************************************************************
   // Validate the squared distance
   //***************************************************************************
   double distError = (correctDist-dist).lpNorm<Infinity>();
   if(EPSILON < distError)
   {
      std::cout << "Incorrect Squared Distance" << std::endl;
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
   
} // function testSquaredDistance()
   
} // module namespace

/**
 * Test harness (not yet implmented).
 */
int main()
{
   std::cout << "Hello world! " << std::endl;
   using namespace Eigen;

   try
   {
      //************************************************************************
      // Test squared distance function
      //************************************************************************
      if(EXIT_SUCCESS!=testSquaredDistance())
      {
         std::cout << "Squared distance test failed." << std::endl;
         return EXIT_FAILURE;
      }
      std::cout << "Squared distance test passed." << std::endl;

      //************************************************************************
      // Test Squared Exponential Covariance function.
      //************************************************************************
      if(EXIT_SUCCESS!=testSEiso())
      {
         std::cout << "Squared Exponential test failed." << std::endl;
         return EXIT_FAILURE;
      }
      std::cout << "Squared Exponential test passed." << std::endl;

      //************************************************************************
      // Test Noise Covariance function.
      //************************************************************************
      if(EXIT_SUCCESS!=testNoise())
      {
         std::cout << "Noise test failed." << std::endl;
         return EXIT_FAILURE;
      }
      std::cout << "Noise test passed." << std::endl;
      
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

