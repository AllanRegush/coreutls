@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\mv\mv.cpp user32.lib
popd