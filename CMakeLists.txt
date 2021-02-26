cmake_minimum_required(VERSION 3.5)

project(BookmarkManager	LANGUAGES C	CXX)

include(src_variables.cmake)


#			Visual Studio
foreach(i ${BKM_ALL})
	get_filename_component(FILE_DIR ${i} DIRECTORY)
	source_group(${FILE_DIR} FILES ${i})
endforeach()

add_executable(BookmarkManager WIN32 ${BKM_ALL} src_variables.cmake)

#			Libraries
target_link_libraries(BookmarkManager PRIVATE comctl32)


set_target_properties(BookmarkManager PROPERTIES
											CXX_STANDARD 11
											CXX_STANDARD_REQUIRED TRUE)
