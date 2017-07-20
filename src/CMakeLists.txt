# The extension is already found. Any number of sources could be listed here.
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library (${PROJECT_NAME} ${SRC_FILES})
include_directories(${COMMON_INCLUDES})
# Make sure the compiler can find include files for our DecTable library
# when other libraries or executables link to DecTable
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
