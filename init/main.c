#include "include/atomic.h"
#include "include/lock.h"
#include "include/semaphore.h"
#include "include/sched.h"
#include "bsp.h"
#include "include/kernel.h"
//#include "include/aperiodic.h"

unsigned long numcreated;
unsigned long volatile count1;   // number of times thread1 loops
unsigned long volatile count2;   // number of times thread2 loops
unsigned long volatile count3;   // number of times thread3 loops
unsigned long volatile count4;   // number of times thread4 loops
unsigned long volatile count5;   // number of times thread5 loops
unsigned long volatile count6;
unsigned long volatile count7;
unsigned long volatile count8;

semaphore_new(sema4_display, 1);

void delay(u32_t count)
{
	while(count > 0) {
		--count;
	}
}

int itoa10(unsigned long num, char *buf, const int buflen)
{
	int i, j;
	#define BUFFER_MIN 2
	#define TMP_BUFFER_LEN 10
	char tmp_buffer[TMP_BUFFER_LEN];

	if (buflen < BUFFER_MIN || buflen > TMP_BUFFER_LEN)
		return -1;

	if (0 == num) {
		buf[0] = '0';
		buf[1] = '\0';
		return 0;
	}

	for (i = 0; i < buflen && num > 0; i++) {
		tmp_buffer[i] = '0' + (num % 10);
		num = num / 10;
	}

	if (i == buflen && num != 0) { // num is too large to fit in buffer
		return -1;
	} else {
		for (j = 0; j < i; j++) { // Reverse string for correct ordering
			buf[j] = tmp_buffer[i - 1 - j];
		}
		if (j < buflen)
			buf[j] = '\0';
		else
			return -1;
	}
	return 0;
}

void thread_debug_(const char *name, unsigned long id, unsigned long value)
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

#define thread_debug(name, id, value)				\
do {								\
	if(value % 1 == 0)					\
		thread_debug_(name, id, value);			\
} while(0)

void thread1(void){
	count1 = 0;
	for(;;){
		count1++;
		thread_debug("thread1: ", 1, count1);
	}
}
void thread2(void){
	count2 = 0;      
	for(;;){
		count2++;
		thread_debug("thread2: ", 2, count2);
	}
}
void thread3(void){
	count3 = 0;          
	for(;;){
		count3++;
		thread_debug("thread3: ", 3, count3);
	}
}
void thread4(void){
	count4 = 0;
	for(;;){
		count4++;
		thread_debug("thread4: ", 4, count4);
	}
}
void thread5(void){
	count5 = 0;
	for(;;){
		count5++;
		thread_debug("thread5: ", 5, count5);
	}
}
void thread6(void){
	count6 = 0;
	for(;;){
		count6++;
		thread_debug("thread6: ", 6, count6);
	}
}
void thread7(void){
	count7 = 0;
	for(;;){
		count7++;
		thread_debug("thread7: ", 7, count7);
	}
}
void thread8(void){
	count8 = 0;
	for(;;){
		count8++;
		thread_debug("thread8: ", 8, count8);
	}
}

void thread_print(void)
{
	static u32_t count = 0;
	for(;;) {
		u32_t select = count % 8;
		switch (select) {
		case 0:
			thread_debug("thread1: ", 1, count1);
			break;
		case 1:
			thread_debug("thread2: ", 2, count2);
			break;
		case 2:
			thread_debug("thread3: ", 3, count3);
			break;
		case 3:
			thread_debug("thread4: ", 4, count4);
			break;
		case 4:
			thread_debug("thread5: ", 5, count5);
			break;
		case 5:
			thread_debug("thread6: ", 6, count6);
			break;
		case 6:
			thread_debug("thread7: ", 7, count7);
			break;
		case 7:
			thread_debug("thread8: ", 8, count8);
			break;
		}
		++count;
		schedule();
	}
}

int main(void){ 
	heartbeat_init();
	display_init();
	kernel_init();           // initialize, disable interrupts
//	newthread(&thread_print, 0, 5, 1);
	newthread(&thread1, 1, 100, 1);
	newthread(&thread2, 2, 100, 10);
	newthread(&thread3, 3, 100, 5);
	newthread(&thread4, 4, 100, 5);
	newthread(&thread5, 5, 100, 5);
	newthread(&thread6, 6, 100, 5);
	newthread(&thread7, 7, 100, 10);
	newthread(&thread8, 8, 100, 10);
	newthread(&heartbeat,0, 250, 1);
 	kernel_launch(TIMESLICE); // doesn't return, interrupts enabled in here
  	return 0;             // this never executes
}

