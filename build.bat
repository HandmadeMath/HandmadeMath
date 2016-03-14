@echo off

IF NOT EXIST build mkdir build

pushd build

REM C Build
REM cl -FC -nologo -Z7 -Tc ../main.c

REM C++ Build
cl -nologo -Zi -FC  ../main.cpp

popd
