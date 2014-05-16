/*! \file kernel.c
 *  \brief Routines for starting kernel and other stuff
 */
#include "include/kernel.h"
#include "board.h"
#include "bsp.h"
#include "include/sched.h"
#include "include/time.h"

// Defined in arch/arm/cortexM3/sched_asm.S
extern void runfirstthread(void); //kernel_asm.S

volatile u32_t idle_counter; // Telling compiler hands off

/*! \brief This is the idle thread
 *  \note This is the lowest priority thread it keeps the kernel
          from running of the rails. It may be useful to measure 
          how much this thread runs.
 */
void idlethread(void) 
{
	idle_counter = 0;
	for(;;) {
		++idle_counter;
	}
}

/*! \brief This routine initializes the system to start running.
 */
void kernel_init(void)
{
	board_init(); //FIXME: This may make more sense somewhere else
	systimeinit();
	sched_init();
	// The period of the idle thread will alwasy be up and the budget depleted
	// This should be improved.
	newthread(&idlethread, PRIORITY_LEVELS - 1, 0, 1);
}

/*! \brief This launches the kernel
 */
void kernel_launch(unsigned long slice)
{
	
	thread_current = firstthread();

	timeslice = slice;
	
	board_launch(slice);

	runfirstthread();

	while(1);
}
