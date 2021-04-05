# Setting up build environment

In your cmd window run `vcvarsall.bat x64` in your compilers directory this will let you use MSVC from the command prompt.
I have a batch file run on command prompt start up.   

```batch
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
```

### Build All
run `src\buildall.bat` this will compile all the programs - compiled programs will be in the `build` directory.

### Build One
run `build.bat` in the folder of the program you wish to compile. ex. `src\cp\build.bat`