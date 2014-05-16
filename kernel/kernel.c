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

/*! \brief This is the idle thread
 *  \note This is the lowest priority thread it keeps the kernel
          from running of the rails. It may be useful to measure 
          how much this thread runs.
 */
void idlethread(void) 
{
	volatile u32_t tmp; //Telling compiler hands off. 
	for(;;) {
		tmp++;
	}
}

/*! \brief This routine initializes the system to start running.
 */
void kernel_init(void)
{
	board_init(); //FIXME: This may make more sense somewhere else
	systimeinit();
	sched_init();
	newthread(&idlethread, PRIORITY_LEVELS - 1);
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
