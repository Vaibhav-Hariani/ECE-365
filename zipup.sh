#!/bin/bash
## One linear to create submission
echo "Creating Zipped $1"
zip $1 *.cpp *.h Makefile
mv $1 Submissions/$1
