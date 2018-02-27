cmake_minimum_required(VERSION 3.0)
project(modest_client_tests)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -std=c99") # c

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../../Modest/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/../../Modest/lib")

message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# myhtml

set(MYHTML_TESTS
  serialization_high_level
  modify_and_serialize
  string_manipulate_high_level
)

foreach(TEST ${MYHTML_TESTS})
  add_executable(
    ${TEST}
    myhtml/${TEST}.c
  )
endforeach()

set(TESTS ${TESTS} ${MYHTML_TESTS})

# link libraries for all tests
foreach(TEST ${TESTS})
  target_link_libraries(
    ${TEST}
    libmodest_static.a
  )
endforeach()