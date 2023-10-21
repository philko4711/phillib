#!/bin/bash
mkdir converted
for f in *.HEIC
do
echo "Working on file $f"
heif-convert $f $f.jpg
cp $f.jpg converted
done
