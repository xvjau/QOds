#cmake -G "MinGW Makefiles"
message(STATUS "${CMAKE_CURRENT_LIST_FILE}")
cmake_minimum_required(VERSION 2.8.12)
Project(QOds)

message(STATUS ${CMAKE_SYSTEM}) # print OS name

add_subdirectory(zlib)
add_subdirectory(quazip)
add_subdirectory(ods)
add_subdirectory(app)
