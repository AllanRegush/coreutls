@echo off
set back = %cd%
for /D %%s in (.\*) do (

	IF NOT "%%s" == ".\build" (
		cd %%s
		call build.bat
		cd ..
	)
)
cd %back%
