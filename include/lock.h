/*! \file lock.h
 *  \brief This file provides the kernel API for locks
 */
#ifndef KERNEL_LOCK_H
#define KERNEL_LOCK_H

#include "include/types.h"
#include "include/atomic.h"

typedef struct thread thread_l_t;

/*! \typedef lock_t
 *  \brief This is a lock object
 */
typedef struct {
	atomic_t atomic;
	thread_l_t *owner;
} lock_t;

/*! \def lock_new
 */
#define lock_new(name) lock_t name = {atomic_init(0), NULL}

/*! \def lock_init
 */
#define lock_init() {atomic_init(0), NULL}

/*! \brief Tries to aquire a lock or spin on it
 */	
void spin_lock(lock_t *l);

/*! \brief Unlocks a kernel lock object
 */
void spin_unlock(lock_t *l);

#endif // KERNEL_LOCK_H
