@REM Batch script to run UpdateTool.exe on all your code files.
@REM Examples:
@REM "UpdateHMM2.0" -> Recursively update files in the current folder.
@REM "UpdateHMM2.0 Code\Project\" -> Recursively update all files/folders in .\Code\Project\

for /r %1 %%v in (*.c) do UpdateTool.exe "%%v"
for /r %1 %%v in (*.h) do UpdateTool.exe "%%v"
for /r %1 %%v in (*.cpp) do UpdateTool.exe "%%v"
for /r %1 %%v in (*.hpp) do UpdateTool.exe "%%v"

@REM @REM Uncomment for sokol-samples
@REM for /r %1 %%v in (*.glsl) do UpdateTool.exe "%%v"
@REM for /r %1 %%v in (*.hlsl) do UpdateTool.exe "%%v"
