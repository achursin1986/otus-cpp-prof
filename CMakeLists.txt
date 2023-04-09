cmake_minimum_required(VERSION 3.5)

project(bayan CXX)


add_executable(bayan main.cpp)

find_package(Boost COMPONENTS program_options filesystem regex REQUIRED )
set_target_properties(bayan PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(bayan PRIVATE include)
target_compile_options(bayan PRIVATE -g )
target_link_libraries(bayan ${Boost_LIBRARIES} )

install(TARGETS bayan RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "bayan")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
