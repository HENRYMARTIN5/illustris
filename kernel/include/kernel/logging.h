#ifndef _KERNEL_LOGGING_H
#define _KERNEL_LOGGING_H

#include <stdio.h>

void log(char* message, char* level);
void info(char* message);
void warn(char* message);
void error(char* message);

#endif