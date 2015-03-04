cmake_minimum_required(VERSION 2.6)

##### Storm main #########################

set(storm_sources main.c storm.c storm_compute.c storm_output.c)
add_executable(storm ${storm_sources})
target_link_libraries(storm m)

##### Install files ######################

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/storm
        DESTINATION bin
	COMPONENT storm)
