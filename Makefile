SHELL=bash
#SHELL=bash -x
#.SILENT:
.PHONY: all clean bumprev test astyle

OUTDIR=build

CC=m68k-amigaos-gcc
AS=vasmm68k_mot
STRIP=m68k-amigaos-strip
SIZE=m68k-amigaos-size
CFLAGS=-Os -mregparm=4 -fomit-frame-pointer -Wall -Werror
ASFLAGS=-Fhunk -opt-fconst -quiet -nowarn=62
LDFLAGS=-noixemul

GIT_HEADER:=$(OUTDIR)/git.h

SRCS=$(wildcard src/*.c) $(wildcard src/*.s)
TARGET=$(OUTDIR)/main.exe

all: $(TARGET)

ALL_TOOLS = $(CC) $(AS) $(STRIP) $(SIZE)
ALL_OK := $(foreach tool,$(ALL_TOOLS), $(if $(shell which $(tool)),,$(error "No '$(tool)' in PATH")))

##
## Feed build time and date via defines rather than using __DATE__ / __TIME__
##

VER_DATE:="$(shell date +%d.%-m.%y)"
VER_TIME:="$(shell date "+%d %b %Y / %T")"
VER_YEAR:="$(shell date +%Y)"

##
## Build VERSION & REVISION. Use the 'bumprev' target to increase the revision number
##

#$(info $(shell [[ ! -e VERSION ]] && echo 1 > VERSION))
#$(info $(shell [[ ! -e REVISION ]] && echo 1 > REVISION))
VERSION :=$(shell cat VERSION)
REVISION:=$(shell cat REVISION)

$(info VERSION     = $(VERSION).$(REVISION))

##

CFLAGS+=-I$(OUTDIR)
CFLAGS+=-MMD
CFLAGS+=-DVERSION=$(VERSION)
CFLAGS+=-DREVISION=$(REVISION)
CFLAGS+=-DVER_DATE=$(VER_DATE)
CFLAGS+=-DVER_TIME=$(VER_TIME)
CFLAGS+=-DVER_YEAR=$(VER_YEAR)
CFLAGS+=-DTARGET=$(TARGET)

GCC_ROOT:=$(abspath $(addsuffix ..,$(dir $(shell which m68k-amigaos-gcc))))
ASFLAGS+=-I$(GCC_ROOT)/m68k-amigaos/ndk-include

OBJS=$(addprefix $(OUTDIR)/,$(filter %.o,$(SRCS:.c=.o)))
OBJS+=$(addprefix $(OUTDIR)/,$(filter %.o,$(SRCS:.s=.o)))
DEPS=$(OBJS:.o=.d)

##
# Generate debug info, but strip it from the final output
CFLAGS+=-g
LDFLAGS+=-g -Wl,-Map,$(basename $(TARGET))_map.txt
TARGET_DEBUG=$(basename $(TARGET))_sym$(suffix $(TARGET))

##
# Create output dirs
$(shell mkdir -p $(OUTDIR) $(dir $(OBJS)) > /dev/null)

##
## Generate a C header file with a macro defining the current git hash (incl dirty state)
##

GIT :=$(shell git describe --always --dirty)
GIT_HEADER?=git.h
GIT_DEFINE:='\#define GIT $(GIT)'
OLD_DEFINE:='$(shell [[ -e $(GIT_HEADER) ]] && cat $(GIT_HEADER) || echo "nothing")'
$(info GIT         = $(GIT))
#$(info GIT_DEFINE  = $(GIT_DEFINE))
#$(info OLD_DEFINE  = $(OLD_DEFINE))
$(info $(shell [[ $(OLD_DEFINE) != $(GIT_DEFINE) ]] && echo $(GIT_DEFINE) > $(GIT_HEADER)))

##

clean:
	rm -rf $(TARGET) $(OBJS) $(DEPS) $(GIT_HEADER) $(OUTDIR)

bumprev:
	echo $$(( $(REVISION) + 1 )) > REVISION

test: $(TARGET)
	@hash vamos 2>/dev/null && vamos -q $< || echo "amitools/vamos not installed"

astyle:
	astyle --formatted --style=bsd --suffix=none --indent=spaces --indent-switches --keep-one-line-blocks --pad-comma --keep-one-line-statements --min-conditional-indent=0 --align-pointer=type --indent-preprocessor --pad-oper --pad-header --break-blocks --recursive  src/*.c,*.h

##

# All objects depend on Makefile changes (to pick up CFLAGS changes etc)
$(OBJS) : $(MAKEFILE_LIST) VERSION REVISION

# Include all generated .d files
-include $(DEPS)

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTDIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET_DEBUG) : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGET) : $(TARGET_DEBUG)
	cp $< $@
	$(STRIP) $@
	$(SIZE) $@
