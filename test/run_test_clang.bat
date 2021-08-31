@echo off

if not exist "build" mkdir build
pushd build

clang-cl /Fehmm_test_c.exe ..\HandmadeMath.c ..\hmm_test.c
hmm_test_c

clang-cl /Fehmm_test_c_no_sse.exe /DHANDMADE_MATH_NO_SSE ..\HandmadeMath.c ..\hmm_test.c
hmm_test_c_no_sse

clang-cl /Fehmm_test_cpp.exe ..\HandmadeMath.cpp ..\hmm_test.cpp
hmm_test_cpp

clang-cl /Fehmm_test_cpp_no_sse.exe /DHANDMADE_MATH_NO_SSE ..\HandmadeMath.cpp ..\hmm_test.cpp
hmm_test_cpp_no_sse

popd
