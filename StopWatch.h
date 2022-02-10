/*
 * StopWatch.h
 *  Created on: Feb 10, 2022
 *  Author:Mohamed Emad El-Dien Mahmoud
 *  Version:1
 */

#ifndef LAB1_H_
#define LAB1_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void PINS_Init();
void INT0_Init();
void INT1_Init();
void INT2_Init();
void Timer1_CTC_Init(int ticks);
ISR(TIMER1_COMPA_vect);
ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);


extern char g_second1;
extern char g_second2;
extern char g_minute1;
extern char g_minute2;
extern char g_hour1;
extern char g_hour2;


#endif /* LAB1_H_ */
