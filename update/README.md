# Handmade Math 2.0 Update Tool

Due to the large number of breaking naming changes in Handmade Math 2, we provide a small tool to update your programs automatically. It's a C program that takes a list of files and updates their text, along with some scripts to recursively run the program on all code in a directory.

You can compile the tool yourself with any C/C++ compiler:

```bash
# MSVC (Windows)
cl update_hmm.c

# gcc
gcc update_hmm.c -o update_hmm

# clang
clang update_hmm.c -o update_hmm
```

Once built, the tool can be run on any C or C++ files:

```bash
# Windows
update_hmm.exe MyGame.cpp MyPlatformLayer.cpp

# Other platforms
update_hmm MyGame.cpp MyPlatformLayer.cpp
```

Or, update all C/C++ files in a directory by running one of the provided shell scripts:

```bash
# Windows
update_hmm_all.bat "path\to\project"

# Other platforms
update_hmm_all.sh path/to/project
```
