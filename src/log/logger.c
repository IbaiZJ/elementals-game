#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_CYAN    "\033[36m"

static const char* getLevelString(LogLevel level) {
    switch (level) {
        case LOG_INFO:    return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR:   return "ERROR";
        case LOG_DEBUG:   return "DEBUG";
        default:          return "UNKNOWN";
    }
}

static const char* getLevelColor(LogLevel level) {
    switch (level) {
        case LOG_INFO:    return COLOR_GREEN;
        case LOG_WARNING: return COLOR_YELLOW;
        case LOG_ERROR:   return COLOR_RED;
        case LOG_DEBUG:   return COLOR_CYAN;
        default:          return COLOR_RESET;
    }
}

void clearTerminal() {
    system(CLEAR_COMMAND);
}

void logMessage(LogLevel level, const char *format, ...) {
    fprintf(stderr, "%s[%s]%s ", getLevelColor(level), getLevelString(level), COLOR_RESET);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
}
