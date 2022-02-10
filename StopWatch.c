/*
 * StopWatch.c
 *  Created on: Feb 10, 2022
 *  Author:Mohamed Emad El-Dien Mahmoud
 *  Version:1
 */

#include "StopWatch.h"

char g_second1=0;
char g_second2=0;
char g_minute1=0;
char g_minute2=0;
char g_hour1=0;
char g_hour2=0;

void PINS_Init()
{
	// Enabling PortA and PortC pins

	DDRC |= 0x0F;  // Making the first 4 pins in PORTC output pins
	DDRA |= 0x3F;  // Making the first 6 pins in PORTA output pins

	PORTC &= ~0x0F; // Initializing the OUTPUT of First 4 PINS in PORTC with 0
	PORTA &= ~0x3F; // Initializing the OUTPUT of First 6 PINS in PORTA with 0
}


void INT0_Init()
{
	// Enabling INT0

	GICR |= (1<<INT0);
	MCUCR |= (1<<ISC01); //Generate Interrupt with falling edge
	MCUCR &= ~(1<<ISC00);
	DDRD &= ~(1<<PD2); // Configure pin 2 in PORTD as input pin
	PORTD |= (1<<PD2); // Activate the internal pull up resistor at PD2
}


void INT1_Init()
{
	// Enabling INT1

	GICR |= (1<<INT1);
	MCUCR |= (1<<ISC10) | (1<<ISC11); //Generate Interrupt with rising edge
	DDRD &= ~(1<<PD3); // Configure pin 3 in PORTD as input pin
}


void INT2_Init()
{
	// Enabling INT2

	GICR |= (1<<INT2);
	MCUCSR &= ~(1<<ISC2); //Generate Interrupt with falling edge
	DDRB &= ~(1<<PB2); // Configure pin 2 in PORTB as input pin
	PORTB |= (1<<PB2); // Activating the internal pull up resistor at PB2
}

void Timer1_CTC_Init(int ticks)
{
	// Enable Timer1 at CTC mode with a Pre scaler = 64
	// The timer will give an interrupt every one second

	TCNT1 = 0;
	OCR1A = ticks;
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
	TIMSK |= (1<<OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
	g_second1++; // Always incrementing our seconds counter every one second

	if(g_second1==10)
	{
		g_second1=0;
		g_second2++;
	}
	if(g_second2==6)
	{
		g_second2=0;
		g_minute1++;
	}
	if(g_minute1==10)
	{
		g_minute1=0;
		g_minute2++;
	}
	if(g_minute2==6)
	{
		g_minute2=0;
		g_hour1=0;
	}
	if(g_hour1==10)
	{
		g_hour1=0;
		g_hour2++;
	}
}


ISR(INT0_vect)
{
	// Reseting all the counters to start from the begining

	g_second1=0;
	g_second2=0;
	g_minute1=0;
	g_minute2=0;
	g_hour1=0;
	g_hour2=0;
}


ISR(INT1_vect)
{
	// Disabling the clock therefore there will be no timer counting

	TCCR1B &= ~(1<<CS10) & ~(1<<CS12);
}


ISR(INT2_vect)
{
	// Enabling the clock again to make the timer count again

	TCCR1B |= (1<<CS10) | (1<<CS12);
}
