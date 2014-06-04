/*! \file semaphore.c
 *  \bried This is the kernel API for semaphores
 */
#include "include/atomic.h"
#include "include/list.h"
#include "include/sched.h"
#include "include/semaphore.h"

// Defined in arch/arm/cortexM3/sched_asm.S 
extern void reschedule(void);

void static inline __attribute__((always_inline))
wait_for_switch(void)
{
	volatile s32_t tmp = atomic_read(&switch_count);
	
	while (tmp == atomic_read(&switch_count));
}

//extern thread_t *thread_current; FIXME: Add this and pull it out of sched.h

/*! \brief Use to aquire the semaphore or be blocked and be placed 
 *   on a queue. 
 *  \note Do not attempt to acquire a semaphore if you currently
 *        hold a lock. Use semaphores when the assciated overhead
 *        is much less than the time used to use the resource that
 *        the semaphore is protecting. Also do not use semaphores
 *        in interrupt context.
 */
void __attribute__((optimize(0))) 
semaphore_down(semaphore_t *s)
{
	// Preemption disabled because the scheduler runs in interrupt
	//     context and accesses the data structures below.
	atomic_inc(&preempt_disable);

	if (atomic_dec(&s->value)) {
		
		thread_current->blocked_on = s;

		list_add(&s->queue, NULL, &thread_current->block_list);

		atomic_dec(&preempt_disable);
	
		reschedule();
	
		wait_for_switch();
	} else {

		s->owner = thread_current;

		atomic_dec(&preempt_disable);
	}
}

/*! \brief Use this to make the semaphore available for other threads
 */
void __attribute__((optimize(0))) 
semaphore_up(semaphore_t *s)
{
	link_t *list_ptr;
	thread_t *thread_ptr;

	// Preemption disabled because the scheduler runs in interrupt
	//     context and accesses the data structures below.
	atomic_inc(&preempt_disable);
		
	atomic_inc(&s->value);

	if (NULL != list_get_head(&s->queue)) {

		list_ptr = list_remove(&s->queue, s->queue.head);

		thread_ptr = member_of(list_ptr, thread_t, block_list);
		
		thread_ptr->blocked_on = NULL;

		s->owner = thread_ptr;		
	} else {		
		s->owner = NULL;
	}

	atomic_dec(&preempt_disable);

}
