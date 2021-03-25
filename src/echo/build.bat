@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\echo\main.cpp user32.lib
popd