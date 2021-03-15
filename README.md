## Amiga Development Template

```__stdargs  // main() uses arguments passed via the stack
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
```
![screen]

### Usage
```
$ make || ./docker.sh make 
VERSION     = 1.0
GIT         = e2017d1

m68k-amigaos-gcc -Os -mregparm=4 -fomit-frame-pointer -Wall -Werror -Ibuild -MMD -DVERSION=1 -DREVISION=0 -DVER_DATE="12.3.21" -DVER_TIME="12 Mar 2021 / 18:29:55" -DVER_YEAR="2021" -DTARGET=build/main.exe -g -c -o build/src/logging.o src/logging.c
m68k-amigaos-gcc -Os -mregparm=4 -fomit-frame-pointer -Wall -Werror -Ibuild -MMD -DVERSION=1 -DREVISION=0 -DVER_DATE="12.3.21" -DVER_TIME="12 Mar 2021 / 18:29:55" -DVER_YEAR="2021" -DTARGET=build/main.exe -g -c -o build/src/main.o src/main.c
vasmm68k_mot -Fhunk -opt-fconst -quiet -nowarn=62 -I/opt/amiga/m68k-amigaos/ndk-include -o build/src/rainbow.o src/rainbow.s
m68k-amigaos-gcc -noixemul -g -Wl,-Map,build/main_map.txt build/src/logging.o build/src/main.o build/src/rainbow.o -o build/main_sym.exe
cp build/main_sym.exe build/main.exe
m68k-amigaos-strip build/main.exe
m68k-amigaos-size build/main.exe
   text	   data	    bss	    dec	    hex	filename
   8520	    384	    140	   9044	   2354	build/main.exe
```

[screen]: .github/screen.png  "FS-UAE / socat"
