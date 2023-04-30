cmake_minimum_required(VERSION 3.5)

project(async_test CXX)
add_executable(async_test test.cpp)
set_target_properties(async_test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(async_test PRIVATE include)
target_link_libraries(async_test async)


add_library(async SHARED async.cpp)
target_include_directories(async PRIVATE include)
target_link_libraries(async pthread)



install(TARGETS async_test RUNTIME DESTINATION bin)
install(TARGETS async LIBRARY DESTINATION lib)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "async")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS YES)
include(CPack)
