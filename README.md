munkres-cpp
===========

[![build status](https://gitlab.com/Gluttton/munkres-cpp/badges/devel/pipeline.svg)](https://gitlab.com/Gluttton/munkres-cpp/commits/devel)
[![coverage report](https://gitlab.com/Gluttton/munkres-cpp/badges/devel/coverage.svg)](https://gitlab.com/Gluttton/munkres-cpp/commits/devel)


An implementation of the Kuhn–Munkres algorithm.



License
-------

Copyright (c) 2007-2017 John Weaver and contributors.  
Licensed under the GPLv2. See the file COPYING for details.



Requires
--------

For using:  
 - C++ compiler with C++11 support.  



Portability
-----------

The project is developing under GNU/Linux OS with gcc compiler and usualy not tested under other OS and compilers.
But in the project not used OS or compiler specific features (types, attributes, etc) so it's expected that the project will be normally work under other platforms.  

For easy integration of the library into existing projects, adapters are provided for several of the most well-known libraries.  

Full support (square and rectangular matrices):  
 - Armadillo;  
 - boost;  
 - Eigen;  
 - matrices based on `std::vector`.  

Partial support (square matrices only):  
 - OpenCV;  
 - Qt.  



Usage
-----

To use the project the following steps are required:  
  - download: ```$ git clone https://github.com/saebyn/munkres-cpp.git```  
  - install: ``` $ cd munkres-cpp && make install```  
  - or copy: ```src/munkres-cpp``` subfolder into your project tree  



Example
-------

Briefly, to solve the problem you need:  
```
#include <munkres-cpp/munkres.h>
...
// set cost matrix using the type provided by the library,
munkres_cpp::Matrix<int> data {
    {1, 3}
   ,{5, 9} };
// create solver and pass the matrix to it.
munkres_cpp::Munkres<int> solver (data);
```
Thats all! The library solves the problem in-place and put the solution it the input matrix.

Examples subfolder contains set of examples which step-by-step show usage of the library.



Development
-----------

The source code is managed using git. The main repository is hosted at [gitlab](https://gitlab.com/Gluttton/munkres-cpp)
and the mirror is hosted at [github](https://github.com/Gluttton/munkres-cpp). To prevent project complications,
a separate branch `devel` is used for development. Using of gitlab allows to implement CI process.
The current CI implements the following steps:  
 - get the source code from `devel` branch;  
 - build and launch unit tests;  
 - analyze test coverage;  
 - build examples;  
 - build benchmarks;  
 - check the code with static code analyzer.

CI is executed inside the Docker container. The container is created automatically by commit in `docker` branch.

All CI steps are defined inside standard GitLab script: `.gitlab.yaml`.



Requirements:  
 - [GCC](https://gcc.gnu.org/) (tested on 4.6.3, 6.3.0);  
 - [GNU Make](https://www.gnu.org/software/make/);  
 - [CMake](http://www.cmake.org/) (2.8.12);  
 - the test suite requires the [Google C++ Test Framework](http://code.google.com/p/googletest/);  
 - microbenchmaring requires [Benchmark](https://github.com/google/benchmark), [Celero](https://github.com/DigitalInBlue/Celero), [Hayai](https://github.com/nickbruun/hayai) and [gprof](http://www.gnu.org/software/binutils/);  
 - code coverage requires [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) and lcov;  
 - static code analysis requires [cppcheck](https://github.com/danmar/cppcheck);  
 - source code formatting requires [uncrustify](http://uncrustify.sourceforge.net).  



For development purpose in the project implemented a variety of build targets.
All of them help to continuously check correctness of algorithm implementation, performance, memory management, etc.
To configure project in development mode ```-DMUNKRESCPP_DEVEL_MODE=ON``` option must be passed to CMake.

Launch of unit tests.
The project contains unit tests to build and launch it performs the following steps:
```
$ git clone https://github.com/saebyn/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug -DMUNKRESCPP_DEVEL_MODE=ON ..
$ make tests
$ tests/munkrestest
```


Lunch code coverage analyze.
To get correct report unit tests must be compiled in debug mode.
```
$ <build and lunch unit tests>
$ make coverage
$ firefox coverage/index.html &
```


Lunch memory profiler.
As far unit tests call all functions which implement algorithm this is appropriate way to check memory management by using valgrind during performing unit tests.
```
$ <build unit tests>
$ valgrind tests/munkrestest
```


Lunch microbenchmarks.
Buildning microbenchmarks:
```
$ git clone https://github.com/saebyn/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DMUNKRESCPP_DEVEL_MODE=ON ..
$ make benchmarks
```
To get comparable results it's required to generate data set wich will be used for all benchmarks:
```
$ benchmarks/tools/generator/matrixgenerator.bin {dim_1 dim_2 ... dim_n}
```
Where every ```dim_x``` parameter generate square matrix dith ```dim_x``` dimension.
To launch microbenchmark performs any following command:
```
$ benchmarks/tests/munkresbenchmark_celero.bin
$ benchmarks/tests/munkresbenchmark_google.bin
$ benchmarks/tests/munkresbenchmark_hayai.bin
$ benchmarks/tests/munkresbenchmark_rdtsc.bin
```


Lunch performance analyze.
```
$ <build microbenchmarks and generate data set>
$ benchmarks/tests/munkresbenchmark_gprof.bin
$ gprof benchmarks/tests/munkresbenchmark_gprof.bin gmon.out -p -b
```


Lunch static code analyze.
```
$ make cppcheck
```


Lunch code formatter.
Code formatter is used to convert style of each contributor to common style and make code easier to read.  
In the project [Uncrustify](http://uncrustify.sourceforge.net) is used as code formatter.  
Modified code before commit should be formatted using Uncrustify.  
```
$ make beauty
```


Bug reporting and work to be done
---------------------------------

Check the [issues list at GitLab](https://gitlab.com/Gluttton/munkres-cpp/issues?scope=all&utf8=%E2%9C%93&state=opened).
