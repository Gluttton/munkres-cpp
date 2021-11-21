find_package (Armadillo)
find_package (Boost     COMPONENTS  system)
find_package (Eigen3)
find_package (OpenCV    COMPONENTS  core)

if (ARMADILLO_FOUND)
    add_definitions (-DMUNKRES_CPP_ARMADILLO)
endif ()
if (Boost_FOUND)
    add_definitions (-DMUNKRES_CPP_BOOST)
endif ()
if (EIGEN3_FOUND)
    add_definitions (-DMUNKRES_CPP_EIGEN3)
endif ()
if (OpenCV_FOUND)
    add_definitions (-DMUNKRES_CPP_OPENCV)
    set (CMAKE_EXE_LINKER_FLAGS "-l${OpenCV_LIBS}")
endif ()

include_directories (${OPENCV_INCLUDE_DIRS})
include_directories (${ARMADILLO_INCLUDE_DIRS})
include_directories (${EIGEN3_INCLUDE_DIR})

if (NOT DEFINED MUNKRES_CPP_VALUE_TYPE)
    set (MUNKRES_CPP_VALUE_TYPE long\ unsigned\ int)
endif ()
if (NOT DEFINED MUNKRES_CPP_MATRIX_TYPE)
    set (MUNKRES_CPP_MATRIX_TYPE matrix_eigen)
endif ()

add_definitions (-DMUNKRES_CPP_VALUE_TYPE=${MUNKRES_CPP_VALUE_TYPE})
add_definitions (-DMUNKRES_CPP_MATRIX_TYPE=${MUNKRES_CPP_MATRIX_TYPE})


# Data generator.
include_directories (${OpenCV_INCLUDE_DIRS})
add_executable (
    generator EXCLUDE_FROM_ALL
    ${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
)


# Benchmark based on the Celero Framework.
ExternalProject_Add (
    Celero
    GIT_REPOSITORY "https://github.com/DigitalInBlue/Celero.git"
    GIT_TAG "v2.8.2"
    PATCH_COMMAND eval "sed 's/CACHE.*FORCE//g' CMakeLists.txt > CMakeLists.mod && mv CMakeLists.mod CMakeLists.txt"
    CMAKE_ARGS "-DCELERO_ENABLE_EXPERIMENTS=OFF;-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/Celero"
    BINARY_DIR "${PROJECT_BINARY_DIR}/CeleroBuild"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (Celero PROPERTIES EXCLUDE_FROM_ALL TRUE)
set (CELERO_FOUND true)
set (CELERO_INCLUDE_DIR "${PROJECT_BINARY_DIR}/Celero/include")
set (CELERO_LIBRARY "${PROJECT_BINARY_DIR}/CeleroBuild/libcelero.so")

set (MunkresCppBenchmarkCelero_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
add_executable (munkresbenchmark EXCLUDE_FROM_ALL ${MunkresCppBenchmarkCelero_SOURCES})
include_directories (${CELERO_INCLUDE_DIR})
target_link_libraries (munkresbenchmark ${OpenCV_LIBS} ${CELERO_LIBRARY})
add_dependencies (munkresbenchmark Celero)


# Prevent launch tests before will be generated test data set.
set (BenchmarkDataSet ${PROJECT_BINARY_DIR}/matrices.txt)
add_custom_command (
    OUTPUT ${BenchmarkDataSet}
    COMMAND cd ${PROJECT_BINARY_DIR} && ./benchmarks/generator 20
)
add_custom_target (generate_benchmark_dataset DEPENDS ${BenchmarkDataSet})
add_dependencies (generate_benchmark_dataset generator)

add_dependencies (munkresbenchmark generate_benchmark_dataset)


add_custom_target  (benchmarks)
add_dependencies (
    benchmarks
    munkresbenchmark
    generator
)
