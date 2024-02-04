find_package(libhv CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

file(GLOB_RECURSE SERVER_SRC ./*.h ./*.cc)

add_executable(
  class-system-server
  ${SERVER_SRC}
  ${PROTO_SRC}
)

target_link_libraries(class-system-server PRIVATE hv protobuf::libprotobuf unofficial::sqlite3::sqlite3)
