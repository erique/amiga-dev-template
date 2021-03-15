#pragma once

#include <stdarg.h>

int kprintf(const char* format, ...);
int kvprintf(const char* format, va_list ap);

#define LOG_SILENT  (0)
#define LOG_FATAL   (1)
#define LOG_ERROR   (2)
#define LOG_WARN    (3)
#define LOG_INFO    (4)
#define LOG_DEBUG   (5)
#define LOG_VERBOSE (6)

int klog(int prio, const char* tag, const char* fmt, ... );

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_VERBOSE
#endif

#define KLOG(p, t, ...) do { if ((p) <= LOG_LEVEL) klog(p, t, __VA_ARGS__); } while(0)

#define KFATAL(t, ...)   do { if (LOG_FATAL   <= LOG_LEVEL) klog(LOG_FATAL,   t, __VA_ARGS__); } while(0)
#define KERROR(t, ...)   do { if (LOG_ERROR   <= LOG_LEVEL) klog(LOG_ERROR,   t, __VA_ARGS__); } while(0)
#define KWARN(t, ...)    do { if (LOG_WARN    <= LOG_LEVEL) klog(LOG_WARN,    t, __VA_ARGS__); } while(0)
#define KINFO(t, ...)    do { if (LOG_INFO    <= LOG_LEVEL) klog(LOG_INFO,    t, __VA_ARGS__); } while(0)
#define KDEBUG(t, ...)   do { if (LOG_DEBUG   <= LOG_LEVEL) klog(LOG_DEBUG,   t, __VA_ARGS__); } while(0)
#define KVERBOSE(t, ...) do { if (LOG_VERBOSE <= LOG_LEVEL) klog(LOG_VERBOSE, t, __VA_ARGS__); } while(0)
