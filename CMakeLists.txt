cmake_minimum_required(VERSION 2.8)
project(tfc)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})

include(CheckCXXCompilerFlag)
include(cmake/utils.cmake)

#
# compile flags
#
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

#
# find packages
#
find_package(Eigen REQUIRED)
find_package(Threads)

#
# include directories
#
include_directories(SYSTEM ${Eigen_INCLUDE_DIRS})
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/third-party/google/protobuf/include/)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/third-party/google/tensorflow/)

#
# list tensorflow proto generated files
#
file(GLOB_RECURSE PROTO_SRCS "${PROJECT_SOURCE_DIR}/third-party/google/tensorflow/*.cc")
file(GLOB_RECURSE PROTO_HDRS "${PROJECT_SOURCE_DIR}/third-party/google/tensorflow/*.h")

#
# create tensorflow proto library
#
add_library(tf_proto SHARED ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(tf_proto ${PROJECT_SOURCE_DIR}/third-party/google/protobuf/lib/libprotobuf.so)
target_link_libraries(tf_proto ${CMAKE_THREAD_LIBS_INIT})

add_subdirectory(tools)
add_subdirectory(src)
