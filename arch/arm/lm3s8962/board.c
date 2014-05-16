#include "hw_types.h"
#include "sysctl.h"
#include "systick.h"
#include "interrupt.h"
#include "lm3s8962.h"
#include "board.h"

void board_init(void)
{
// Disable syspem interrupts
	IntMasterDisable();
// SYSTEM CLOCK
// Run At 50MHz
// Set the clocking to run directly from the cryspal.
// Externl Crystal 8MHz and Use PLL and SYSDIV_4
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
			SYSCTL_XTAL_8MHZ);
// SYSTICK
	SysTickEnable();
// Enable SysTick Interrupt
	SysTickIntEnable();
// Set PendSV priority to lowest
	NVIC_SYS_PRI2_R |= 0xE0000000L;
}

