cmake_minimum_required(VERSION 3.8.2)
project(glia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost 1.58 REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIR})

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(SOURCE_FILES src/glia.cpp src/options.cpp)
add_executable(glia ${SOURCE_FILES})
target_link_libraries(glia LINK_PUBLIC ${Boost_LIBRARIES})

#set (git_cmd "git")
#set (git_arg "--version")
#message(STATUS "git cmd: ${git_cmd}")
#execute_process(COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/build/Hello
#    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
