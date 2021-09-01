@echo off

if "%1%"=="travis" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat" -host_arch=amd64 -arch=amd64
) else (
    where /q cl
    if ERRORLEVEL 1 (
        for /f "delims=" %%a in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -find VC\Auxiliary\Build\vcvarsall.bat') do (%%a x64)
    )
)

if not exist "build" mkdir build
pushd build

cl /Fehmm_test_c.exe ..\HandmadeMath.c ..\hmm_test.c
hmm_test_c

cl /Fehmm_test_c_no_sse.exe /DHANDMADE_MATH_NO_SSE ..\HandmadeMath.c ..\hmm_test.c
hmm_test_c_no_sse

cl /Fehmm_test_cpp.exe ..\HandmadeMath.cpp ..\hmm_test.cpp
hmm_test_cpp

cl /Fehmm_test_cpp_no_sse.exe /DHANDMADE_MATH_NO_SSE ..\HandmadeMath.cpp ..\hmm_test.cpp
hmm_test_cpp_no_sse

popd
