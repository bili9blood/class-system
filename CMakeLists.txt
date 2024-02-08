cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(class-system LANGUAGES CXX VERSION 1.0.0)

find_package(protobuf CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets CONFIG REQUIRED)
find_package(libhv CONFIG REQUIRED)

include(./proto.cmake)

include_directories(${CMAKE_BINARY_DIR} include .)

file(GLOB_RECURSE SHARED_SRC shared/*.h shared/*.cc)

add_subdirectory(./display/)
add_subdirectory(./manage/)
add_subdirectory(./server/)
