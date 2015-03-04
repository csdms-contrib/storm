cmake_minimum_required(VERSION 2.6)

project(storm)

set(STORM_VERSION 0.1-bmi)

set(CMAKE_C_FLAGS "-ansi -Wall -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2")

set(model_dir ${CMAKE_HOME_DIRECTORY}/storm)
set(bmi_dir ${CMAKE_HOME_DIRECTORY}/bmi)

include_directories(${CMAKE_HOME_DIRECTORY})
include_directories(${model_dir})
include_directories(${bmi_dir})

add_subdirectory(bmi)
add_subdirectory(storm)
