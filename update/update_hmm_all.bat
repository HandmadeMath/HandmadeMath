@REM Batch script to run update_hmm.exe on all your code files.
@REM Example:
@REM "update_hmm_all.bat Code\Project\" -> Recursively update all files/folders in .\Code\Project\

for /r %1 %%v in (*.c) do update_hmm.exe "%%v"
for /r %1 %%v in (*.h) do update_hmm.exe "%%v"
for /r %1 %%v in (*.cpp) do update_hmm.exe "%%v"
for /r %1 %%v in (*.hpp) do update_hmm.exe "%%v"

@REM @REM Uncomment for sokol-samples
@REM for /r %1 %%v in (*.glsl) do update_hmm.exe "%%v"
@REM for /r %1 %%v in (*.hlsl) do update_hmm.exe "%%v"
