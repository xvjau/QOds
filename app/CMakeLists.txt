message(STATUS ${CMAKE_CURRENT_LIST_FILE})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(${QOds_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib)

if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (NOT MSVC)

# Set some Win32 Specific Settings
if(WIN32)
	set(GUI_TYPE "") #or WIN32 for no console output
# Set some Apple MacOS Specific settings
elseif (APPLE)
	set(GUI_TYPE MACOSX_BUNDLE)
endif (WIN32)

find_package(Qt5Core)
find_package(Qt5Gui)

file(GLOB_RECURSE src_files
	"*.h" "*.hh" "*.hpp" "*.hxx"
	"*.c" "*.cc" "*.cpp"
	"ods")

foreach(f IN LISTS src_files)
	get_filename_component(b ${f} NAME)
	set_source_files_properties(${f} PROPERTIES
		COMPILE_DEFINITIONS "SRC_FILE_NAME=\"${b}\"")
endforeach()

add_executable(ods_test ${GUI_TYPE} ${src_files})
target_link_libraries(ods_test ods quazip zlib Qt5::Core Qt5::Gui)
