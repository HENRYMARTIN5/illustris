#include <kernel/logging.h>
#include <stdio.h>

void log(char* message, char* level) {
    printf("[%s] %s", level, message);
}
void info(char* message) {
    log(message, "INFO");
}
void warn(char* message) {
    log(message, "WARN");
}
void error(char* message) {
    log(message, "ERR");
}