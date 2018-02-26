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
	modest.c
)

target_link_libraries(
  ${PROJECT_NAME}
  libmodest_static.a
)

# add_subdirectory(test)
# enable_testing()
# add_test(NAME "test_id" COMMAND test_id)