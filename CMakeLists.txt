cmake_minimum_required(VERSION 3.5)
project(glia)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(SOURCE_FILES src/glia.cpp)
add_executable(glia ${SOURCE_FILES})

#set (git_cmd "git")
#set (git_arg "--version")
#message(STATUS "git cmd: ${git_cmd}")
#execute_process(COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/build/Hello
#    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
