#include "include/atomic.h"

s32_t atomic_read(atomic_t *a)
{
	return a->value;
}
