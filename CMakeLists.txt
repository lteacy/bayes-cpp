########################################
# set up the project basic information #
########################################

# project name
PROJECT(Bayes-CPP)

# minimum cmake version required
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# add or remove debugging info
SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++" )
list( APPEND LINK_FLAGS "-stdlib=libc++" )

# verbose makefile
SET(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# output directory for binaries and libraries
SET(BIN ${CMAKE_SOURCE_DIR}/bin)
SET(LIB ${CMAKE_SOURCE_DIR}/lib)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.40.0 COMPONENTS random)
find_package(Eigen3 3.1.0)

###########################################
# Generate Documentation                  #
###########################################
# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
   ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
   COMMENT "Generating API documentation with Doxygen" VERBATIM
   )
endif(DOXYGEN_FOUND)

###########################################
# Dump exec and libraries in the same place
###########################################

# set the output directories
SET(LIBRARY_OUTPUT_PATH ${LIB} CACHE PATH "Output directory for the libraries")
SET(EXECUTABLE_OUTPUT_PATH ${BIN} CACHE PATH "Output directory for the executables")

# allow linking to these directories
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})
MESSAGE(${EIGEN3_INCLUDE_DIR})

############################
# make an uninstall target #
############################

#CONFIGURE_FILE(
# 	"${CMAKE_CURRENT_SOURCE_DIR}/UninstallScript.cmake.in"
#  	"${CMAKE_CURRENT_BINARY_DIR}/UninstallScript.cmake"
#  	IMMEDIATE @ONLY
#)

#ADD_CUSTOM_TARGET(uninstall
#  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/UninstallScript.cmake")

#############################
# compile project library   #
#############################
#FILE(GLOB Bayes_SRC src/*.cpp)
#ADD_LIBRARY(Bayes SHARED ${Bayes_SRC})
#TARGET_LINK_LIBRARIES(Bayes ${Boost_LIBRARIES})

###############################
# build test harnesses        #
###############################
ADD_EXECUTABLE(harness tests/harness.cpp)
ADD_EXECUTABLE(sandbox tests/sandbox.cpp)
#TARGET_LINK_LIBRARIES(harness Bayes)

###############################
# enable testing              #
###############################
ENABLE_TESTING()
ADD_TEST(TEST1 ${CMAKE_SOURCE_DIR}/bin/harness)

