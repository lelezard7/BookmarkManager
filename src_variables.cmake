set(BKM_WINDOWS
			src/Windows/BookmarkManagerWindow/BookmarkManagerWindow.h
			src/Windows/BookmarkManagerWindow/BookmarkManagerWindow.cpp
			src/Windows/ContainerCreationWindow/ContainerCreationWindow.h
			src/Windows/ContainerCreationWindow/ContainerCreationWindow.cpp
			src/Windows/AboutProgramWindow/AboutProgramWindow.h
			src/Windows/AboutProgramWindow/AboutProgramWindow.cpp
			src/Windows/SettingsProgramWindow/SettingsProgramWindow.h
			src/Windows/SettingsProgramWindow/SettingsProgramWindow.cpp)
		
set(BKM_APPLICATIONSETTINGS
			src/ApplicationSettings/ApplicationSettings.h
			src/ApplicationSettings/ApplicationSettings.cpp)

set(BKM_ARCHIVE
			src/Archive/Archive.h
			src/Archive/Archive.cpp)
		
set(BKM_COMMON
			src/Common/BkmDef.h
			src/Common/PositionAndSizeControls.h
			src/Common/CommonOperations.h
			src/Common/CommonOperations.cpp
			src/Common/Debug.h
			src/Common/Debug.cpp)

set(BKM_RESOURCES
			src/res/Resource.h
			res/Resource.rc
			res/icon/BKM_Icon_1.ico)

set(BKM_HANDLEMANAGER
			src/HandleManager/HandleManager.h
			src/HandleManager/HandleManager.cpp)
			
set(BKM_HELP
			help/BookmarkManager.chm)
set(BKM_HELP_SRC
			help/src/About_program.htm)

set(BKM_OTHER
			src/BookmarkManager.cpp)


set(BKM_ALL
			${BKM_WINDOWS}
			${BKM_APPLICATIONSETTINGS}
			${BKM_ARCHIVE}
			${BKM_COMMON}
			${BKM_RESOURCES}
			${BKM_HANDLEMANAGER}
			${BKM_HELP_SRC}
			${BKM_OTHER})