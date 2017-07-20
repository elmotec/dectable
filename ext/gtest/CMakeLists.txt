cmake_minimum_required(VERSION 2.8.11)
project(googletest-download NONE)

include(ExternalProject)

include(ExternalProject)
ExternalProject_Add(googletest
  #GIT_REPOSITORY    https://github.com/google/googletest.git
  #GIT_TAG           master
  #SOURCE_DIR        "${CMAKE_BINARY_DIR}/ext/gtest/googletest-src"
  #BINARY_DIR        "${CMAKE_BINARY_DIR}/ext/gtest/googletest-build"
  #CONFIGURE_COMMAND ""
  CMAKE_ARGS        "-DBUILD_GTEST=ON"
  PREFIX            "${CMAKE_CURRENT_BINARY_DIR}"
  # Disable install and test.
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include PARENT_SCOPE)

# Specify MainTest's link libraries
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBS_DIR ${binary_dir}/googlemock/gtest PARENT_SCOPE)
