cmake_minimum_required(VERSION 3.5)
project(BookmarkManager	LANGUAGES C	CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
add_library(SaveModule SHARED
							src/SaveModule.h
							src/SaveModule.cpp)

target_include_directories(SaveModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
