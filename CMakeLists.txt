cmake_minimum_required(VERSION 3.5)

project(BookmarkManager	LANGUAGES C	CXX)


#			Variables
set(BKM_WINDOWS
			src/Windows/BookmarkManagerWindow.h
			src/Windows/BookmarkManagerWindow.cpp
			src/Windows/ContainerCreationWindow.h
			src/Windows/ContainerCreationWindow.cpp
			src/Windows/AboutProgramWindow.h
			src/Windows/AboutProgramWindow.cpp)
		
set(BKM_APPLICATIONSETTINGS
			src/ApplicationSettings/ApplicationSettings.h
			src/ApplicationSettings/ApplicationSettings.cpp)

set(BKM_ARCHIVE
			src/Archive/Archive.h
			src/Archive/Archive.cpp)
		
set(BKM_TOTAL
			src/Total/GeneralOperations.h
			src/Total/GeneralOperations.cpp
			src/Total/HandleManager.h
			src/Total/HandleManager.cpp
			src/Total/BmDef.h)

set(BKM_RESOURCES
			src/BookmarkManager.cpp
			src/res/Resource.h
			res/Resource.rc
			res/icon/BKM_Icon_1.ico)

set(BKM_OTHER
			src/BookmarkManager.cpp)

set(BKM_ALL
			${BKM_WINDOWS}
			${BKM_APPLICATIONSETTINGS}
			${BKM_ARCHIVE}
			${BKM_TOTAL}
			${BKM_RESOURCES}
			${BKM_OTHER})


#			Visual Studio
foreach(i ${BKM_ALL})
	get_filename_component(FILE_DIR ${i} DIRECTORY)
	source_group(${FILE_DIR} FILES ${i})
endforeach()


add_executable(BookmarkManager WIN32 ${BKM_ALL})

#			Libraries
target_link_libraries(BookmarkManager PRIVATE comctl32)


set_target_properties(BookmarkManager PROPERTIES
											CXX_STANDARD 11
											CXX_STANDARD_REQUIRED TRUE)
