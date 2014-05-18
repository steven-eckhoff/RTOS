/*! \file lock.c
 *  \brief API for kernel locks
 */

#include "include/lock.h"
#include "asm/lock.h"

/*! \brief Make lock available for other threads
 */
void spin_unlock(lock_t *l)
{
	atomic_write(&l->atomic, 0);
}
