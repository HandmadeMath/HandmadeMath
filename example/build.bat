@echo off

mkdir build\example
pushd build\example
cl^
    /I..\..\.. /I..\..\external\glew\include /I..\..\external\glfw-win64\include^
    /MD /EHsc^
    ..\..\src\*.cpp^
    /Fehmm_example.exe^
    /link^
    /LIBPATH:..\..\external\glew\lib\Release\x64 /LIBPATH:..\..\external\glfw-win64\lib-vc2015^
    opengl32.lib gdi32.lib user32.lib shell32.lib glew32.lib glfw3.lib
copy ..\..\external\glew\bin\Release\x64\glew32.dll glew32.dll
popd
