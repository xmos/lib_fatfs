// Copyright 2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
/* Load the port configuration before upstream ff.h selects ffconf.h. */
#include "../api/ff.h"
#include "../../third_party/FatFs/source/ff.c"
