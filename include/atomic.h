#ifndef KERNEL_ATOMIC_H
#define KERNEL_ATOMIC_H

#include "include/types.h"
#include "asm/atomic.h"

/*! \typedef atomic_t
 *  \brief This is an atomic type object
 */
typedef struct {
	s32_t value;
} atomic_t;

/*! \brief Reads value of atomic type
 */
s32_t atomic_read(atomic_t *);

/*! \def Creates a new atomic object
 */
#define atomic_new(name, value) atomic_t name = {value}

#define atomic_init(value) {value}

#endif // KERNEL_ATOMIC_H
