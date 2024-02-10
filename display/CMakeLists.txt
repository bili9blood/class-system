file(GLOB_RECURSE DISPLAY_SRC CONFIGURE_DEPENDS ./*.h ./*.cc)
file(GLOB_RECURSE DISPLAY_UI_FILES CONFIGURE_DEPENDS ./*.ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt5_wrap_ui(DISPLAY_FORM_SRC ${DISPLAY_UI_FILES})

add_executable(
  class-system-display
  ${DISPLAY_SRC} ${DISPLAY_FORM_SRC} ../resources/display.qrc
  ${SHARED_SRC}
)

target_link_libraries(
  class-system-display PRIVATE
  Qt5::Core Qt5::Widgets
  hv protobuf::libprotobuf
)

target_include_directories(
  class-system-display PRIVATE ${CMAKE_BINARY_DIR}/display
)

target_precompile_headers(
  class-system-display PRIVATE common.h
)

if(${WIN32} AND NOT ${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set_property(
    TARGET class-system-display PROPERTY
    WIN32_EXECUTABLE ON
  )
endif()

add_dependencies(class-system-display generate_message)
