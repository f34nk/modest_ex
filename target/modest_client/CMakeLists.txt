cmake_minimum_required(VERSION 3.0)
project(modest_client)

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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/../Modest/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/../Modest/lib")

message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

# make sure that erlang and pthread gets linked as last
# https://cmake.org/pipermail/cmake/2009-February/026779.html
set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE} -lerl_interface -lei -lpthread")

add_executable(
	${PROJECT_NAME}
	modest_client.c
  handlers.c
  handle_find.c
  handle_serialize.c
  handle_attribute.c
  handle_text.c
  handle_remove.c
  handle_append.c
  handle_prepend.c
  handle_insert_before.c
  handle_insert_after.c
  handle_replace.c
  utils.c
  modest_find.c
  modest_serialize.c
  modest_attribute.c
  modest_text.c
  modest_remove.c
  modest_append.c
  modest_prepend.c
  modest_insert_before.c
  modest_insert_after.c
  modest_replace.c
  modest_slice.c
)

target_link_libraries(
  ${PROJECT_NAME}
  libmodest_static.a
)

# add target tests

add_subdirectory(test)
enable_testing()
file(GLOB_RECURSE TESTS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.c")
foreach(TEST ${TESTS})
  get_filename_component(TEST ${TEST} NAME_WE)
  add_test(NAME ${TEST} COMMAND ${TEST})
endforeach()