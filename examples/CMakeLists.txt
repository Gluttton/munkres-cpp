add_executable (example_01
    EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_01.cpp
)
target_link_libraries (example_01
    PRIVATE lp::munkres-cpp
)

add_executable (example_02
    EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_02.cpp
)
target_link_libraries (example_02
    PRIVATE lp::munkres-cpp
)

find_package (Boost COMPONENTS system)
add_executable (example_03
    EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_03.cpp
)
target_link_libraries (example_03
    PRIVATE lp::munkres-cpp
    PRIVATE Boost::system
)

add_executable (example_04
    EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_04.cpp
)
target_link_libraries (example_04
    PRIVATE lp::munkres-cpp
    PRIVATE Boost::system
)

add_executable (example_05
    EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_05.cpp
)
target_link_libraries (example_05
    PRIVATE lp::munkres-cpp
    PRIVATE Boost::system
)

add_executable (example_06
    EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_06.cpp
)
target_link_libraries (example_06
    PRIVATE lp::munkres-cpp
)

add_custom_target (examples)
add_dependencies  (examples
    example_01
    example_02
    example_03
    example_04
    example_05
    example_06
)
