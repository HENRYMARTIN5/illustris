#!/bin/bash

PROJECTS="kernel"

for PROJECT in $PROJECTS; do
    cd $PROJECT
        ./build.sh -b
        ./build.sh -C
        ./build.sh -c
    cd ..
done