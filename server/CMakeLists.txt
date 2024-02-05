find_package(libhv CONFIG REQUIRED)

file(GLOB_RECURSE SERVER_SRC ./*.h ./*.cc)

add_executable(
  class-system-server
  ${SERVER_SRC}
  ${PROTO_SRC}
)

target_link_libraries(
  class-system-server PRIVATE
  hv protobuf::libprotobuf sqlite3
)

target_compile_definitions(
  class-system-server PRIVATE
  _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
)
