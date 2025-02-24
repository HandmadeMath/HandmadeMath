@echo off

where /q cl
if ERRORLEVEL 1 (
    for /f "delims=" %%a in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -find VC\Auxiliary\Build\vcvarsall.bat') do (%%a x64)
)

if not exist "build" mkdir build
pushd build

cl /std:c11 /Fehmm_test_c11.exe ..\HandmadeMath.c ..\hmm_test.c || exit /b 1
hmm_test_c11 || exit /b 1

cl /std:c11 /Fehmm_test_c11_no_simd.exe /DHANDMADE_MATH_NO_SIMD ..\HandmadeMath.c ..\hmm_test.c || exit /b 1
hmm_test_c11_no_simd || exit /b 1

cl /std:c17 /Fehmm_test_c17.exe ..\HandmadeMath.c ..\hmm_test.c || exit /b 1
hmm_test_c17 || exit /b 1

cl /std:c++14 /Fehmm_test_cpp14.exe ..\HandmadeMath.cpp ..\hmm_test.cpp || exit /b 1
hmm_test_cpp14 || exit /b 1

cl /std:c++14 /Fehmm_test_cpp14_no_simd.exe /DHANDMADE_MATH_NO_SIMD ..\HandmadeMath.cpp ..\hmm_test.cpp || exit /b 1
hmm_test_cpp14_no_simd || exit /b 1

cl /std:c++17 /Fehmm_test_cpp17.exe ..\HandmadeMath.cpp ..\hmm_test.cpp || exit /b 1
hmm_test_cpp17 || exit /b 1

cl /std:c++20 /Fehmm_test_cpp20.exe ..\HandmadeMath.cpp ..\hmm_test.cpp || exit /b 1
hmm_test_cpp20 || exit /b 1

popd
