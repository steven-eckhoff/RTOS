/*! \file sched.h
 *  \brief kernel scheduling 
 */
#ifndef KERNEL_SCHED_H
#define KERNEL_SCHED_H

#include "include/types.h"
#include "include/lock.h"
#include "include/semaphore.h"
#include "include/list.h"
#include "bsp.h"

#define MAX_NUM_THREADS	13
#define STACK_SIZE	512
#define PRIORITY_LEVELS	MAX_NUM_THREADS
#define MAX_PRIORITY (PRIORITY_LEVELS - 1)

/*! \typedef
 */
typedef struct thread {
	u32_t  *stack_top;
	u32_t  *stack_bottom;
	u32_t  *stack_ptr;
	u32_t  stack_size;
	u32_t  id;
	u32_t  priority;
	u32_t  period_reload;
	u32_t  period;
	u32_t  budget_reload;
	u32_t  budget;
	u32_t  run_count;
	atomic_t sleep_count;
	atomic_t sleep_total;
	lock_t *spinning_on;
	semaphore_t *blocked_on;
	link_t thread_list;
	link_t block_list;
	u32_t  stack[STACK_SIZE];
} thread_t;

//FIXME: Pull all of these out and extern them in each *.c that needs them
extern thread_t thread_blocks[];
extern atomic_t preempt_disable; //FIXME: Convert to IPC
extern atomic_t schedule_now; //FIXME: Convert to IPC
extern thread_t *thread_current;
extern list_t kernel_threads;

// Defined in arch/arm/cortexM3/sched_asm.S
extern void schedule(void);
extern void reschedule(void);

/*! \brief
 */
void sched_init(void);

/*! \brief Call to get the first thread to run
 *  \return Returns the highest priority thread from the kernel thread list
 */
thread_t *firstthread(void);

/*! \brief
 */
int newthread(void(*task)(void), u32_t priority, u32_t period, u32_t budget);

/*! \brief
 */
void sleep(u32_t count);

#endif // KERNEL_SCHED_H
