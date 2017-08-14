cmake_minimum_required(VERSION 3.8.2)
project(options VERSION 0.0.1 LANGUAGES CXX)

FILE(GLOB_RECURSE INCLUDE_FILES include/*.h)
FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/glia/common")

add_library(options STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(options PUBLIC ${Boost_LIBRARIES})