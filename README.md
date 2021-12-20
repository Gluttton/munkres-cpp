# munkres-cpp

[![build status](https://gitlab.com/Gluttton/munkres-cpp/badges/devel/pipeline.svg)](https://gitlab.com/Gluttton/munkres-cpp/commits/devel)
[![coverage report](https://gitlab.com/Gluttton/munkres-cpp/badges/devel/coverage.svg)](https://gitlab.com/Gluttton/munkres-cpp/commits/devel)
[![License: GPL v2](https://img.shields.io/badge/License-GPL_v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)


A generic implementation of the [Kuhn–Munkres algorithm](https://en.wikipedia.org/wiki/Hungarian_algorithm) for solving an [Assignment Problem](https://en.wikipedia.org/wiki/Assignment_problem).



## License

Copyright (c) 2007-2017 John Weaver and contributors.  
Copyright (c) 2018-2021 Gluttton <gluttton@ukr.net> and contributors.  
Licensed under the GPLv2. See the file COPYING for details.



## Requires

C++ compiler with C++11 support.



## Usage

### Breif example
```
// Include a header with the Solver class.
#include <munkres-cpp/munkres.h>
// Include a header with a buit-in Matrix container.
#include <munkres-cpp/matrix.h>

// Create and fill a cost matrix.
munkres_cpp::Matrix <int> data {
    {1, 3}
   ,{5, 9}
};

// Create a solver instance and initialize it with the prepared matrix.
munkres_cpp::Munkres <int, munkres_cpp::Matrix> solver (data);

// The task will be solved immediately in the solver constructor and
// the solution will be stored in the input variable.
// So the `data` matrix will contain the following data:
//  0, 1
//  1, 0
// That means that 3 + 5 is an optimal solution (it's true because 3 + 5 < 1 + 9).
```

The `examples` subfolder contains a set of examples that step-by-step explain the usage of the library.


### Complete example with detailed explanations

#### Introduction

One area where this library can be used is the data association step in object tracking.
Let us suppose that it is needed to track three objects in two-dimensional cartesian space.
Gating, filtering and other tracking subtasks are out of scope and in this particular example, we are interested only in the implementation of the data association step.
The old estimated position of objects is known, and we need to recalculate it based on the provided measurement innovation.
To illustrate this example let use ASCII plot:

```
^ Y
|
|   o C(2,9)
|           + z(6,8)
|           o B(6,7)
|                 + y(9,6)
|
|     + x(3,4)
|
| o A(1,2)
|
+--------------------> X

    o - estimations;
    + - measurements.
```

The project has the following structure:
```
association
├── CMakeLists.txt
└── src
    └── main.cpp
```

The `CMakeLists.txt` is trivial:
```
cmake_minimum_required (VERSION 3.10)

project (association CXX)

add_executable (association
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)
```

And source file contains the initial data definition:
```
#include <cstdlib>
#include <utility>
#include <vector>

int main (int, char **)
{
    using point = std::pair <float, float>;

    std::vector <point> estimations {
        {1, 2} // A.
      , {6, 7} // B.
      , {2, 9} // C.
    };

    std::vector <point> measurements {
        {3, 4} // x.
      , {9, 6} // y.
      , {6, 8} // z.
    };

    // Here the data association is going to be implemented.

    return EXIT_SUCCESS;
}
```


#### Installation

There are several options how to integrate the `munkres-cpp` library into a project.
1. Install the library in the system folder to make it system-wide available.
    ```
    $ git clone
    $ sudo make install
    ```
Since the `munkres-cpp` is a very small and header-only library this option seems too complicated.

2. Copy the whole library and integrate it as s separate `CMake` project via `add_subproject` directive.
    ```
    $ cd project
    $ git clone https://github.com/Gluttton/munkres-cpp .
    ```
This option seems the best choise from compatibility and long term support points of view for `CMake` based projects. This approach not only incorporate `munkres-cpp` sources into the existing project, but also inherit all the necessary requirements (actually the `munkres-cpp` has only one requirement - C++11).

3. Copy only librarie's headers into the project directory and use it as it's part.
    ```
    $ git clone https://github.com/Gluttton/munkres-cpp .
    $ mkdir project/include
    $ cp -a munkres-cpp/src/munkres-cpp project/include
    ```
This option is simple enough and sufficient and may be used for non `CMake` based projects.

In the example `munkres-cpp` will be integrated using the third option (moreover we will copy only the necessary headers but not the whole folder):
```
$ git clone https://github.com/Gluttton/munkres-cpp .
$ mkdir -p association/include/munkres-cpp
$ cp -a munkres-cpp/src/munkres-cpp/munkres.h association/include/munkres-cpp
$ cp -a munkres-cpp/src/munkres-cpp/matrix.h association/include/munkres-cpp
$ cp -a munkres-cpp/src/munkres-cpp/matrix_base.h association/include/munkres-cpp
```
Also we need to say `CMake` where to find our headers (if it wasn't done before):
```
~~~
target_include_directories (association
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)
```

The `munkres.h` header file contains the solver sources. The solver takes input data represented in a matrix form (the cost matrix).
The current implementation doesn't depend on a specific matrix type and can be used with an arbitrary data type that meets the following requirements:
 - the container type must implement the subscription operator `operator ()` that takes two parameters (row and column) and return a corresponding element of a matrix;
 - the container type must implement the `columns` and `rows` member functions that return matrix dimension;
 - the container type must implement the `begin` and `end` member functions that return appropriate iterators.

Also, the library doesn't require any specific type for a scalar element of the matrix, so any arbitrary data type can be used that meets the following requirements:
 - the element type must comparable with zero;
 - the element type must implement comparison operators (`<`, `>`);
 - the element type must implement addition and subtraction (`+`, `-`);
 - the element type must implement the assignment operator (`=`).

All fundamental arithmetic types meet the above requirements and can be used as elements of a matrix.
But unfortunately, C++ doesn't provide any ready-for-use type that may represent a matrix.
To overcome this limitation and make using easier the library provides three capabilities:
1. The `matrix_base` abstract class can be used as a helper for adaptation existing or creating a new own matrix type.
2. The `matrix` type implements the `matrix_base` interface and can be used if there are no other project-specific requirements or prohibitions.
3. A set of `adapters` types that implements the `matrix_base` interface for the most common matrix libraries such `Armadillo`, `Boost`, `Eigen` and `OpenCV`.



#### Using

Lets summaries:
 - the library provides the solver class;
 - the solver requires that input data is represented in matrix form;
 - the library provides the built-in matrix data type and set of adapters;
 - the are no unusual requirements for scalar data types, so any fundamental arithmetic type can be used.

In this example, we will use the built-in type of matrix container.
That's why above we have copied `munkres.h`, `matrix.h` and `matrix_base.h` headers.
The particular scalar type should be chosed based on the requirements to precision and performance.
If there are not any specific requirements the `float` type seems like a reasonable compromise between precision and performance.
```
#include <munkres-cpp/matrix.h>
~~~

    ~~~
    munkres_cpp::Matrix <float> data (estimations.size (), measurements.size () );
    ~~~
```

After the matrix is created we need to fill it with "cost" data.
For data association, the optimal solution means binding estimates and measurements with the minimum distance residual.
So in our example the "cost" means distance.
There are different types of distances that can be used for data association ([Manhattan](https://en.wikipedia.org/wiki/Taxicab_geometry), [Mahalanobis](https://en.wikipedia.org/wiki/Mahalanobis_distance), etc), but in this example, we will use [Euclidean](https://en.wikipedia.org/wiki/Euclidean_distance) distance.
Hence we need to calculate distance between all estimates and measurements:
```
           __________________
d(A,x) = \/ ((1-3)^2+(2-4)^2) = 2.83;
           __________________
d(A,y) = \/ ((1-9)^2+(2-6)^2) = 8.94;
           __________________
d(A,z) = \/ ((1-6)^2+(2-8)^2) = 7.81;
           __________________
d(B,x) = \/ ((6-3)^2+(7-4)^2) = 4.24;
           __________________
d(B,y) = \/ ((6-9)^2+(7-6)^2) = 3.16;
           __________________
d(B,z) = \/ ((6-6)^2+(7-8)^2) = 1.00;
           __________________
d(C,x) = \/ ((2-3)^2+(9-4)^2) = 5.10;
           __________________
d(C,y) = \/ ((2-9)^2+(9-6)^2) = 7.62;
           __________________
d(C,z) = \/ ((2-6)^2+(9-8)^2) = 4.12;


              x     y     z
           +-----------------
         A | 2.83  8.94  7.81
           |
         B | 4.24  3.16  1.00
           |
         C | 5.10  7.62  4.12 |
                             -+
```

Let's implement the above calculations using C++.
First, create a function to calculate Euclidean distance between two points in two-dimensional space:
```
float Distance (const point & a, const point & b)
{
    const float dx = a.first  - b.first;
    const float dy = a.second - b.second;
    return std::hypot (dx, dy);
}

```
And then fill the matrix using this function:
```
for (size_t i = 0; i < estimations.size (); ++i) {
    for (size_t j = 0; j < measurements.size (); ++j) {
        data (i, j) = Distance (estimations [i], measurements [j]);
    }
}
```

The input data is ready and can be passed to the solver!
```
#include <munkres-cpp/munkres.h>
~~~

    ~~~
    munkres_cpp::Munkres <float, munkres_cpp::Matrix> solver (data);
    // Now data contains the optimal solution.
    ~~~
```
The task is solved and our input matrix contains the optimal solution, hence the data association step is complete.

Next, we will see how to interpret the solution.

Let's assume that updating of estimation is trivial and implemented as an average value between old estimation and measurement:
```
point Update (const point & estimation, const point & measurement)
{
    return {(estimation.first  + measurement.first)  / 2,
            (estimation.second + measurement.second) / 2};
}
```

In this case, we can perform the update step using prepared association data like this:
```
for (size_t i = 0; i < data.rows (); ++i) {
    for (size_t j = 0; j < data.columns (); ++j) {
        // Zero means that this estimation and this measurement are associated
        if (data (i, j) == 0) {
            estimations [i] = Update (estimations [i], measurements [j]);
        }
    }
}
```
The complete example can be found in the `examples` subfolder.



## Examples

Find more examples in the `examples` subfolder:
 - `example_01.cpp` - trivial example with obvious solution;  
 - `example_02.cpp` - trivial example with less obvious solution;  
 - `example_03.cpp` - trivial example with input data validation;  
 - `example_04.cpp` - brief example of using adapter with Boost matrix;  
 - `example_05.cpp` - more complex example of using adapter with `Boost` matrix;  
 - `example_06.cpp` - more complex example of using adapter with `OpenCV` matrix;  
 - `example_07.cpp` - more complex example of creating own matrix class;  
 - `example_08.cpp` - complete real-life example of using the library for data association;  
 - `example_09.cpp` - trivial interactive example.



## Special cases

The original algorithm was developed to find an optimal solution as a minimal.
If the optimal solution should be maximal, then input data should be inverted before passing it to the solver.

The original algroithm requires that input data must be positive (zero or greater).
If "cost" values can be negative according to the application domain, then data must be transformed before passing it to the solver.

The solver doesn't allow `NaN` or `Infinity` values for "cost" values represented by floating-point types.
The algorithm is optimized for performance and tries to avoid unnecessary work. That's why explicit data validation is skipped.

If input data are unreliable, they must be validated. The library provides validation functions for different types in `utils.h` file.

The original algorithm was developed for square matrices, but the solver also handles rectangular matrices as well.
For solving rectangular matrices container type must implement a `resize` member function. Note that built-in matrix type and adapters implement this interface.



## Portability

The project is developing under GNU/Linux OS with GCC compiler and usualy not tested under other OS and compilers.
But in the project not used OS or compiler specific features (types, attributes, etc) so it's expected that the project will be normally work under other platforms.  

For easy integration of the library into existing projects, adapters are provided for several of the most well-known libraries:
 - Armadillo;  
 - Boost;  
 - Eigen;  
 - OpenCV;  
 - matrices based on `std::vector`.  



## Development

The source code is managed using git. The main repository is hosted at [gitlab](https://gitlab.com/Gluttton/munkres-cpp) and the mirror is hosted at [github](https://github.com/Gluttton/munkres-cpp).
To prevent project complications, a separate branch `devel` is used for development.
Using of gitlab allows to implement CI process.
The current CI implements the following steps:  
 - get the source code from `devel` branch;  
 - build and launch unit tests;  
 - analyze test coverage;  
 - build examples;  
 - build benchmarks.

CI is executed inside the Docker container.
The container is created automatically by commit in `docker` branch.

All CI steps are defined inside standard GitLab script: `.gitlab.yaml`.



Requirements:  
 - [GCC](https://gcc.gnu.org/) (tested on 4.6.3, 6.3.0);  
 - [GNU Make](https://www.gnu.org/software/make/);  
 - [CMake](http://www.cmake.org/) (2.8.12);  
 - the test suite requires the [Google C++ Test Framework](http://code.google.com/p/googletest/);  
 - microbenchmaring requires [Celero](https://github.com/DigitalInBlue/Celero);  
 - code coverage requires [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) and lcov.  



For development purpose in the project implemented several build targets.
All of them help to continuously check correctness of algorithm implementation, performance, memory management, etc.
To configure project in development mode checkout on ```devel``` branch.

Launch of unit tests.
The project contains unit tests to build and launch it performs the following steps:
```
$ git clone https://github.com/gluttton/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake ..
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
$ git clone https://github.com/gluttton/munkres-cpp.git
$ cd munkres-cpp
$ mkdir build && cd build
$ cmake ..
$ make benchmarks
```
To get comparable results it's required to generate data set wich will be used for all benchmarks:
```
$ benchmarks/generator {dim_1 dim_2 ... dim_n}
```
Where every ```dim_x``` parameter generate square matrix dith ```dim_x``` dimension.
To launch microbenchmark performs any following command:
```
$ benchmarks/tests/munkresbenchmark
```



## Bug reporting and work to be done

Check the [issues list at GitLab](https://gitlab.com/Gluttton/munkres-cpp/issues?scope=all&utf8=%E2%9C%93&state=opened).
