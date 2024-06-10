#!/bin/bash

# loop through each item in the current directory 
echo "Running..."
for dir in */ ; do 
    # check of its a directory and does not start with .
    if [ -d "$dir" ] && [[ "basename "$dir")" != .* ]]; then
        # cd in 
        cd "$dir"

        #check for makefile 
        if [ -f Makefile ] || [ -f makefile ]; then
            # call make clean
            echo "Running 'make clean' in $dir"
            make clean
        else
            echo "No Makefile found in $dir"
        fi

        #go back to parent dir 
        cd ..
    fi
done