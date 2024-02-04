cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

project(class-system LANGUAGES CXX VERSION 1.0.0)

find_package(protobuf CONFIG REQUIRED)
include(./proto.cmake)

include_directories(${CMAKE_BINARY_DIR} include)

add_subdirectory(./display/)
add_subdirectory(./manage/)
add_subdirectory(./server/)
