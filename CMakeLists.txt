cmake_minimum_required(VERSION 3.5)

project(print_ip CXX)

add_executable(print_ip print_ip.cpp)
set_target_properties(print_ip PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(print_ip PRIVATE include)
target_compile_options(print_ip PRIVATE )

install(TARGETS print_ip RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "print_ip")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

