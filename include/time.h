#ifndef KERNEL_TIME_H
#define KERNEL_TIME_H

#include "include/types.h"

#define systimeinc() systemtime++
#define systimeget() systemtime

extern u32_t systemtime;

void systimeinit(void);

#endif // KERNEL_TIME_H
