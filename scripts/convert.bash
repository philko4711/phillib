#!/bin/bash
mkdir converted
N=$(find . -name "*.HEIC" | wc -l)
echo "Found" $N " HEIC images"
n=0
for f in *.HEIC
do
    n=$((n+1))
    var=$(basename $f .HEIC)
    echo "Working on file $var ($n of $N)"
    heif-convert $f $var.jpg
    mv $var.jpg converted
done
