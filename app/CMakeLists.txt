message(STATUS "PROCESSING ${CMAKE_CURRENT_LIST_FILE}")

include_directories(${QOds_SOURCE_DIR})
include_directories(${QOds_SOURCE_DIR}/mtl)
include_directories(${QOds_SOURCE_DIR}/ods)
include_directories(${QOds_SOURCE_DIR}/quazip)

link_directories(${QOds_BINARY_DIR}/ods)
link_directories(${QOds_BINARY_DIR}/quazip)

add_definitions(-std=c++11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Set some Win32 Specific Settings
if(WIN32)
	set(GUI_TYPE "") #or WIN32 for no console output
# Set some Apple MacOS Specific settings
elseif (APPLE)
	set(GUI_TYPE MACOSX_BUNDLE)
endif (WIN32)

find_package(Qt5Core)
find_package(Qt5Gui)
set(src_files main.cpp Invoice.cpp Invoice.hpp Item.cpp Item.hpp)

foreach(f IN LISTS src_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

add_executable(ods_test ${GUI_TYPE} ${src_files})
target_link_libraries(ods_test pthread m
	Qt5::Core Qt5::Gui mtl quazip ods)
