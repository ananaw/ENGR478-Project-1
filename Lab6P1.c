//*****************************************************************************
// Copyright (c) 2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This file was automatically generated by the Tiva C Series PinMux Utility
// Version: 1.0.4
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "Lab6P1.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h" 

//*****************************************************************************
void
PortFunctionInit(void)
{
    // Enable Peripheral Clocks 
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable pin PF0 for GPIOInput (SW2)
    //

    //
    //First open the lock and select the bits we want to modify in the GPIO commit register.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

    //
    //Now modify the configuration of the pins that we unlocked. (SW2)
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

    //
    // Enable pin PF4 for GPIOInput (SW1)
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
		
		//
    // Enable pin PF3 for GPIOOutput (Green, 0x08)
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
		
    //
    // Enable pin PF1 for GPIOOutput (Red, 0x02)
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
		
		// Enable internal pull-up for PF0 (SW2), manually added by programmer
		GPIO_PORTF_PUR_R |= 0x01;
		
		// Enable internal pull-up for PF4 (SW1)
		GPIO_PORTF_PUR_R |= 0x10;
}

// Manually added code
int main(void)
{
	// Initiatialize GPIO ports.
	PortFunctionInit();
	uint8_t LED_data; 						// create 8 bit unsigned integer type variable.
	
	// Set clock rate to 400M/2/5 = 40MHz. (or 25MHz, divide by 8)
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //
	//float clock = SysCtlClockGet(); 
	
	// Turn on red and green LED. 
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
	
	//
	// Loop forever
	//
	while(1)
	{
		// if SW1 is pressed.
		if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0x00) 
		{
			if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0x00) 
			{
			// clear red LED
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
				
			// clear green LED			
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);			
			}
			
			else
			{
			// clear green LED			
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
			
			// Toggle red LED. 
			LED_data ^= 0x02;
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LED_data);
				
			// Delay for 0.5 sec. ((25M*0.5)-2)/3 + 1 = 4166667.
			SysCtlDelay(6666667);
			}
		}
		
		// if SW2 is pressed, turn off both LEDs.
		else if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0x00) 
		{
			// clear red LED
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);	
			
			// clear green LED			
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);			
		}
		
		else
		{
			// clear red LED
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);	
			
			// toggle green LED
			LED_data ^= 0x08;
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, LED_data);
			
			// Delay for 0.5 sec. 
			SysCtlDelay(6666667);
		}
	}
}
				
				
			
		
