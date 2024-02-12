cmake_minimum_required(VERSION 3.11)
project(hw7)
 
# Are we in the wrong directory?
if (CMAKE_SOURCE_DIR MATCHES "[Hh][Ww]([0-9])$"
   AND NOT PROJECT_NAME MATCHES "${CMAKE_MATCH_1}$")
    message(FATAL_ERROR "Building ${PROJECT_NAME} in ${CMAKE_SOURCE_DIR}")
endif()
 
# Add compiler options
add_compile_options(-Wall -Wextra -Wpedantic -std=c++17)
 
# Create the library from CountSort.cc:
add_library(${PROJECT_NAME} CountSort.cc)
 
# Create the executable from the source file TestCountSort.cc:
add_executable(TestCountSort TestCountSort.cc)
target_link_libraries(TestCountSort ${PROJECT_NAME})
 
# Create a tar file every time:
#add_custom_target(${PROJECT_NAME}.tar ALL COMMAND
#    tar -cf ${PROJECT_NAME}.tar *.cc *.h CMakeLists.txt)
