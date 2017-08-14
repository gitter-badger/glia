cmake_minimum_required(VERSION 3.8.2)
project(glia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tools/cmake/")

find_package(Threads)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.64 REQUIRED COMPONENTS program_options filesystem log)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package (GRPC REQUIRED)
link_libraries(grpc++_unsecure ${GRPC_LIBRARIES} ${PROTOBUF_LIBRARY})

find_package(Protobuf 3.3.0 REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

find_package(RapidJSON REQUIRED)

find_package(mstch REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src/common/logging)
add_subdirectory(src/common/options)
add_subdirectory(src/gliac)
add_subdirectory(src/gliad)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

#set (git_cmd "git")
#set (git_arg "--version")
#message(STATUS "git cmd: ${git_cmd}")
#execute_process(COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/build/Hello
#    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
