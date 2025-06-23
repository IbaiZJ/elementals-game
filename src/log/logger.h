#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_DEBUG
} LogLevel;

void logMessage(LogLevel level, const char *format, ...);
void clearTerminal();

#endif
