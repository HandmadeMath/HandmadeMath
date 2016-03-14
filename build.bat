@echo off

IF NOT EXIST build mkdir build

pushd build

REM C Build
cl -FC -nologo -Z7 -Tc ../main.c

REM C++ Build
REM cl -nologo -Zi -FC  ../main.cpp

popd
