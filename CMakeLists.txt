cmake_minimum_required(VERSION 3.21)

option(BUILD_DISPLAY_AND_MANAGE "Build Display and Manage" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(class-system LANGUAGES CXX VERSION 1.0.0)

find_package(protobuf CONFIG REQUIRED)

if(${BUILD_DISPLAY_AND_MANAGE})
  find_package(Qt5 COMPONENTS Core Widgets CONFIG REQUIRED)
endif()

find_package(libhv CONFIG REQUIRED)

include(./proto.cmake)

include_directories(${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/proto include ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SHARED_SRC shared/*.h shared/*.cc)

if(${BUILD_DISPLAY_AND_MANAGE})
  add_subdirectory(./display/)
  add_subdirectory(./manage/)
endif()

add_subdirectory(./server/)
