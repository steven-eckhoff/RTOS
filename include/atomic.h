#ifndef KERNEL_ATOMIC_H
#define KERNEL_ATOMIC_H

#include "include/types.h"

/*! \typedef atomic_t
 *  \brief This is an atomic type object
 */
typedef struct {
	s32_t value;
} atomic_t;

#include "asm/atomic.h"

/*! \brief Reads value of atomic type
 *  \note Only accurate if preemption is disabled. This is just to keep the 
 *        interface with atomics consistent. This does not guarantee atomicity.
 */
s32_t static inline // __attribute__((always_inline)) //FIXME: Compiler creates junk
atomic_read(atomic_t *a)
{
	return a->value;
}


// #define atomic_read(x) ((x)->value) FIXME: This also doesn't work

/*! \def Creates a new atomic object
 */
#define atomic_new(name, value) atomic_t name = {value}

#define atomic_init(value) {value}

#endif // KERNEL_ATOMIC_H
