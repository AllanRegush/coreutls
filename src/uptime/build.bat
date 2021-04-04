@echo off

mkdir ..\build
pushd ..\build
echo $pwd
cl -Zi ..\uptime\uptime.cpp
popd