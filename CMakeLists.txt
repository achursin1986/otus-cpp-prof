cmake_minimum_required(VERSION 3.5)

project(bulk_server CXX)
add_executable(bulk_server bulk_server.cpp)
set_target_properties(bulk_server PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(bulk_server PRIVATE include)
target_link_libraries(bulk_server async)


add_library(async SHARED async.cpp)
target_include_directories(async PRIVATE include)
target_link_libraries(async pthread)



install(TARGETS bulk_server RUNTIME DESTINATION bin)
install(TARGETS async LIBRARY DESTINATION lib)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "bulk_server")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS YES)
include(CPack)
