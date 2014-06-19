# author f35f22fan at gmail dot com
# extensions:
# .hh, .cc:  namespace with functions
# .cpp, hpp: classes
# .hxx:      (const) declarations

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(${QOds_SOURCE_DIR})
include_directories(${QOds_SOURCE_DIR}/mtl)
link_directories(${QOds_BINARY_DIR}/mtl)
link_directories(${QOds_BINARY_DIR}/quazip)

add_definitions(-std=c++11)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (DEFINED ODS_DSO)
	add_definitions(-DODS_DSO_BUILD)
	set(lib_type SHARED)
else (DEFINED ODS_DSO)
	set(lib_type STATIC)
endif (DEFINED ODS_DSO)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

file(GLOB_RECURSE lib_files
	"*.h" "*.hh" "*.hpp" "*.hxx"
	"*.c" "*.cc" "*.cpp"
	"ods")

foreach(f IN LISTS lib_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

add_library(ods ${lib_type} ${lib_files})
target_link_libraries(ods quazip mtl Qt5::Core Qt5::Gui)



 
