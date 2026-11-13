cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(test_file_sequence)

if(NOT DEFINED APP_HW_TARGET)
  set(APP_HW_TARGET XK-EVK-XU316)
endif()

set(APP_INCLUDES src)
include(${CMAKE_CURRENT_LIST_DIR}/../../examples/deps.cmake)
set(XMOS_SANDBOX_DIR ${CMAKE_CURRENT_LIST_DIR}/../../..)
XMOS_REGISTER_APP()
