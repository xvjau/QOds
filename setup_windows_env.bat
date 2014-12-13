@echo off
echo Setting up the Window$ Qt environment...

rem ==> MinGW
rem set PATH=C:\Qt\Qt5.4.0\5.4\mingw491_32\bin;%PATH%
rem set PATH=C:\Qt\Qt5.4.0\Tools\mingw491_32\bin;%PATH%
	rem Dir with make.exe:
rem set PATH=C:\Program Files (x86)\GnuWin32\bin;%PATH%
	rem Dir with cmake.exe:
rem set PATH=C:\Program Files (x86)\CMake\bin;%PATH%
rem <== MinGW

rem ==> Visual Studio 2013 32bit
rem set PATH=C:\Qt\Qt5.3.2\5.3\msvc2013_opengl\bin;%PATH%
	rem Dir with cmake.exe:
rem set PATH=C:\Program Files\CMake\bin;%PATH%
rem <== Visual Studio 2013 32bit

rem ==> Visual Studio 2013 64bit
set PATH=C:\Qt\Qt5.3.2\5.3\msvc2013_64_opengl\bin;%PATH%
	rem Dir with cmake.exe:
set PATH=C:\Program Files (x86)\CMake\bin;%PATH%
rem <== Visual Studio 2013 64bit

echo Done
