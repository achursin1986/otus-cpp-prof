cmake_minimum_required(VERSION 3.5)

project(application CXX)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(application VERSION ${PROJECT_VERSION})
configure_file(version.h.in include/version.h)

add_executable(application application.cpp)
set_target_properties(application PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(application PRIVATE include)
target_compile_options(application PRIVATE  -g  )

install(TARGETS application RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)

