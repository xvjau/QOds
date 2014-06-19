# author f35f22fan at gmail dot com
# "mtl" stands for "my tiny library"

message(STATUS ${CMAKE_CURRENT_LIST_FILE})
add_definitions(-std=c++11)

if (DEFINED MTL_DSO)
	add_definitions(-DMTL_DSO_BUILD)
	set(lib_type SHARED)
else (DEFINED MTL_DSO)
	set(lib_type STATIC)
endif (DEFINED MTL_DSO)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)

set (lib_files
	dso.hxx
	err.hpp
	global.hxx
)

foreach(f IN LISTS lib_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

add_library(mtl ${lib_type} ${lib_files})
target_link_libraries(mtl Qt5::Core)

