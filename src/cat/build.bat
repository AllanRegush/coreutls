@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\cat\cat.cpp user32.lib
popd