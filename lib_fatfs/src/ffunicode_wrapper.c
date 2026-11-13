// Copyright 2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
/* Unicode support for long file names. Upstream compiles this to nothing
 * unless FF_USE_LFN is enabled in the application's fatfs_conf.h. */
#include "../api/ff.h"
#include "../../third_party/FatFs/source/ffunicode.c"
