#include "inc/lm3s8962.h"
#include "led.h"

void led_init(void)
{
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;	// Enable GPIO
	__asm__ ("nop");			// delay
	GPIO_PORTF_DIR_R = 0x01;		// Output
	GPIO_PORTF_DEN_R = 0x01;		// Enable Digital
}

void led_on(void)
{
	GPIO_PORTF_DATA_R |= 0x01;
}

void led_off(void)
{
	GPIO_PORTF_DATA_R &= ~(0x01);
}

void led_toggle(void)
{
	GPIO_PORTF_DATA_R ^= 0x01;
}
