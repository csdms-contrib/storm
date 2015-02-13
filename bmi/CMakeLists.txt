cmake_minimum_required(VERSION 2.6)

project (storm)

set (STORM_VERSION 0.2)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/stormc.pc.cmake
                ${CMAKE_CURRENT_SOURCE_DIR}/stormc.pc)

set (BUILD_SHARED_LIBS ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set (bmi_storm_lib_SRCS bmi_storm.c storm.c)
add_library (bmi_stormc ${bmi_storm_lib_SRCS} )

########### Storm main ###############

set (storm_sources main.c storm.c)
add_executable (stormc ${storm_sources})

########### Install files ###############

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/stormc 
        DESTINATION bin
	COMPONENT storm)
install(TARGETS bmi_stormc 
        DESTINATION lib 
	COMPONENT storm)
install(FILES bmi_storm.h
        DESTINATION include/storm
	COMPONENT storm)
install(FILES stormc.pc 
        DESTINATION lib/pkgconfig)
