  
#define NVIC_INT_CTRL	0xE000ED04	// Interrupt control state register.
#define NVIC_PENDSVSET	0x10000000	// Value to trigger PendSV exception.
#define NVIC_ST_CURRENT_R 0xE000E018
.extern thread_current
.extern nextthread

.global schedule
.global reschedule
.global runfirstthread
.global pendsv_handler
.global resettick

.data

.align 2
resettick:
.word 0x0

.text
.syntax unified

	.thumb_func
schedule:
	ldr r0, =resettick
	mov r1, #1
	str r1, [r0]
	ldr r0, =NVIC_INT_CTRL
	ldr r1, =NVIC_PENDSVSET
	str r1, [r0]
	bx  lr

	.thumb_func
reschedule:
	ldr r0, =resettick
	mov r1, #0
	str r1, [r0]
	ldr r0, =NVIC_INT_CTRL
	ldr r1, =NVIC_PENDSVSET
	str r1, [r0]
	bx  lr

	.thumb_func
runfirstthread:
	ldr	r0,  =thread_current
	ldr	r0,  [r0]
	ldr	r0,  [r0, #8]		// r0 is new process sp; sp = ostcbhighrdy->ostcbstkptr;
	ldm	r0,  {r4-r11}		// restore r4-11 from new process stack
	adds	r0,  r0, #0x24
	ldm	r0,  {r1-r3}		// restore r1-3
	adds	r0,  r0, #0x0c
	ldr	r13, [r0, #4]		// restore lr
	ldr	r12, [r0, #8]		// save thread address into r12
	adds	r0,  r0, #12		// move r0 to end of stack
	mov	r13,  r0		// load new stack value into sp
	bx	r12			// jump to thread
osstarthang:
	b	osstarthang		// this line should never be executed

	.thumb_func	
pendsv_handler:
	cpsid	i			//prevent interruption during context switch

	ldr     r1, =thread_current	// r1 points to &topstackpt
        ldr     r1, [r1]		// r1 points to topstackpt
	adds    r1, r1, #8		// r1 points to stackpt
        
	mov     r0, r13			// r13 is sp - sp points to memory
	subs    r0, r0, #0x20		// Subtract 4x8=32 to store r4-r11
        stm     r0, {r4-r11}		// Store goes up in memory instead of down

        str     r0, [r1]		// Save new sp into tcb
	mov	r4, r14			// Save link register to r4
	ldr     r3, =nextthread		// Update thread_current
	blx     r3			// Call function nextthread()
	mov     r14, r4			// Restore the link register

        ldr     r0, =thread_current	// r0 holds address of thread_current
	ldr     r1, [r0]		// r1 holds address of actual current tcb 

        ldr     r0, [r1, #8]		// r0 is new process sp; sp = ostcbhighrdy->ostcbstkptr;
        ldm     r0, {r4-r11}		// restore r4-11 from new process stack
        adds    r0, r0, #0x20
        mov     r13, r0			// load msp with new process sp
        orr     lr, lr, #0x09		// ensure exception return uses process stack
	ldr	r0, =resettick		//
	ldr	r0, [r0]
	cmp	r0, #1
	ittt	eq
	ldreq	r0, =NVIC_ST_CURRENT_R  // Load the systick timer register address to r0
	moveq	r1, #0			// 
	streq	r1, [r0]		// Set systick timer reg to zero
        cpsie   i
        bx      lr			// exception return will restore remaining context
