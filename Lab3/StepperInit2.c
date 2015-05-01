/* Kyle Groom
 * CS238
 * 1/30/2015
 * Stepping motor without lights
 */

#include "tm4c123gh6pm.h"
#include "systick.h"
#include <stdint.h>
   
int data[4] = {10, 6, 5, 9};
#define STEPPER  (*((volatile unsigned long *)0x4000703C))

///Initialize stepping motor
void Stepper_Init(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; //activate port D
  SysTick_Init();
	GPIO_PORTD_AFSEL_R &= ~0x0F;
	GPIO_PORTD_AMSEL_R &= ~0x0F;
	GPIO_PORTD_PCTL_R &= ~0x0000FFFF;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;
	GPIO_PORTD_DR8R_R |= 0x0F;
}

int c;

int main(void)
{
	Stepper_Init();
	
	while(1)
	{
		//clockwise
		for(c = 0; c < 4; c++)
		{
				//Change the stepper Pin Value
				GPIO_PORTD_DATA_R = data[c];
			
				//wait to advance
				SysTick_Wait(100000);
		}
	}
	
	while(1)
	{
		//counter clockwise
		for(c = 0; c < 4; c++)
		{
				//Change the stepper Pin Value
				GPIO_PORTD_DATA_R = ~(data[c]);
				
				//wait to advance
				SysTick_Wait(100000);
		}
	}

}
