#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <exec/types.h>
#include <inline/exec.h>

#include "logging.h"

#define RawPutChar(___ch) \
    LP1NR(516, RawPutChar , BYTE, ___ch, d0,\
          , EXEC_BASE_NAME)

static void raw_put_char(uint32_t c __asm("d0"))
{
    struct ExecBase* SysBase = *(struct ExecBase**)4;
    RawPutChar(c);
}

int kprintf(const char* format, ...)
{
    if (format == NULL)
        return 0;

    va_list arg;
    va_start(arg, format);
    int ret = kvprintf(format, arg);
    va_end(arg);
    return ret;
}

int kvprintf(const char* format, va_list ap)
{
    __asm volatile("bchg.b #1,0xbfe001": : : "cc", "memory");

    struct ExecBase* SysBase = *(struct ExecBase**)4;
    RawDoFmt((STRPTR)format, ap, (__fpt)raw_put_char, NULL);
    return 0;
}

#define SGR_RESET   0
#define SGR_BLACK   30
#define SGR_RED     31
#define SGR_GREEN   32
#define SGR_YELLOW  33
#define SGR_BLUE    34
#define SGR_MAGENTA 35
#define SGR_CYAN    36
#define SGR_WHITE   37

int klog(int prio, const char* tag, const char* fmt, ... )
{
    uint8_t color = SGR_RESET;
    uint8_t c;
    char buf[8];

    switch (prio)
    {
        case LOG_FATAL:
            c = 'F';
            color = SGR_MAGENTA;
            break;

        case LOG_ERROR:
            c = 'E';
            color = SGR_RED;
            break;

        case LOG_WARN:
            c = 'W';
            color = SGR_YELLOW;
            break;

        case LOG_INFO:
            c = 'I';
            color = SGR_GREEN;
            break;

        case LOG_DEBUG:
            c = 'D';
            color = SGR_CYAN;
            break;

        case LOG_VERBOSE:
            c = 'V';
            color = SGR_WHITE;
            break;

        default:
            c = '?';
            color = SGR_WHITE;
            break;
    }

    int16_t i = 0;

    for (; i < sizeof(buf) && tag[i]; ++i)
        buf[i] = tag[i];

    for (; i < sizeof(buf); ++i)
        buf[i] = ' ';

    buf[sizeof(buf) - 1] = 0;

    kprintf("\x1b[%ldm[%lc/%s] ", color, (uint32_t)c, buf);

    va_list arg;
    va_start(arg, fmt);
    int ret = kvprintf(fmt, arg);
    va_end(arg);

    kprintf("\x1b[%ldm", SGR_RESET);

    return ret;
}
