#pragma once

#include "git.h"

#define AS_STRING(x) #x
#define STR(x) AS_STRING(x)

#define BUILD_DATE      STR(VER_DATE)
#define BUILD_VERREV    STR(VERSION) "." STR(REVISION)
#define BUILD_ID        TITLE " " BUILD_VERREV " (" BUILD_DATE ")"

#define BUILD_DETAILS   STR(VER_TIME) " (" STR(GIT) ")"
#define BUILD_LEGAL     "Copyright \xa9 " STR(VER_YEAR) " " AUTHOR

#define BUILD_FULLINFO  "Built on " BUILD_DETAILS " using " __VERSION__

#define VSTRING         BUILD_ID " " BUILD_FULLINFO "\r\n"
#define VERSTAG         "\0$VER: " BUILD_ID " " BUILD_LEGAL
