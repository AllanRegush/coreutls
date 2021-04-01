@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\cp\cp.cpp
popd