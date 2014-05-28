RTOS
====

This is an RTOS that I started in school and now I am working to improve and extend it.

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

5/14/2014 - 	I have this RTOS working pretty well using rate monotonic scheduling.
		What is posted here will not allow you to build and run the RTOS yet. 
		This is because I was unhappy with how it was organized and now I am
		rewriting several pieces. For example there was no generic implementation
		for the list data structure. 

5/27/2014 -	I have added a list API for the kernel. I have built and ran code using 
		the new API, but it is not without bugs. I am currently ironing these out.
