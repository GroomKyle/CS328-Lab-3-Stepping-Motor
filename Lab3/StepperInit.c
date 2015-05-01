/* Kyle Groom
 * CS238
 * 1/30/2015
 * Stepping motor with lights
 */

#include "tm4c123gh6pm.h"
#include "systick.h"
#include <stdint.h>
   
int data[4] = {10, 6, 5, 9};
int color[4] =  {0x02, 0x04, 0x06, 0x08};
#define STEPPER  (*((volatile unsigned long *)0x4000703C))

//Initialize the Stepping motor
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
	// Enable the GPIO port that is used for the on-board LED.
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
	
	Stepper_Init();
	
	while(1)
	{	
		//clockwise
		for(c = 0; c < 4; c++)
		{
				//Enable the GPIO pin for the LED
				GPIO_PORTF_DIR_R = color[c];
				
				//Set the direction as output, and enable the GPIO pin for digital function.
				GPIO_PORTF_DEN_R = color[c];
				
				//Turn on the LED
				GPIO_PORTF_DATA_R |= color[c];
				
				//Change the stepper Pin Value
				GPIO_PORTD_DATA_R = data[c];
				
				//Wait To Advance
				SysTick_Wait(100000);
				
				//Turn Off The LED
				GPIO_PORTF_DATA_R &= ~(GPIO_PORTF_DATA_R);
		}
	}
	
	while(1)
	{	
		//counter clockwise
		for(c = 0; c < 4; c++)
		{
				//Enable the GPIO pin for the LED
				GPIO_PORTF_DIR_R = color[c];
				
				//Set the direction as output, and enable the GPIO pin for digital function.
				GPIO_PORTF_DEN_R = color[c];
				
				//Turn on the LED
				GPIO_PORTF_DATA_R |= color[c];
			
				//Change the stepper Pin Value
				GPIO_PORTD_DATA_R = ~(data[c]);
			
				//Wait To Advance
				SysTick_Wait(100000);
			
				//Turn Off The LED
				GPIO_PORTF_DATA_R &= ~(GPIO_PORTF_DATA_R);
		}
	}

}
