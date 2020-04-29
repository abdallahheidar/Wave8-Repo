#include "tm4c123gh6pmRegisters.h"



//Subroutine to initilize PortF
void PortF_Init(void){
	int delay;
  SYSCTL_RCGC2_R |= 0x00000008;     // 1) Activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // Allow time for clock to start
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   // 2) Unlock GPIO Port F
  GPIO_PORTD_CR_R = 0x000000FF;           // Allow changes to PF4-0
//Only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTD_AMSEL_R = 0x00;        // 3) disable analog on PortF
  GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTD_DIR_R = 0xFF;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTD_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
            // enable pull-up on PF0 and PF4
  GPIO_PORTD_DEN_R = 0xFF;          // 7) enable digital I/O on PF4-0
}

//The code start here....
int main(void) {
//---->Initilization
	PortF_Init();
volatile float result;
/* enable clocks */
SYSCTL_RCGCGPIO_R |= 0x10; /* enable clock to GPIOE (AIN0 is on PE3) */
SYSCTL_RCGCADC_R |= 0x1; /* enable clock to ADC0 */
/* initialize PE3 for AIN0 input */
GPIO_PORTE_AFSEL_R |= 0x8; /* enable alternate function */
GPIO_PORTE_DEN_R &= ~0x8; /* disable digital function */
GPIO_PORTE_AMSEL_R |= 0x8; /* enable analog function */
/* initialize ADC0 */
ADC0_ACTSS_R &= ~0x8; /* disable SS3 during configuration */
ADC0_EMUX_R &= ~0xF000; /* software trigger conversion */
ADC0_SSMUX3_R = 0x0; /* get input from channel 0 */
ADC0_SSCTL3_R |= 0x0; /* take one sample at a time, set flag at 1st sample */
ADC0_ACTSS_R |= 0x8; /* enable ADC0 sequencer 3 */

// Pin Naming
	int PF0;
	int PF4;

//---->Loop
	while(1){
ADC0_PSSI_R |= 0x8; /* start a conversion sequence 3 */
while ((ADC0_RIS_R & 0x8) == 0); /* wait for conversion complete */
result = ADC0_SSFIFO3_R; /* read conversion result */
ADC0_ISC_R = 0x8; /* clear completion flag */

 result=result*3.3/4096;
		if(result<=0.6)
		{
		GPIO_PORTD_DATA_R &= 0x00;
		}
		else if((result>0.6)&&(result<=1.2))
		{
		GPIO_PORTD_DATA_R &= 0x00;	
		GPIO_PORTD_DATA_R = 0x1F;
		}
		else if((result>1.2)&&(result<=2.2))
		{
			GPIO_PORTD_DATA_R &= 0x00;
		GPIO_PORTD_DATA_R = 0x2F;
		}
		else
		{
			GPIO_PORTD_DATA_R &= 0x00;
			GPIO_PORTD_DATA_R = 0xFF;
		}
		
		

//End of the code...
}
}