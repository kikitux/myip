cmake_minimum_required(VERSION 2.8)
project(builtin_myip)
set(BASH_DIR ../../aports/main/bash/src/bash-4.3)
set(INCLUDE_DIR ../lib ${BASH_DIR} ${BASH_DIR}/include
  ${BASH_DIR}/builtins ${BASH_DIR}/examples/loadables
  ${BASH_DIR}/examples ${BASH_DIR}/lib
  ${BASH_DIR}/lib/termcap)
set(SOURCE_FILES ../lib/myexip.c ../lib/myexip.h ../lib/mylocalip.c ../lib/mylocalip.h ../lib/print_info.c ../lib/print_info.h)

SET(BUILD_SHARED_LIBRARIES ON)
SET(CMAKE_EXE_LINKER_FLAGS "-shared")
add_definitions("-fPIC -DHAVE_CONFIG_H -DSHELL")
add_executable(builtin_myip builtin_myip.c ${SOURCE_FILES})
target_include_directories(builtin_myip PRIVATE ${INCLUDE_DIR})

MESSAGE( STATUS "BASH_DIR ${BASH_DIR}" )
MESSAGE( STATUS "INCLUDE_DIR ${INCLUDE_DIR}" )
MESSAGE( STATUS "SOURCE_FILES ${SOURCE_FILES}" )
