cmake_minimum_required(VERSION 3.0)
project(gumbo_query_client_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../../gumbo-query/src")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/../../gumbo-query/lib")

message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

set(tests test_id)

add_executable(
  test_id
  ID.cpp
)

target_link_libraries(
  ${tests}
  libgq.a
  libgumbo.a
)

set_property(TARGET ${tests} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${tests} PROPERTY CXX_STANDARD_REQUIRED ON)
