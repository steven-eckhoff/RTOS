#include "hw_memmap.h"
#include "hw_types.h"
#include "sysctl.h"
#include "systick.h"
#include "led.h"
#include "rit128x96x4.h"
#include "gpio.h"
#include "pwm.h"
#include "bsp.h"
#include "interrupt.h"
#include "lm3s8962.h"

void heartbeat_init(void)
{
	led_init();
	led_on();
}

void heartbeat(void)
{
	for(;;) {
		led_toggle();
//		sleep(250); // FIXME: Add a calculation based on the timeslice
	}
}

void board_launch(unsigned long slice)
{
	IntMasterEnable();

	SysTickPeriodSet(slice);
}

void display_init(void)
{	
	RIT128x96x4Init(1000000); // Init OLED
}

void string_draw(const char *s, unsigned long x, unsigned long y, unsigned char level)
{
	RIT128x96x4StringDraw(s, x, y, level);
}

void pwm_init(unsigned long pwm)
{
	unsigned long period = SysCtlClockGet() / 333; //333Hz (Assume PWM clock == sysclock)
	unsigned long duty = (period * 50) / 100;

	switch (pwm) {
	case 0:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		
//		delay(5);

		GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

		PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

		PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty);

		PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
		PWMGenEnable(PWM0_BASE, PWM_GEN_0);
		break;
	case 1:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

		GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1);

		PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

		PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, period);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, duty);

		PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
		PWMGenEnable(PWM0_BASE, PWM_GEN_0);
		break;
	case 2:

/*
void PanTilt_Init(void){
    #if (SYS_PWM_CLOCK_DIV == 16)
        SysCtlPWMClockSet(SYSCTL_PWMDIV_16); // Divide system clock by 16
    #endif
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM); // Enable PWM peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // PWM0 is at PF0
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1); // PWM0 is at PF0
    PWMGenConfigure(PWM_BASE, PWM_GEN_1, 
                    PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC); // 
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, PWM2_PERIOD*SYS_CLOCK_N_MHZ/SYS_PWM_CLOCK_DIV); // 
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_2, SERVO_FRONT_PAN_90*SYS_CLOCK_N_MHZ/SYS_PWM_CLOCK_DIV); // 1.25 ms = center
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_3, SERVO_FRONT_TILT_0*SYS_CLOCK_N_MHZ/SYS_PWM_CLOCK_DIV); // 1.25 ms = center
    PWMOutputState(PWM_BASE, (PWM_OUT_2_BIT|PWM_OUT_3_BIT), 1); // Enable output
    PWMGenEnable(PWM_BASE, PWM_GEN_1); // Start timer in generator 0
} 
*/
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
//		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
//		delay(10);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

//		delay(10);
		
		GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_0);
//		delay(10);

		PWMGenConfigure(PWM_BASE, PWM_GEN_1,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
//		delay(10);

		PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, period);
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_2, duty);

		PWMOutputState(PWM_BASE, PWM_OUT_2_BIT, true);

		PWMGenEnable(PWM_BASE, PWM_GEN_1);
		break;
	case 3: 
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_1);
		PWMGenConfigure(PWM_BASE, PWM_GEN_1,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
		PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, period);
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_3, duty);
		PWMOutputState(PWM_BASE, PWM_OUT_3_BIT, true);
		PWMGenEnable(PWM_BASE, PWM_GEN_1);
		break;
/*	case 4:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM2);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_0);
		PWMGenConfigure(PWM2_BASE, PWM_GEN_2,
                    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
		PWMGenPeriodSet(PWM2_BASE, PWM_GEN_2, period);
		PWMPulseWidthSet(PWM2_BASE, PWM_OUT_2, duty);
		PWMOutputState(PWM2_BASE, PWM_OUT_2_BIT, true);
		PWMGenEnable(PWM2_BASE, PWM_GEN_2);
		break;
	case 5:
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM2);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_1);
		PWMGenConfigure(PWM2_BASE, PWM_GEN_2,
                    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
		PWMGenPeriodSet(PWM2_BASE, PWM_GEN_2, period);
		PWMPulseWidthSet(PWM2_BASE, PWM_OUT_2, duty);
		PWMOutputState(PWM2_BASE, PWM_OUT_2_BIT, true);
		PWMGenEnable(PWM2_BASE, PWM_GEN_2);
		break;*/
	default :
		break;
	}
}

void pwm_set_duty(unsigned long pwm, unsigned long duty)
{
	unsigned long period;
	
	if (pwm == 0) {
		period = PWMGenPeriodGet(PWM_BASE, PWM_GEN_0);
		duty = (period * duty) / 100;
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, duty);
	} else if (pwm == 2) {
		period = PWMGenPeriodGet(PWM_BASE, PWM_GEN_1);
		duty = (period * duty) / 100;
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_2, duty);
	} else if (pwm == 3) {
		period = PWMGenPeriodGet(PWM_BASE, PWM_GEN_1);
		duty = (period * duty) / 100;
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_3, duty);

	}
}
