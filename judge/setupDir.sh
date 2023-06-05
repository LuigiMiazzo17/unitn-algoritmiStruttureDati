#!/usr/bin/env bash

if [ -z "$1" ]; then
    echo "Usage: $0 <name of the project>"
    exit 1
fi

# Create a new project directory

projectCounter="$(cat ./.setupProject/counter.txt)"
dirName="${projectCounter}-$1"
mkdir "$dirName"
cp ./.setupProject/template.cpp "$dirName/$1.cpp"

#increment counter file
echo $(( projectCounter + 1 )) > ./.setupProject/counter.txt
