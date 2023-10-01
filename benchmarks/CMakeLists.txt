find_package (Armadillo)
find_package (Boost     COMPONENTS  system)
find_package (Eigen3)
find_package (OpenCV    COMPONENTS  core)


# Benchmark based on the Celero Framework.
include (ExternalProject)
ExternalProject_Add (Celero
    GIT_REPOSITORY "https://github.com/DigitalInBlue/Celero.git"
    GIT_TAG "v2.8.3"
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


if (NOT DEFINED MUNKRES_CPP_VALUE_TYPE)
    set (MUNKRES_CPP_VALUE_TYPE long\ unsigned\ int)
endif ()
if (NOT DEFINED MUNKRES_CPP_MATRIX_TYPE)
    set (MUNKRES_CPP_MATRIX_TYPE matrix_eigen)
endif ()


# Data generator.
add_executable (generator EXCLUDE_FROM_ALL
    ${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp
)

target_compile_definitions (generator
    PRIVATE MUNKRES_CPP_VALUE_TYPE=${MUNKRES_CPP_VALUE_TYPE}
    PRIVATE MUNKRES_CPP_MATRIX_TYPE=${MUNKRES_CPP_MATRIX_TYPE}
)

target_include_directories (generator
    PRIVATE ${CELERO_INCLUDE_DIR}
    PRIVATE ${ARMADILLO_INCLUDE_DIRS}
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries (generator
    PRIVATE lp::munkres-cpp
    PRIVATE ${OpenCV_LIBS}
)


# Test.
add_executable (munkresbenchmark
    EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
)

target_compile_options (munkresbenchmark
    PRIVATE -O3
)

target_compile_definitions (munkresbenchmark
    PRIVATE -DARMADILLO_FOUND=$<BOOL:${ARMADILLO_FOUND}>
    PRIVATE -DBOOST_FOUND=$<BOOL:${BOOST_FOUND}>
    PRIVATE -DEIGEN3_FOUND=$<BOOL:${EIGEN3_FOUND}>
    PRIVATE -DOPENCV_FOUND=$<BOOL:${OpenCV_FOUND}>
    PRIVATE -DQT5_FOUND=$<BOOL:${Qt5Gui_FOUND}>
    PRIVATE MUNKRES_CPP_VALUE_TYPE=${MUNKRES_CPP_VALUE_TYPE}
    PRIVATE MUNKRES_CPP_MATRIX_TYPE=${MUNKRES_CPP_MATRIX_TYPE}
)

target_include_directories (munkresbenchmark
    PRIVATE ${CELERO_INCLUDE_DIR}
    PRIVATE ${ARMADILLO_INCLUDE_DIRS}
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries (munkresbenchmark
    PRIVATE lp::munkres-cpp
    PRIVATE Boost::system
    PRIVATE ${OpenCV_LIBS}
    PRIVATE ${CELERO_LIBRARY}
)

add_dependencies (munkresbenchmark Celero)


add_custom_target (benchmarks)
add_dependencies  (benchmarks
    generator
    munkresbenchmark
)
