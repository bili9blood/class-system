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
