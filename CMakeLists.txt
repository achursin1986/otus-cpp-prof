cmake_minimum_required(VERSION 3.10)

project(ip_filter)


find_package(GTest REQUIRED)

add_executable(ip_filter ip_filter.cpp)
add_executable(test_gtest test_gtest.cpp)

set_target_properties(ip_filter test_gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)



set_target_properties(test_gtest PROPERTIES
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)




target_link_libraries(test_gtest
    gtest
    pthread
)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(test_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

