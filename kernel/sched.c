/*! \file sched.c
 *  \brief Kernel scheduling routines
 */
#include "include/atomic.h"
#include "include/lock.h"
#include "stack.h"
#include "include/sched.h"

thread_t thread_blocks[MAX_NUM_THREADS];
list_new(kernel_threads, DOUBLE, NULL, NULL);
thread_t *thread_current;

u32_t nextid;
u32_t numthreads;
u32_t timeslice;
s32_t preemptcount;
s32_t preemptasap;

/*! \brief initializes the kernel threads. Later this will change for dynamic allocation
 */
void threads_init(void) {
	u32_t i,j;

	nextid = 1;
	for(i = 0; i < MAX_NUM_THREADS; i++) {
		for(j = 0; j < STACK_SIZE; j++) {
			thread_blocks[i].stack[j] = (j << 16) | 0x0000ffaa; // recognizable pattern
		}
		thread_blocks[i].stack_top    = thread_blocks[i].stack;
		thread_blocks[i].stack_bottom = &(thread_blocks[i].stack[STACK_SIZE - 1]);
		thread_blocks[i].stack_size     = (u32_t)STACK_SIZE;
	}
	
	kthreads = NULL; //FIXME: This should go somewhere else
}

/*! \brief Creates a new thread
 */
int newthread(void(*task)(void), u32_t priority, u32_t period)
{
	int i;
	int ret;
	thread_t *thread_new;
	thread_t *thread_ptr;
	thread_t *thread_last_ptr;
	link_t *list_ptr;
	link_t *list_tail_ptr;

	ret = disableints();

	if (priorityority < 0)
		return -1;

//  Search for 1st available thread control block
	for(i = 0; (i < MAX_NUM_THREADS) && (thread_blocks[i].id != 0); i++);

// Return 0 if no thread control block is available
	if (MAX_NUM_THREADS == i)
        	return -1;

	thread_new = &(thread_blocks[i]);

	thread_new->stack_ptr		= thread_new->stack_bottom;
	thread_new->id			= nextid++;
	thread_new->priority		= priority; //Based on period in RM
	thread_new->period_timer_reload	= period;
	thread_new->period_timer	= period;
	thread_new->run_count		= 0;
	thread_new->sleep_count		= 0;
	thread_new->sleep_total		= 0;
	thread_new->spinning_on		= NULL;
	thread_new->blocked_on		= NULL;
	link_init(&thread_new->thread_list);
	link_init(&thread_new->block_list);

	list_ptr = list_get_head(&kernel_threads);
	
	if (NULL != list_ptr) {
	
		list_tail_ptr = list_get_tail(&kernel_threads);
	
		thread_ptr = member_of(list_ptr, thread_t, thread_list);	
		
		// Threads listed by monotonically increasing priority
		// Priority 0 is the most important
		while ((list_ptr != list_tail_ptr) 
				&& (thread_new->priority > thread_ptr->priority)) {
			thread_last_ptr = thread_ptr;
			list_ptr = list_ptr->next;
			thread_ptr = member_of(list_ptr, thread_t, thread_list);
		}

		list_insert_link(&kernel_threads, thread_last_ptr, thread_ptr);
	} else {
		list_add_head(&kernel_threads, thread_new);
	}

	thread_new->stack_ptr = stack_init(thread_new->stack_ptr, task);

	if (!ret) // Interrupts were enabled
		enableints();
	
	return 0;
}

#define period_expired(x) (0 == (x)->period)

#define period_reset(x) ((x)->period = (x)->period_reload)

#define budget_depleted(x) (0 == (x)->budget)

#define budget_reset(x) ((x)->budget = (x)->budget_reload)

#define budget_consume(x) ({			\
		if (0 != (x)->budget)		\
			--((x)->budget); })

#define ready2run(x) ( (period_expired(x) || !budget_depleted(x))	\
			&& !sleeping(x) )

#define blocked(x) (NULL != (x)->blocked_on)

#define spinning(x) (NULL != (x)->spinning_on)

#define sleeping(x) (0 != (x)->sleep_count)

#define get_sema4_owner(x) ((x)->blocked_on->owner)

#define get_lock_owner(x) ((x)->spinning_on->owner)

#define thread_next(lp, tp) ( {						\
		(lp) = (lp)->next;					\
		(tp) = member_of((lp), thread_t, thread_list); })

/*! \def lock_test_nopreempt
 *  \brief Test a lock if you know you wont be preempted not MP safe
 */
#define lock_test_nopreempt(x) (0 == (x)->atomic.value)

void __attribute__((optimize(0))) nextthread(void)
{
	static thread_t *thread_ptr; //FIXME: Something not stack friendly
	static link_t *list_ptr;
	static link_t *list_tail_ptr;
	static u32_t highpriority;

	// Higher priority threads appear first in the list

	list_ptr = list_get_head(&kernel_threads);
	list_tail_ptr = list_get_tail(&kernel_threads);

	thread_ptr = member_of(list_ptr, thread_t, thread_list);

	while (list_ptr != list_tail_ptr) { //FIXME: Simplify the list iteration
		if (ready2run(thread_ptr)) {
			thread_current = thread_ptr;
			break;
		}
		thread_next(list_ptr, thread_ptr);
	}

	if (period_expired(thread_current)) {
		period_reset(thread_current);
		budget_reset(thread_current);
	}

	while (blocked(thread_current) || spinning(thread_current)) {
		if (blocked(thread_current)) {
			thread_current = get_sema4_owner(thread_current);
		} else {
			if (lock_test_nopreempt(thread_current->spinning_on))
				break;// Lock is unlocked so run spinning thread
			else
				thread_current = get_lock_owner(thread_current);
		}
	}

	thread_current->run_count++;

	budget_consume(thread_current);
}

thread_t *firstthread(void)
{
	return member_of(list_get_head(&kernel_threads), thread_t, thread_list);
}

void sched_init(void)
{
	threads_init();
}

void sleep(u32_t count)
{
// CRITICAL SECTION
	atomic_write(&thread_current->sleep_count, count);
	//atomic_add(&thread_current->sleep_total, count); //FIXME: atomic_add is not tested
	schedule();
}
