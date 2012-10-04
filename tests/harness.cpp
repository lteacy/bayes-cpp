/**
 * @file mdpHarness.cpp
 * Test harness. 
 */
#include <exception>
#include <iostream>
#include <Eigen/Dense>
#include "gp/sqdist.h"

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
      // Create test matrices
      //************************************************************************
      Matrix<double, 5, 3> m1(Matrix<double, 5, 3>::Identity());
      Matrix<double, 5, 3> m2(Matrix<double, 5, 3>::Identity()*2);
      std::cout << "Matrix 1: " << std::endl;
      std::cout << m1 << std::endl;
      std::cout << "Matrix 2: " << std::endl;
      std::cout << m2 << std::endl;
      double dist = bayes::gp::sqdist(m1,m2);
      std::cout << "Squared distance: " << dist << std::endl;
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

