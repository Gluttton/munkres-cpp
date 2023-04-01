find_package (Armadillo)
find_package (Boost     COMPONENTS  system)
find_package (Eigen3)
find_package (OpenCV    COMPONENTS  core)
find_package (Qt5Gui)

enable_testing ()


# Framework for writing tests.
include (ExternalProject)
ExternalProject_Add (googletest
    GIT_REPOSITORY  "https://github.com/google/googletest.git"
    GIT_TAG         "release-1.10.0"
    PATCH_COMMAND    git apply "${PROJECT_SOURCE_DIR}/tests/switch-on-Python-3.patch"
                 &&  git apply "${PROJECT_SOURCE_DIR}/tests/increase-length-of-type-list.patch"
    COMMAND          ./googletest/scripts/pump.py googletest/include/gtest/internal/gtest-type-util.h.pump
    CMAKE_ARGS      "-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR      "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    BINARY_DIR      "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    INSTALL_COMMAND ""
    UPDATE_DISCONNECTED 1
)
set_target_properties (googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)
set (GTEST_ROOT             "${CMAKE_CURRENT_BINARY_DIR}/googletest")
set (GTEST_FOUND            true)
set (GTEST_INCLUDE_DIRS     "${GTEST_ROOT}/googletest/include")
set (GTEST_LIBRARIES        "${GTEST_ROOT}/lib/libgtest.a")
set (GTEST_MAIN_LIBRARIES   "${GTEST_ROOT}/lib/libgtest_main.a")
set (GTEST_BOTH_LIBRARIES   ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})



add_executable (munkrestest EXCLUDE_FROM_ALL ${MunkresCppTest_SOURCES})

target_compile_options (munkrestest
    PRIVATE -fprofile-arcs -ftest-coverage
    PRIVATE -Wall -Wextra
)
target_link_options (munkrestest
    PRIVATE -fprofile-arcs -ftest-coverage
)

target_sources (munkrestest
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/munkres_test.cpp
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/matrix_test.cpp
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/utils_test.cpp
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/adapters_test.cpp
)

target_compile_definitions (munkrestest
    PRIVATE -DARMADILLO_FOUND=$<BOOL:${ARMADILLO_FOUND}>
    PRIVATE -DBOOST_FOUND=$<BOOL:${BOOST_FOUND}>
    PRIVATE -DEIGEN3_FOUND=$<BOOL:${EIGEN3_FOUND}>
    PRIVATE -DOPENCV_FOUND=$<BOOL:${OpenCV_FOUND}>
    PRIVATE -DQT5_FOUND=$<BOOL:${Qt5Gui_FOUND}>
)

target_include_directories (munkrestest
    PRIVATE ${GTEST_INCLUDE_DIRS}
    PRIVATE ${OPENCV_INCLUDE_DIRS}
    PRIVATE ${ARMADILLO_INCLUDE_DIRS}
    PRIVATE ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries (munkrestest
    PRIVATE lp::munkres-cpp
    PRIVATE Boost::system
    PRIVATE ${GTEST_BOTH_LIBRARIES}
    PRIVATE ${OpenCV_LIBS}
    PRIVATE Qt5::Gui
    PRIVATE gcov
    PRIVATE pthread
)
add_custom_target (tests)
add_dependencies  (tests munkrestest)
add_dependencies  (munkrestest googletest)
add_test (MunkresCppTest muknrestest)


# Test coverage report.
set (Coverage_REPORT ${PROJECT_BINARY_DIR}/coverage.info)
set (Coverage_DIR    ${PROJECT_BINARY_DIR}/coverage)
set (LcovRc          "--rc" "lcov_branch_coverage=1")
add_custom_command (
    OUTPUT  ${Coverage_REPORT}
    COMMAND lcov -q -c -f -b . -d ${PROJECT_BINARY_DIR}/tests -o ${Coverage_REPORT} ${LcovRc}
    COMMAND lcov -e ${Coverage_REPORT} '${PROJECT_SOURCE_DIR}/src/*' -o ${Coverage_REPORT} ${LcovRc}
    COMMAND genhtml ${Coverage_REPORT} --legend --demangle-cpp -f -q -o ${Coverage_DIR} ${LcovRc}
    DEPENDS munkrestest
)
add_custom_target (coverage DEPENDS ${Coverage_REPORT})
