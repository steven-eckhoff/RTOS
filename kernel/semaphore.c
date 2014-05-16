#include "include/atomic.h"
#include "include/list.h"
#include "include/sched.h"
#include "include/semaphore.h"

extern void reschedule(void);

void semaphore_down(sema4_t *s)
{
	// Preemption disabled because the scheduler runs in interrupt
	//     context and accesses the data structures below.
	atomic_inc(&preempt_disable);

	if (atomic_dec(&s->value)) {
		
		thread_current->blocked_on = s;

		list_add_tail(&kernel_threads, &thread_current->thread_list);

		atomic_dec(&preempt_disable); //FIXME: This could me moved out
	
		reschedule();
	} else {

		s->owner = current_thread;	
	}
	
	atomic_dec(&preempt_disable);
}

void semaphore_up(sema4_t *s)
{
	link_t *list_ptr;
	thread_t *thread_ptr;

	// Preemption disabled because the scheduler runs in interrupt
	//     context and accesses the data structures below.
	atomic_inc(&preempt_disable);

	if (NULL != list_get_head(&s->queue)) {

		list_ptr = list_remove_head(&s->queue);

		thread_ptr = member_of(list_ptr, thread_t, block_list);
		
		thread_ptr->blocked_on = NULL;

		s->owner = thread_pt;		
	}

		atomic_dec(&preempt_disable);
}
