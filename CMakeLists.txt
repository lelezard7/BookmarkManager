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
target_link_libraries(BookmarkManager PRIVATE htmlhelp)


set_target_properties(BookmarkManager PROPERTIES
											CXX_STANDARD 11
											CXX_STANDARD_REQUIRED TRUE)
											
add_custom_command(TARGET BookmarkManager POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${CMAKE_CURRENT_SOURCE_DIR}/${BKM_HELP}"
					$<TARGET_FILE_DIR:BookmarkManager>)			
add_custom_command(TARGET BookmarkManager POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_if_different
					"${CMAKE_CURRENT_SOURCE_DIR}/${BKM_HELP}"
					"${PROJECT_BINARY_DIR}")