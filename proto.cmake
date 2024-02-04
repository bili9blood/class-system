find_package(Protobuf CONFIG REQUIRED)

set(PROTO_OUTPUT_DIR ${CMAKE_BINARY_DIR}/proto)
set(PROTO_INPUT_DIR ${CMAKE_SOURCE_DIR}/proto)

if(EXISTS ${PROTO_OUTPUT_DIR} AND IS_DIRECTORY ${PROTO_OUTPUT_DIR})
  set(PROTO_META_BASE_DIR ${PROTO_OUTPUT_DIR})
else()
  file(MAKE_DIRECTORY ${PROTO_OUTPUT_DIR})
  set(PROTO_META_BASE_DIR ${PROTO_OUTPUT_DIR})
endif()

# 设置protoc的搜索路径
LIST(APPEND PROTO_FLAGS -I${PROTO_INPUT_DIR})

# 获取需要编译的proto文件
file(GLOB MSG_PROTOS CONFIGURE_DEPENDS ${PROTO_INPUT_DIR}/*.proto)
set(_PROTO_SRC "")
set(PROTO_HDRS "")

foreach(msg ${MSG_PROTOS})
  get_filename_component(FIL_WE ${msg} NAME_WE)

  list(APPEND _PROTO_SRC "${PROTO_OUTPUT_DIR}/${FIL_WE}.pb.cc")
  list(APPEND PROTO_HDRS "${PROTO_OUTPUT_DIR}/${FIL_WE}.pb.h")

  # 使用自定义命令
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

# 设置文件属性为 GENERATED
set_source_files_properties(${_PROTO_SRC} ${_PROTO_HDR} PROPERTIES GENERATED TRUE)

# 添加自定义target
add_custom_target(generate_message ALL
  DEPENDS ${_PROTO_SRC} ${_PROTO_HDR}
  COMMENT "generate message target"
  VERBATIM
)

file(GLOB PROTO_SRC CONFIGURE_DEPENDS ${PROTO_OUTPUT_DIR}/*.pb.cc)
