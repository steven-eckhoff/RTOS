/*! \file atomic.h
 *  \brief Low level atomic routines for ARMv7-M
 */
#ifndef ATOMIC_H
#define ATOMIC_H

#include "include/types.h"

/*! \brief Increments the value of an atomic type 
 */
bool static inline __attribute__((always_inline))
atomic_inc(atomic_t  *a)
{
	s32_t res = 0;

	__asm__ __volatile__ (
"1:	ldrex %0, %1\n"
"	add %0, #1\n"
"	strex r0, %0, %1\n"
"	cmp r0, #0\n"
"	bne 1b\n"
	: "+r" (res)
	: "m" (a->value)
	);

	return (res >= 0 ? true : false);
}

/*! \brief Decrements the value of an atomic type
 */
bool static inline __attribute__((always_inline))
atomic_dec(atomic_t  *a)
{
	s32_t res = 0;

	__asm__ __volatile__ (
"1:	ldrex %0, %1\n"
"	sub %0, #1\n"
"	strex r0, %0, %1\n"
"	cmp r0, #0\n"
"	bne 1b\n"
	: "+r" (res)
	: "m" (a->value)
	);

	return (res < 0 ? true : false);
}

/*! \brief Writes value to atomic type
 */
void static inline __attribute__((always_inline))
atomic_write(atomic_t  *a, s32_t value)
{
	__asm__ __volatile__ (
"	mov %1, r1\n"
"1:	ldrex r0, %0\n"
"	strex r0, r1, %0\n"
"	cmp r0, #0\n"
"	bne 1b\n"
	:
	: "m" (a->value), "r" (value)
	); 
}

/*! \brief Atomically adds one value to another
 */
void static inline __attribute__((always_inline))
atomic_add(atomic_t  *a, s32_t value)
{
	__asm__ __volatile__ (
"	ldrex r0, %0\n"
"1:	add r0, r0, %1\n"
"	strex r1, r0, %0\n"
"	cmp r1, #0\n"
"	bne 1b\n"
	:
	: "m" (a->value), "r" (value)
	);
}

#endif // ATOMIC_H
