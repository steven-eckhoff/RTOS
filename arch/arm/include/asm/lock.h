/*! \file lock.h
 *  \brief This file defines low leve lock routine for ARMv7-M
 */
#ifndef LOCK_H
#define LOCK_H

/*! \brief Spin lock routine for kernel lock object
 */
void spin_lock(lock_t *l)
{
	atomic_t *a = &l->atomic;
	
	__asm__ __volatile__ (
"	mov r0, #1\n"
"1:	ldrex r1, %0\n"
"	cmp r1, #0\n"
"	itt eq\n"
"	strexeq r1, r0, %0\n"
"	cmpeq r1, #0\n"
"	bne 1b"
	:
	: "m" (a->value) );
}

#endif // LOCK_H
