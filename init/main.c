#include "include/atomic.h"
#include "include/lock.h"
#include "include/semaphore.h"
#include "include/sched.h"
#include "bsp.h"
#include "include/kernel.h"
//#include "include/aperiodic.h"

#define digi2char(x) ('0' + x)

unsigned long numcreated;
unsigned long count1;   // number of times thread1 loops
unsigned long count2;   // number of times thread2 loops
unsigned long count3;   // number of times thread3 loops
unsigned long count4;   // number of times thread4 loops
unsigned long count5;   // number of times thread5 loops
unsigned long count6;
unsigned long count7;
unsigned long count8;

semaphore_new(sema4_display, 1);

int itoa10(unsigned long num, char *buf, const int buflen)
{
	int i, j;
	char tmp[100];

	if (buflen < 2 || buflen > 100)
		return -1;

	if (0 == num) {
		buf[0] = '0';
		buf[1] = '\0';
		return 0;
	}

	for (i = 0; i < buflen && num > 0; i++) {
		tmp[i] = digi2char(num % 10);
		num = num / 10;
	}

	if (i == buflen) {
		return -1;
	} else {
		for (j = 0; j < i; j++) { // Reverse string for correct ordering
			buf[j] = tmp[i - j - 1];
		}
		buf[j] = '\0';
		return 0;
	}
}

void thread_debug(const char *name, unsigned long id, unsigned long value)
{
	int i;
	char buf[25];
	
	for(i = 0; name[i] != '\0'; i++)
		buf[i] = name[i];
	itoa10(value, &(buf[i]), 25);
	semaphore_down(&sema4_display);
	string_draw(buf, 0, (id - 1) * 11, 11);
	semaphore_up(&sema4_display);
}

void thread1(void){
	count1 = 0;
	for(;;){
		count1++;
	}
}
void thread2(void){
	count2 = 0;      
	for(;;){
		count2++;
	}
}
void thread3(void){
	count3 = 0;          
	for(;;){
		count3++;
	}
}
void thread4(void){
	count4 = 0;
	for(;;){
		count4++;
		sleep(1);
	}
}
void thread5(void){
	count5 = 0;
	for(;;){
		count5++;
	}
}
void thread6(void){
	count6 = 0;
	for(;;){
		count6++;
	}
}
void thread7(void){
	count7 = 0;
	for(;;){
		count7++;
	}
}
void thread8(void){
	count8 = 0;
	for(;;){
		count8++;
	}
}

void thread_print(void)
{
	for(;;) {
		thread_debug("thread1: ", 1, count1);
		thread_debug("thread2: ", 2, count2);
		thread_debug("thread3: ", 3, count3);
		thread_debug("thread4: ", 4, count4);
//		thread_debug("thread5: ", 5, count5);
//		thread_debug("thread6: ", 6, count6);
//		thread_debug("thread7: ", 7, count7);
//		thread_debug("thread8: ", 8, count8);
		sleep(50);
	}
}

void delay(u32_t delay)
{
	while(delay > 0) {
		--delay;
	}
}

int main(void){ 
	heartbeat_init();
	display_init();
	kernel_init();           // initialize, disable interrupts
//	newthread(&heartbeat,9, 250, 1);
	newthread(&thread1, 0, 100, 10);
	newthread(&thread2, 1, 100, 10);
	newthread(&thread3, 2, 100, 5);
	newthread(&thread4, 3, 100, 10);
	//newthread(&thread_print, 4, 200, 5);
 	kernel_launch(TIMESLICE); // doesn't return, interrupts enabled in here
  	return 0;             // this never executes
}

