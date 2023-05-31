cmake_minimum_required(VERSION 3.5)

project(fashio_mnist CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package( Eigen3 REQUIRED )
add_executable(fashio_mnist fashio_mnist.cpp tf_classifier.cpp helpers.cpp)
set_target_properties(fashio_mnist PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(fashio_mnist PRIVATE include)
target_link_libraries(fashio_mnist tensorflow Eigen3::Eigen)
#target_compile_options(fashio_mnist PRIVATE -g)

