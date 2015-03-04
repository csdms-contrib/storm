cmake_minimum_required(VERSION 2.6)

##### Storm main #########################

set(storm_sources main.c storm.c storm_compute.c storm_output.c)
add_executable(storm ${storm_sources})
target_link_libraries(storm m)

set(storm_data_files 
  ${data_dir}/test0.in 
  ${data_dir}/test1.in 
  ${data_dir}/test2.in)

##### Install files ######################

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/storm
        DESTINATION bin
	COMPONENT storm)
install(FILES ${storm_data_files}
        DESTINATION share/storm/data
	COMPONENT storm)
