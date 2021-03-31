cmake_minimum_required(VERSION 3.5)
project(BookmarkManager	LANGUAGES C	CXX)

include(saveModule_variables.cmake)

foreach(i ${SAVEMODULE_ALL})
	get_filename_component(FILE_DIR ${i} DIRECTORY)
	source_group(${FILE_DIR} FILES ${i})
endforeach()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
add_library(SaveModule SHARED ${SAVEMODULE_ALL} saveModule_variables.cmake)

target_include_directories(SaveModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
