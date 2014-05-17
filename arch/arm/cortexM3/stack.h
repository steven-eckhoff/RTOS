/*! \file stack.h
 */
#ifndef STACK_H
#define STACK_H

/*! \brief Initializes the thread stack
 *  \param sp the stack pointer
 *  \task pointer to the threads code text
 */
unsigned long static inline *stack_init(unsigned long *sp, void(*task)(void))
{
// Push PSR
	(*sp) = (unsigned long)0x01000000L;
// Push PC pointing to function code
	*(--sp) = (unsigned long)task;
#ifdef STACK_DEBUG
// Push LR
	*(--sp) = 0xFFFFFFF9L;
// Push R12
	*(--sp) = 0x12121212L;
// Push R3
	*(--sp) = 0x03030303L;
// Push R2
	*(--sp) = 0x02020202L;
// Push R1
	*(--sp) = 0x01010101L;
// Push R0
	*(--sp) = 0xAFAFAFAFL;
// Push R11
	*(--sp) = 0xBBBBBBBBL;
// Push R10
	*(--sp) = 0xAAAAAAAAL;
// Push R9
	*(--sp) = 0x99999999L;
// Push R8
	*(--sp) = 0x88888888L;
// Push R7
	*(--sp) = 0x77777777L;
// Push R6
	*(--sp) = 0x66666666L;
// Push R5
	*(--sp) = 0x55555555L;
// Push R4
	*(--sp) = 0x44444444L;
	return sp;
#else
	return (sp - 14);
#endif
}

#endif // STACK_H
