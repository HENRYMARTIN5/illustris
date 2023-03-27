# Illustris Design Doc

This document details the overarching design behind Illustris, a simple operating system written from scratch in C.

## Boot Process

The boot process is simple - grub2 passes control of the system to the `boot.S` file, and from there it passes control to the main `kernel.c` file.

## Proc/Task Management

A process contains some simple information: a PID, a list of *tasks*, its current TID, and a pointer to its *storage*. A process can be manipulated in many ways: it can be created (`proc_create`), destroyed (`proc_vaporize`), and can be moved upward in priority to be run next in the queue (`proc_forcenext`). Tasks are the simple steps that make up a process - each one will block the main thread, so they need to be fast. Extremely fast. Data is saved between tasks in the process' storage (all tasks start with 1 KiB of storage, more can be requested from the kernel). If you are observant, you may have noticed that this sounds a lot like a cooperative multitasking system. And if you thought that, you'd be absolutely right - the kernel waits for the current task to yield to it to continue with the next task. Although this somewhat degrades performance, it will remain until a faster alternative is implemented (eg. round robin or true multithreading).

## Filesystem

> Filesystem support (and the VFS layer) haven't been implemented yet. Expect things to change as development continues.

In Illustris, the Virtual File System (VFS) layer provides a uniform interface for accessing files and directories across different filesystems. The VFS layer handles all low-level filesystem interactions, such as reading and writing to storage devices, organizing files and directories, and handling file permissions and metadata.

By abstracting these low-level interactions, the VFS layer allows the operating system to interact with different types of filesystems using a standardized interface. This means that the user can access files and directories in a consistent way, regardless of the underlying filesystem.

For example, when a user requests to open a file, the VFS layer determines the appropriate filesystem driver to use based on the file's location and the filesystem type. The driver then handles the low-level operations required to access the file, such as reading data from a storage device.

## ManuScript

ManuScript is the interpreted programming language used to write high-level applications that run on Illustris. Literally nothing else about this language has been drafted yet.
