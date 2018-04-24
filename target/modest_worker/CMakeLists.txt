cmake_minimum_required(VERSION 3.0)
project(modest_worker)

# resolve wildcard
file(GLOB ERL_INTERFACE "${ERLANG_PATH}/../lib/erl_interface-*")
# make absolute
get_filename_component(ERL_INTERFACE ${ERL_INTERFACE} ABSOLUTE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -std=c99") # c
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wcomment -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_REENTRANT")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-write-strings")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${ERLANG_PATH}/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${ERL_INTERFACE}/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${ERL_INTERFACE}/lib")

#set(MODEST_HTML_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../modest_html")
set(MODEST_HTML_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../modest_html")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${MODEST_HTML_PATH}/src")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${MODEST_HTML_PATH}/libs/Modest/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${MODEST_HTML_PATH}/libs/vec/src")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${MODEST_HTML_PATH}/libs/map/src")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${MODEST_HTML_PATH}/libs/dmt/src")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${MODEST_HTML_PATH}/libs/Modest/lib")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${MODEST_HTML_PATH}/build")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/handlers")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/utils")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}")

message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# make sure that erlang and pthread gets linked as last
# https://cmake.org/pipermail/cmake/2009-February/026779.html
set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE} -lerl_interface -lei -lpthread")
set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE} -lmodest_html -lmodest_static")


file(GLOB_RECURSE HANDLERS "handlers/*.c")
file(GLOB_RECURSE UTILS "utils/*.c")

add_executable(
  ${PROJECT_NAME}
  ${UTILS}
  ${HANDLERS}
  modest_worker.c
  handle_send.c
)

# target_link_libraries(
#   ${PROJECT_NAME}
#   libmodest_static.a
#   libmodest_html.a
# )

# add target tests

add_subdirectory(test)
enable_testing()
file(GLOB_RECURSE TESTS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.c")
foreach(TEST ${TESTS})
  get_filename_component(TEST ${TEST} NAME_WE)
  add_test(NAME ${TEST} COMMAND ${TEST})
endforeach()