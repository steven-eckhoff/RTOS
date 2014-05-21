#include "include/sched.h"
#include "include/time.h"
#include "include/atomic.h"

extern thread_t thread_blocks[];
extern atomic_t preempt_disable;
extern atomic_t schedule_now;

extern void schedule(void);

void systick_handler (void) {
	unsigned long i;

	systimeinc(); 
	for(i = 0; i < MAX_NUM_THREADS; ++i) {
		if (atomic_read(&(thread_blocks[i]).sleep_count) > 0)
			atomic_dec(&(thread_blocks[i]).sleep_count);
		
		if (thread_blocks[i].period > 0)
			--thread_blocks[i].period;
	}
	if (0 == atomic_read(&preempt_disable))
		schedule();
	else
		atomic_inc(&schedule_now); // FIXME: This is not used
}
