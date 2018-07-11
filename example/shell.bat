@echo off

if not defined ORIGINALPATH set ORIGINALPATH=%PATH%
set PATH=%ORIGINALPATH%
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
