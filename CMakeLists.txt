cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

project(class-system-display LANGUAGES CXX VERSION 1.6.2)

find_package(Qt5 COMPONENTS Core Widgets Network CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS display/*.h display/*.cc)
file(GLOB_RECURSE FORMS CONFIGURE_DEPENDS display/*.ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt5_wrap_ui(FORM_SOURCES ${FORMS})

configure_file(display/version.h.in version.h)

add_executable(
  class-system-display
  ${SOURCES} ${FORM_SOURCES} resources/display.qrc resources/win.rc
  ${SHARED_SRC}
)

target_link_libraries(
  class-system-display PRIVATE
  Qt5::Core Qt5::Widgets Qt5::Network
)

target_include_directories(class-system-display PRIVATE display/include)


target_precompile_headers(
  class-system-display PRIVATE display/common.h
)

if(${WIN32} AND NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set_property(
    TARGET class-system-display PROPERTY
    WIN32_EXECUTABLE ON
  )
endif()
