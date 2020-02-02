cmake_minimum_required(VERSION 3.0)
project(modest_worker_tests)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -std=c99") # c
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcomment -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_REENTRANT")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG") # Enable if needed
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-write-strings")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../handlers")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../utils")

message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE UTILS "../utils/*.c")
file(GLOB_RECURSE HANDLERS "../handlers/*.c")

file(GLOB_RECURSE TESTS "*_test.c")
foreach(TEST ${TESTS})
  message("TEST = ${TEST}")
  get_filename_component(TEST_NAME ${TEST} NAME_WE)
  add_executable(${TEST_NAME} ${TEST})
  target_link_libraries(
    ${TEST_NAME}
    libmodest_html.a
    libmodest_static.a
  )
  target_sources(
    ${TEST_NAME}
    PUBLIC
    ${UTILS}
  )
endforeach()

file(GLOB_RECURSE TESTS "bench*_test.c")
foreach(TEST ${TESTS})
  message("TEST = ${TEST}")
  get_filename_component(TEST_NAME ${TEST} NAME_WE)
  target_sources(
    ${TEST_NAME}
    PUBLIC
    ${HANDLERS}
  )
endforeach()

file(GLOB_RECURSE TESTS "handle_*_test.c")
foreach(TEST ${TESTS})
  # message("TEST = ${TEST}")
  get_filename_component(TEST_NAME ${TEST} NAME_WE)
  string(
    REGEX REPLACE
    "_test" ".c"
    TEST_SOUCRE
    ${TEST_NAME}
  )
  target_sources(
    ${TEST_NAME}
    PUBLIC
    ../handlers/${TEST_SOUCRE}
  )
endforeach()