@echo off

pushd "%~dp0"
set "MY_HOME=%CD%"
cd ..
set "BUILD_DIR=%CD%\build"
popd 

if not exist "%BUILD_DIR%" goto:ready
echo %BUILD_DIR% already exists.
goto:eof

:ready
mkdir "%BUILD_DIR%"
pushd "%BUILD_DIR%"
cmake ..\src -G"Visual Studio 15 2017 Win64"
echo Load the solution inside %BUILD_DIR% with MSVC.
popd
goto:eof
