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
      // Do stuff
      //************************************************************************

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

