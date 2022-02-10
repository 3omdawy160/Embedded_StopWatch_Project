/*
 * StopWatch.h
 *  Created on: Feb 10, 2022
 *  Author:Mohamed Emad El-Dien Mahmoud
 *  Version:1
 */

#include "StopWatch.h"


int main()
{
	PINS_Init();    // Initializing our pins
	SREG |= (1<<7); // Enabling the global interrupt (I-bit)


	INT0_Init();    // Initializing INT0
	INT1_Init();    // Initializing INT1
	INT2_Init();    // Initializing INT2

	Timer1_CTC_Init(7200); // Calling our Timer to start counting

	for(;;)
	{
		/* Here we are going to use the round robin algorithm to keep showing the stop watch at all time */

		PORTA = (1<<PA0);
		PORTC = (PORTC & 0xF0) | (g_second1 & 0x0F);
		_delay_ms(3);


		PORTA = (1<<PA1);
		PORTC = (PORTC & 0xF0) | (g_second2 & 0x0F);
		_delay_ms(3);


		PORTA = (1<<PA2);
		PORTC = (PORTC & 0xF0) | (g_minute1 & 0x0F);
		_delay_ms(3);


		PORTA = (1<<PA3);
		PORTC = (PORTC & 0xF0) | (g_minute2 & 0x0F);
		_delay_ms(3);


		PORTA = (1<<PA4);
		PORTC = (PORTC & 0xF0) | (g_hour1 & 0x0F);
		_delay_ms(3);


		PORTA = (1<<PA5);
		PORTC = (PORTC & 0xF0) | (g_hour2 & 0x0F);
		_delay_ms(3);
	}
}
