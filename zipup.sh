#!/bin/bash
## few liner to create submission
echo "Creating Zipped $1"
zip $1.zip $1/*.cpp $1/*.h $1/Makefile
mkdir -p Submissions
mv $1.zip Submissions/$1.zip
