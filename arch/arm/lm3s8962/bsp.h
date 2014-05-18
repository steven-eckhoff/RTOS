#ifndef BSP_H
#define BSP_H

#include "lm3s8962.h"
#include "interrupt.h"

#define disableints() IntMasterDisable()
#define enableints() IntMasterEnable()

void heartbeat_init(void);

void heartbeat(void);

void board_launch(unsigned long slice);

void display_init(void);

void string_draw(const char *s, unsigned long x, unsigned long y, unsigned char level);

void pwm_init(unsigned long pwm);

void pwm_set_duty(unsigned long pwm, unsigned long duty);

#endif // BSP_H
