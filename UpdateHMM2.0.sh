# Bash script to run UpdateTool on all your code files.
# Examples:
# "UpdateHMM2.0" -> Recursively update files in the current folder.
# "UpdateHMM2.0 Code/Project/" -> Recursively update all files/folders in ./Code/Project/
echo $1
for file in "$1"/*.{c,h,cpp,hpp} "$1"/**/*.{c,h,cpp,hpp} ; do
    ./UpdateTool "$file"
done

# # Uncomment for sokol-samples
# for file in "$1"/*.{glsl,hlsl} "$1"/**/*.{glsl,hlsl} ; do
    # ./UpdateTool "$file"
# done

