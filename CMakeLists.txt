cmake_minimum_required(VERSION 3.5)

project(BookmarkManager
			LANGUAGES C	CXX)


set(WINDOWS
		src/Windows/BookmarkManagerWindow.h
		src/Windows/BookmarkManagerWindow.cpp
		src/Windows/ContainerCreationWindow.h
		src/Windows/ContainerCreationWindow.cpp
		src/Windows/AboutProgramWindow.h
		src/Windows/AboutProgramWindow.cpp)
		
set(APPLICATIONSETTINGS
		src/ApplicationSettings/ApplicationSettings.h
		src/ApplicationSettings/ApplicationSettings.cpp)

set(ARCHIVE
		src/Archive/Archive.h
		src/Archive/Archive.cpp)
		
set(TOTAL
		src/Total/GeneralOperations.h
		src/Total/GeneralOperations.cpp
		src/Total/HandleManager.h
		src/Total/HandleManager.cpp
		src/Total/BmDef.h)
		
source_group(src FILES src/BookmarkManager.cpp)
source_group(src/res FILES src/res/Resource.h)
source_group(res FILES res/Resource.rc)
source_group(res/icon FILES res/icon/q1.ico)
source_group(src/Windows FILES ${WINDOWS})
source_group(src/ApplicationSettings FILES ${APPLICATIONSETTINGS})
source_group(src/Archive FILES ${ARCHIVE})
source_group(src/Total FILES ${TOTAL})

add_executable(BookmarkManager WIN32
					src/BookmarkManager.cpp
					src/res/Resource.h
					res/Resource.rc
					res/icon/q1.ico
					${WINDOWS}
					${APPLICATIONSETTINGS}
					${ARCHIVE}
					${TOTAL})
					
#set_source_files_properties(res/icon/q1.ico res/Resource.rc src/res/Resource.h PROPERTIES LANGUAGES RC)

set_target_properties(BookmarkManager PROPERTIES
						CXX_STANDARD 11
						CXX_STANDARD_REQUIRED ON)