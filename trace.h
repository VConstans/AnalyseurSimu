#ifndef __TRACE_H__
#define __TRACE_H__

#include "evt.h"
#include <stdlib.h>
#include <stdio.h>

FILE* ouvertureTrace(char nomtrace[]);
struct evt* nextEvt(FILE* fdTrace);

#endif
