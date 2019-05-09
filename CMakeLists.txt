cmake_minimum_required(VERSION 2.8)
project(vmqtt)

# Set cflags
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -g -fno-strict-aliasing -O2 -Wall -export-dynamic -Wall -pipe  -D_GNU_SOURCE -D_REENTRANT -fPIC -Wno-deprecated -m64)


aux_source_directory(. DIR_ROOT_SRCS)
add_subdirectory(libco)

add_executable(vmqtt ${DIR_ROOT_SRCS})
target_link_libraries(vmqtt colib_static pthread dl)