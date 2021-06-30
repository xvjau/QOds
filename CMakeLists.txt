Project(QOds)

set(LIBRARY_OUTPUT_PATH "${QOds_BINARY_DIR}/lib")

set(CMAKE_CXX_STANDARD 17)

message(STATUS ${CMAKE_SYSTEM}) # print OS name

#set (BUILD_STATIC_LIBRARIES "1")
if (BUILD_STATIC_LIBRARIES)
    set(ODS_STATIC "1")
    set(QUAZIP_STATIC "1")
    set(ZLIB_STATIC "1")
endif (BUILD_STATIC_LIBRARIES)

if(NOT TARGET zlib)
    find_package(ZLIB)
    if(NOT ZLIB_FOUND)
        add_subdirectory(zlib)
        set(ZLIB_LIBRARIES zlib)
        set(ZLIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/zlib)
    endif()
else()
    set(ZLIB_LIBRARIES zlib)
endif()
add_subdirectory(quazip)
add_subdirectory(ods)
add_subdirectory(app)
