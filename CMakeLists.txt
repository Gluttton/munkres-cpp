cmake_minimum_required  (VERSION 3.1)
project                 (munkres-cpp)
set (munkres-cpp_VERSION_MAJOR 3)
set (munkres-cpp_VERSION_MINOR 0)

add_library (munkres-cpp INTERFACE)
add_library (lp::munkres-cpp ALIAS munkres-cpp)

target_compile_features (munkres-cpp
    INTERFACE cxx_std_11
)

target_include_directories (munkres-cpp
    INTERFACE ${PROJECT_SOURCE_DIR}/src
)

install (DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

add_subdirectory (examples)
add_subdirectory (tests)
add_subdirectory (benchmarks)
