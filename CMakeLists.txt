#cmake -G "MinGW Makefiles"
message(STATUS "PROCESSING ${CMAKE_CURRENT_LIST_FILE}")
cmake_minimum_required(VERSION 2.8.11)
Project(QOds)

message(STATUS ${CMAKE_SYSTEM}) # print OS name

if (UNIX)
	#disable -rdynamic
	SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
	SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
	add_definitions(-fPIC)
	# comment out next 2 lines if clang not available
	SET (CMAKE_CXX_COMPILER		"/usr/bin/clang++")
	SET (CMAKE_C_COMPILER		"/usr/bin/clang")
endif (UNIX)

add_definitions(-O2 -Wall -Wno-deprecated -D_FILE_OFFSET_BITS=64)

# Note, for now only the shared version works properly.
# The static version of the lib fails to link with executables.
# Uncomment next line to build a shared lib
set(QUAZIP_BUILD "") # dynamic lib "quazip"
if (DEFINED QUAZIP_BUILD)
	add_definitions(-DQUAZIP_BUILD)
endif (DEFINED QUAZIP_BUILD)

set(ODS_DSO "") # dynamic lib "ods"
if (DEFINED ODS_DSO)
	add_definitions(-DODS_DSO)
endif (DEFINED ODS_DSO)

set(MTL_DSO "") # dynamic lib "mtl"
if (DEFINED MTL_DSO)
	add_definitions(-DMTL_DSO)
endif (DEFINED MTL_DSO)

add_subdirectory(app)
add_subdirectory(mtl)
add_subdirectory(ods)
add_subdirectory(quazip)

