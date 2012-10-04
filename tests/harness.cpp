/**
 * @file mdpHarness.cpp
 * Test harness. 
 */
#include <ctime>
#include <exception>
#include <iostream>

/**
 * Test harness (not yet implmented).
 */
int main()
{
   std::cout << "Hello world! " << std::endl;

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

