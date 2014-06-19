message(STATUS "PROCESSING ${CMAKE_CURRENT_LIST_FILE}")
# set all include directories for in and out of source builds
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${ZLIB_INCLUDE_DIRS}
)

find_package(Qt5Core)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(PkgConfig)
pkg_check_modules(SYSZLIB zlib)
link_directories(${SYSZLIB_LIBRARY_DIRS})
include_directories(${SYSZLIB_INCLUDE_DIRS})

file(GLOB source_files "*.c" "*.cpp" "*.h")

if (DEFINED QUAZIP_BUILD)
	# Must be added to enable export macro
	add_definitions(-DQUAZIP_BUILD)
	set (lib_type SHARED)
else (DEFINED QUAZIP_BUILD)
	add_definitions(-DQUAZIP_STATIC)
	set (lib_type STATIC)
endif (DEFINED QUAZIP_BUILD)

add_library(quazip ${lib_type} ${source_files})
target_link_libraries(quazip Qt5::Core ${SYSZLIB_LIBRARIES})

