## Amiga Development Template

### Usage
```
$ make
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
