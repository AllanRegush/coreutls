@echo off

if "%1" == "1" (
	set release_mode=1
) else (
	set release_mode=0
)

set compiler_flags= -nologo -GS- -Gs9999999

if %release_mode% EQU 0 (
	set compiler_flags=%compiler_flags% -Od -Zi
) else (
	set compiler_flags=%compiler_flags% -O2
)

set compiler_warnings= -W4

set compiler_settings= %compiler_flags% %compiler_warnings%

set linker_settings= -link -nodefaultlib -subsystem:console kernel32.lib -stack:0x100000,0x100000

mkdir ..\build
pushd ..\build
echo $pwd
cl %compiler_settings% ..\pwd\pwd.cpp %linker_settings%
del *.obj > NUL 2 > NUL
popd