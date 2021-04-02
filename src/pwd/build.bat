@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\pwd\pwd.cpp user32.lib
popd