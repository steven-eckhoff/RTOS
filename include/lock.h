/*! \file lock.h
 *  \brief This file provides the kernel API for locks
 */
#ifndef KERNEL_LOCK_H
#define KERNEL_LOCK_H

#include "include/types.h"
#include "include/atomic.h"
#include "asm/lock.h"
#include "include/sched.h"

/*! \typedef lock_t
 *  \brief This is a lock object
 */
typedef struct {
	atomic_t atomic;
	atomic_t *preempt_disable;
	atomic_t *schedule_now;
	thread_t *owner;
} lock_t;

/*! \def lock_new
 */
#define lock_new(name) lock_t name = {
				atomic_init(0),
				NULL,
				NULL,
				NULL }	
/*! \def lock_new_nopreempt
 */
#define lock_new_nopreempt(name) lock_t name = {
				atomic_init(0),
				&preempt_disable,
				&schedule_now,
				NULL }

/*! \def lock_init
 */
#define lock_init() {atomic_init(0), NULL, NULL, NULL}

/*! \def lock_init_nopreempt
 */
#define lock_init_nopreempt() {atomic_init(0), &preempt_disable, &schedule_now, NULL}
	
/*! \brief Unlocks a kernel lock object
 */
void spin_unlock(lock_t *l);

#endif // KERNEL_LOCK_H
