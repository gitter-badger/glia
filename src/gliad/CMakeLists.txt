cmake_minimum_required(VERSION 3.8.2)
project(gliad VERSION 0.0.1 LANGUAGES CXX)

file(GLOB PROTO_FILES ${CMAKE_SOURCE_DIR}/src/common/proto/*.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
protobuf_generate_grpc_cpp(PROTO_GRPC_SRCS PROTO_GRPC_HDRS ${PROTO_FILES})

FILE(GLOB_RECURSE INCLUDE_FILES include/*.h)
FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp)

include_directories("${options_SOURCE_DIR}/include")
include_directories("${logging_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(gliad
    ${SOURCE_FILES}
    ${INCLUDE_FILES}
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    ${PROTO_GRPC_SRCS}
    ${PROTO_GRPC_HDRS})

target_link_libraries(gliad PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    ${Protobuf_LIBRARIES}
    mstch::mstch
    options
    logging)