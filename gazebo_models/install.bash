#!/bin/bash
declare -a folders
for f in *; do
    if [ -d "$f" ]; then
        folders+=("$f")
    fi
done

p=$PWD
cd $HOME/.gazebo/models

for i in "${folders[@]}"; do
    echo "sudo ln -s  $p/$i $i"   
    ln -s  $p/$i $i
done    
