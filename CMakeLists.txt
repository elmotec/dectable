# CMakeLists files in this project can
# refer to the root source directory of the project as ${dectable_SOURCE_DIR} and
# to the root binary directory of the project as ${dectable_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
set(PROJECT_NAME dectable)
project(${PROJECT_NAME} C CXX)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(src)

option(TEST "Builds the test subproject" OFF)

if(TEST)
    add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
    enable_testing()
    set(TEST_PROJECT_NAME test${PROJECT_NAME})
    include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})
    file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
    add_executable(${TEST_PROJECT_NAME} ${TEST_SRC_FILES})
    add_dependencies(${TEST_PROJECT_NAME} googletest)
    target_link_libraries(${TEST_PROJECT_NAME}
        ${PROJECT_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${CMAKE_THREAD_LIBS_INIT}
        )
    add_test(testdectable ${TEST_PROJECT_NAME})
endif()
