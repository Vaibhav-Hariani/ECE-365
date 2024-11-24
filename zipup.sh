#!/bin/bash
## few liner to create submission
echo "Creating Zipped $1"
zip $1 *.cpp *.h Makefile
mkdir -p Submissions
mv $1 Submissions/$1
