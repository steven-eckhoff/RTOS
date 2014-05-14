/*! \file semaphore.h
 *  \brief This file contains the kernel api for semaphores
 *  \author Steven W. Eckhoff
 *  \bug No known bugs
 */

#ifndef KERNEL_SEMAPHORE_H
#define KERNEL_SEMAPHORE_H

#include "include/types.h"
#include "include/lock.h"
#include "include/list.h"
#include "include/shced.h"

/*! \typedef semaphore
 *  \brief Provides a semaphore
 */
typedef struct {
	atomic_t value;
	thread_t *owner;
	queue_t queue;
} semaphore_t;

/*! \brief
 */
void semaphore_destroy(semaphore_t *s);

/*! \brief
 */
void semaphore_down(semaphore_t *s);

/*! \brief
 */
void semaphore_up(semaphore_t *s);

/*! \def semaphore_new
 *  \brief Creates a new semaphore
 */
#define semaphore_new(name, value) semaphore_t name = { atomic_init(value),
							NULL,
							queue_init_nopreempt }

#endif // KERNEL_SEMAPHORE_H
