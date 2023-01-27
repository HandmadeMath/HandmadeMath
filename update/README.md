# Handmade Math 2.0 Update Tool

Due to the large number of breaking naming changes in Handmade Math 2, we provide a small Python script to update your programs automatically. It can run on individual files or on all files in a directory (recursively).

**Warning!** This tool is not very smart! Please ensure that your work is committed and backed up, in case you have to revert this tool's changes.

```
# see usage info and options
> python3 update_hmm.py -h
usage: update_hmm [-h] [--exts .foo [.foo ...]] filename [filename ...]
...

# run on individual files
> python3 update_hmm.py MyPlatformLayer.c MyPlatformLayer.h
Updating: MyPlatformLayer.c
Updating: MyPlatformLayer.h
Updated 2 files with 0 warnings.

# run on a whole directory
> python3 update_hmm.py projects/MyCoolGame
Updating: projects/MyCoolGame/src/MyPlatformLayer.c
Updating: projects/MyCoolGame/include/MyPlatformLayer.h
...
```
