#ifndef BSP_H
#define BSP_H

// FIXME: Maybe not the best. Rethinik this. 
#include "interrupt.h"
#include "lm3s8962.h"
#include "include/types.h"

#define disableints() IntMasterDisable()
#define enableints() IntMasterEnable()

void heartbeat_init(void);

void heartbeat(void);

void board_launch(unsigned long slice);

void display_init(void);

void string_draw(const char *s, unsigned long x, unsigned long y, unsigned char level);

void pwm_init(u32_t pwm);

void pwm_set_duty(u32_t pwm, u32_t duty);
#endif // BSP_H
