@echo off
echo Setting up the Window$ Qt environment...

rem MinGW:
rem set PATH=C:\Qt\Qt5.3.2\5.3\mingw482_32\bin;%PATH%
rem set PATH=C:\Qt\Qt5.3.2\Tools\mingw482_32\bin;%PATH%

rem Visual Studio 2013 32bit:
set PATH=C:\Qt\Qt5.3.2\5.3\msvc2013_opengl\bin;%PATH%

rem Visual Studio 2013 64bit:
set PATH=C:\Qt\Qt5.3.2\5.3\msvc2013_64_opengl\bin;%PATH%

rem Dir with cmake.exe:
set PATH=C:\Program Files (x86)\CMake\bin;%PATH%

rem Dir with make.exe:
rem set PATH=C:\Program Files (x86)\GnuWin32\bin;%PATH%

echo Done
