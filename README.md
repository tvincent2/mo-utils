mo-utils
========

Shared utilities for multiple objective optimization solvers.

These utilities are used by [biobj-simplex](https://github.com/tvincent2/biobj-simplex) and [mo-solver](https://github.com/tvincent2/mo-solver).

## Running tests

First install dependencies:
* CMake
* CppUnit

`apt-get install cmake libcppunit-dev`

Then build the test suite:  
`mkdir build`  
`cd build`  
`cmake ..`  
`make`

And test!  
`test/mo_utils_tests`
