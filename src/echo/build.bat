@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\echo\echo.cpp user32.lib
popd