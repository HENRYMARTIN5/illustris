#!/bin/bash

./build.sh

qemu-system-x86_64 -kernel kernel.amd64.bin -serial stdio