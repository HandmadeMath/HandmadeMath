@echo off

IF NOT EXIST build mkdir build

pushd build

REM C Build
cl -nologo -FC -Z7 -Tc ..\main.c

REM C++ Build
cl -nologo -FC -Z7 ..\main.cpp

popd 
