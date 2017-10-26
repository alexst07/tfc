include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(tfc ${SRCS})
target_link_libraries(tfc tf_proto)
