@echo off

if "%1" == "1" (
	set release_mode=1
) else (
	set release_mode=0
)

set compiler_flags= -nologo 

if %release_mode% EQU 0 (
	set compiler_flags=%compiler_flags% -Od -Zi
) else (
	set compiler_flags=%compiler_flags% -O2
)

set compiler_warnings= -W4

set compiler_settings= %compiler_flags% %compiler_warnings%

mkdir ..\build
pushd ..\build
echo $pwd
cl %compiler_settings% ..\cat\cat.cpp
popd