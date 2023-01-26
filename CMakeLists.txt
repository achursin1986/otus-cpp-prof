cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(application application.cpp)
set_target_properties(application PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(application PRIVATE include)
target_compile_options(application PRIVATE  -g  )
