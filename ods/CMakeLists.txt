# author f35f22fan at gmail dot com
# extensions:
# .hh, .cc:  namespace with functions
# .cpp, hpp: classes
# .hxx:      (const) declarations
cmake_policy(SET CMP0100 NEW)
message(STATUS ${CMAKE_CURRENT_LIST_FILE})
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${QOds_SOURCE_DIR})
link_directories(${QOds_BINARY_DIR}/lib)

find_package(Qt5 COMPONENTS Core Gui)

file(GLOB_RECURSE lib_files
	"*.h" "*.hh" "*.hpp" "*.hxx"
	"*.c" "*.cc" "*.cpp"
	"ods")

foreach(f IN LISTS lib_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

if (DEFINED ODS_STATIC)
	set(lib_type STATIC)
else (DEFINED ODS_STATIC)
	set(lib_type SHARED)
	add_definitions(-DODS_SHARED -DODS_BUILDING)
endif (DEFINED ODS_STATIC)

add_library(ods ${lib_type} ${lib_files})
set_property(TARGET ods PROPERTY AUTOMOC ON)
target_link_libraries(ods quazip Qt5::Core Qt5::Gui)
