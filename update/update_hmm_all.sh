# Bash script to run update_hmm on all your code files.
# Example:
# "update_hmm_all Code/Project/" -> Recursively update all files/folders in ./Code/Project/
echo $1
for file in "$1"/*.{c,h,cpp,hpp} "$1"/**/*.{c,h,cpp,hpp} ; do
    ./update_hmm "$file"
done

# # Uncomment for sokol-samples
# for file in "$1"/*.{glsl,hlsl} "$1"/**/*.{glsl,hlsl} ; do
    # ./update_hmm "$file"
# done
