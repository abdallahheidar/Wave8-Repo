/*****************************************************************************/
/*					SysCtr_Lcfg.c												 */	
/*****************************************************************************/

#include "SysCtr_Lcfg.h"
#include "SysCtr_Types.h"

ClkFreq_type ClkFreq = FREQ_40MHz ;

#define CLOCK_FREQ 40

/* Clock Gates */

int CfgArr[NUM_OF_PRIPHERALS] =
{
	/*WD0  */   DISABLE, 
	/*WD1  */   DISABLE,
	
	/*TIMER0 */   DISABLE,
	/*TIMER1 */   DISABLE,
	/*TIMER2 */   DISABLE,
	/*TIMER3 */   DISABLE,
	/*TIMER4 */   DISABLE,
	/*TIMER5 */   DISABLE,

	/*GpioA  */   ENABLE, 
	/*GpioB  */   ENABLE,
	/*GpioC  */   ENABLE,
	/*GpioD  */   ENABLE,
	/*GpioE  */   ENABLE,
	/*GpioF  */   ENABLE,

	
	/*DMA  */   DISABLE,
	
	/*HIB  */   DISABLE,
	
	/*UART0  */   DISABLE,
	/*UART1  */   DISABLE,
	/*UART2 */   DISABLE,
	/*UART3 */   DISABLE,
	/*UART4 */   DISABLE,
	/*UART5 */   DISABLE,
	/*UART6 */   DISABLE,
	/*UART7 */   DISABLE	,
	
		
	/*SSI0  */   DISABLE,
	/*SSI1  */   DISABLE,
	/*SSI2 */   DISABLE,
	/*SSI3 */   DISABLE,
	
	/*I2C0 */   DISABLE,
	/*I2C1 */   DISABLE,
	/*I2C2 */   DISABLE,
	/*I2C3 */   DISABLE	,
	
		
	/*USB  */   DISABLE,
	
	/*CAN0  */   DISABLE,
	/*CAN1 */   DISABLE,
	
	/*ADC0 */   ENABLE,
	/*ADC1 */   DISABLE,
	
	/*ACMP */   DISABLE,
	
	/*PWM0 */   DISABLE,
	
	/*PWM1 */   DISABLE
	
};

