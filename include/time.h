#ifndef KERNEL_TIME_H
#define KERNEL_TIME_H

#include "include/types.h"

extern u32_t systemtime;

void static inline systimeinc(void)
{
	++systemtime;
}

void static inline systimeget(void) 
{
	return systemtime;
}

void systimeinit(void);

#endif // KERNEL_TIME_H
