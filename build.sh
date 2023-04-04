#!/bin/bash

PROJECTS="kernel"
TARGET_TRIPLE="x86_64-elf"

for PROJECT in $PROJECTS; do
    cd $PROJECT
    make clean
    TRIPLE=$TARGET_TRIPLE make
    cd ..
done