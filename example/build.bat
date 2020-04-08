@echo off

where /q cl
if ERRORLEVEL 1 (
    for /f "delims=" %%a in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -find VC\Auxiliary\Build\vcvarsall.bat') do (%%a x64)
)

python lib\flextgl-gen\flextGLgen.py -D lib\flextgl -T glfw3 flextgl-profile.txt

if not exist "build" mkdir build
pushd build

cl ^
/Feexample.exe /MD ^
/I..\lib\glfw\include /I..\lib\flextgl /I..\lib\EGL-Registry\api ^
..\src\main.c ..\lib\flextgl\flextGL.c ^
/link user32.lib shell32.lib gdi32.lib opengl32.lib ..\lib\glfw\lib-vc2017\glfw3.lib

popd
