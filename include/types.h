/*! \file types.h
 *  \brief This file defines standard kernel types for ARMv7-M
 */
#ifndef TYPES_H
#define TYPES_H

/*! \def NULL
 *  \brief This is a null pointer
 */
#define NULL ((void *)0)

/*! \typedef bool
 *  \brief This is a boolean
 */
typedef enum {FALSE, TRUE} bool;

/*! \typedef s32_t
 *  \brief This is a signed 32bit type
 */
typedef long s32_t;

/*! \typedef u32_t
 *  \brief This is an unsigned 32bit type
 */
typedef unsigned long u32_t;

#endif // TYPES_H
