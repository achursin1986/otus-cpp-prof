cmake_minimum_required(VERSION 3.5)

project(bulk CXX)

add_executable(bulk main.cpp)
set_target_properties(bulk PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(bulk PRIVATE include)
target_compile_options(bulk PRIVATE -g )

install(TARGETS bulk RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "bulk")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
