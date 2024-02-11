find_package(Protobuf CONFIG REQUIRED)

set(PROTO_OUTPUT_DIR ${CMAKE_BINARY_DIR}/proto)
set(PROTO_INPUT_DIR ${CMAKE_SOURCE_DIR}/proto)

if(EXISTS ${PROTO_OUTPUT_DIR} AND IS_DIRECTORY ${PROTO_OUTPUT_DIR})
  set(PROTO_META_BASE_DIR ${PROTO_OUTPUT_DIR})
else()
  file(MAKE_DIRECTORY ${PROTO_OUTPUT_DIR})
  set(PROTO_META_BASE_DIR ${PROTO_OUTPUT_DIR})
endif()

LIST(APPEND PROTO_FLAGS -I${PROTO_INPUT_DIR})

file(GLOB MSG_PROTOS CONFIGURE_DEPENDS ${PROTO_INPUT_DIR}/*.proto)
set(PROTO_SRC "")
set(PROTO_HDRS "")

if("${PROTOBUF_PROTOC_EXECUTABLE}" STREQUAL "")
  set(PROTOBUF_PROTOC_EXECUTABLE "protoc")
endif()

foreach(msg ${MSG_PROTOS})
  get_filename_component(FIL_WE ${msg} NAME_WE)

  list(APPEND PROTO_SRC "${PROTO_OUTPUT_DIR}/${FIL_WE}.pb.cc")
  list(APPEND PROTO_HDRS "${PROTO_OUTPUT_DIR}/${FIL_WE}.pb.h")

  add_custom_command(
    OUTPUT "${PROTO_OUTPUT_DIR}/${FIL_WE}.pb.cc"
    "${PROTO_OUTPUT_DIR}/${FIL_WE}.pb.h"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS --cpp_out ${PROTO_META_BASE_DIR}
    -I${PROTO_INPUT_DIR}
    ${msg}
    DEPENDS ${msg}
    COMMENT "Running C++ protocol buffer compiler on ${msg}"
    VERBATIM
  )
endforeach()

set_source_files_properties(${PROTO_SRC} ${_PROTO_HDR} PROPERTIES GENERATED TRUE)

add_custom_target(generate-message ALL
  DEPENDS ${PROTO_SRC} ${_PROTO_HDR}
  COMMENT "generate message target"
  VERBATIM
)
