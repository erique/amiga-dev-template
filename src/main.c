#include <stdio.h>

#define TITLE		"Program"
#define AUTHOR		"Nomen Nominandum"

#include "version.h"
#include "logging.h"

const char IDString[] = VSTRING;
const char VTAG[] = VERSTAG;

void rainbow(int16_t delay);

__stdargs  // main() uses arguments passed via the stack
int main(int argc, const char* argv[])
{
    // print to stdout
    printf("\n%s :\n", argv[0]);
    printf("VSTRING = %s", IDString);

    // print to serial (9600 8N1)
    kprintf("\n%s :\n", argv[0]);

    KLOG(LOG_INFO, __FILE__, "VSTRING = %s\n", IDString);

    KFATAL  ("FATAL",   "This is a fatal error\n");
    KERROR  ("ERROR",   "This is an error\n");
    KWARN   ("WARN",    "This is a warning\n");
    KINFO   ("INFO",    "This is an info message\n");
    KDEBUG  ("DEBUG",   "This is debug info\n");
    KVERBOSE("VERBOSE", "This is verbose output\n");

    // call some assembly code
    rainbow(111);

    return 0;
}
