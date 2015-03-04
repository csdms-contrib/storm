cmake_minimum_required(VERSION 2.6)

##### Build shared library ###############

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/storm.pc.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/storm.pc)

set(BUILD_SHARED_LIBS ON)

set(bmi_storm_lib_srcs 
  bmi_storm.c 
  bmi.c
  ${model_dir}/storm.c 
  ${model_dir}/storm_compute.c)

add_library(bmi_storm ${bmi_storm_lib_srcs})

##### Install files ######################

install(TARGETS bmi_storm
        DESTINATION lib 
	COMPONENT storm)
install(FILES bmi_storm.h bmi.h bmilib.h
        DESTINATION include/storm
	COMPONENT storm)
install(FILES storm.pc 
        DESTINATION lib/pkgconfig)
