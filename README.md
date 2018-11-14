RTOS
====

This is an RTOS that I started in school and I WAS working to improve and extend it. I may try to get this running on another board I have laying around, but I don't think it will happen any time soon.

Videos:

	- I will post links to videos on the wiki

Features (More coming):
	
	- hard real-time scheduling
	- rate monotonic scheduler
	- priority inheritance 
	- synchronization mechanisms

Supported Architectures (More coming):
	
	- ARMv7-M

Supported Boards (More coming):

	- lm3s8962 CAN Evaluation kit

Notes:

05/14/2014 - 	I have this RTOS working pretty well using rate monotonic scheduling.
		What is posted here will not allow you to build and run the RTOS yet. 
		This is because I was unhappy with how it was organized and now I am
		rewriting several pieces. For example there was no generic implementation
		for the list data structure. 

05/27/2014 -	I have added a list API for the kernel. I have built and ran code using 
		the new API, but it is not without bugs. I am currently ironing these out.

06/03/2014 -	I have tested semaphores running 8 threads contending for the display and
                this seemed to work. Despite this there are some bugs in the compiling and
                I will focus on this in the near future. Also there is a design flaw with
                the priority inheritance logic. With a lot of contention on a semaphore
                owned by a thread that has no budget the thread will frequently be scheduled. 
		This causes the budget to swell and compromise the feasability of the schedule.
