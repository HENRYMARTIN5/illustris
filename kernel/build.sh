#!/bin/bash
# build.sh - illustris kernel
# Possible arguments:
# -b: build
# -C: copy artifacts out of the folder
# -c: clean

# Parse arguments
while getopts "bCc" opt; do
  case $opt in
    b)
      echo "Building kernel" >&2
      cargo bootimage
      ;;
    C)
      echo "Copying artifacts" >&2
      mkdir -p ../output/kernel
      cp ./target/x86_64-illustris/debug/bootimage-illustris.bin ../output/kernel/kernel.bin
      ;;
    c)
      echo "Cleaning" >&2
      rm -Rfv ./target
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      ;;
  esac
done