#!/bin/bash

source config.sh

for PROJECT in $PROJECTS; do
    cd $PROJECT
        ./build.sh -b
        ./build.sh -C
    cd ..
done