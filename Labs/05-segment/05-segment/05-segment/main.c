/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC


/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */

uint8_t value0 = 0;
uint8_t value1 = 0;
uint8_t value2 = 0;
uint8_t value3 = 0;


int main(void)
{
    // Configure SSD signals
    SEG_init();

    /* Configure 16-bit Timer/Counter1
     * Set pre scaler and enable overflow interrupt */
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();
	
	/* Configure 8-bit Timer/Counter0
     * Set pre scaler and enable overflow interrupt */
	TIM0_overflow_1ms();
	TIM0_overflow_interrupt_enable();
	
    // Enables interrupts by setting the global interrupt mask
	sei();
	
    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter1 overflows. 
 * Controls snake behavior.
 */
ISR(TIMER1_OVF_vect)
{
	if ((value0 == 9) && (value1 == 5) && (value2 == 9) && (value3 == 5))
	{
		value0 = 0;
		value1 = 0;
		value2 = 0;
		value3 = 0;
	}
	else if ((value0 == 9) && (value1 == 5) && (value2 == 9))
	{
		value0 = 0;
		value1 = 0;
		value2 = 0;
		value3++;
	}
	else if ((value0 == 9) && (value1 == 5))
	{
		value0 = 0;
		value1 = 0;
		value2++;
	}
	else if ((value0 == 9))
	{
		value0 = 0;
		value1++;
	}
	else
	{
		value0++;
	}
	
	/*
	static uint8_t step = 0;
	switch (step){
		case 0:
			value0 = 10;
			value1 = 10;
			value2 = 10;
			value3 = 11;
			break;
		case 1:
			value0 = 10;
			value1 = 10;
			value2 = 11;
			value3 = 11;
			break;
		case 2:
			value0 = 10;
			value1 = 11;
			value2 = 11;
			value3 = 11;
			break;
		case 3:
			value0 = 11;
			value1 = 11;
			value2 = 11;
			value3 = 11;
			break;
		case 4:
			value0 = 12;
			value1 = 11;
			value2 = 11;
			value3 = 10;
			break;
		case 5:
			value0 = 13;
			value1 = 11;
			value2 = 10;
			value3 = 10;
			break;
		case 6:
			value0 = 14;
			value1 = 10;
			value2 = 10;
			value3 = 10;
			break;
		case 7:
			value0 = 15;
			value1 = 17;
			value2 = 10;
			value3 = 10;
			break;
		case 8:
			value0 = 16;
			value1 = 17;
			value2 = 17;
			value3 = 10;
			break;
		case 9:
			value0 = 17;
			value1 = 17;
			value2 = 17;
			value3 = 17;
			break;
		case 10:
			value0 = 10;
			value1 = 17;
			value2 = 17;
			value3 = 18;
			break;
		case 11:
			value0 = 10;
			value1 = 10;
			value2 = 17;
			value3 = 19;
			break;
		case 12:
			value0 = 10;
			value1 = 10;
			value2 = 10;
			value3 = 20;
			break;
		case 13:
			value0 = 10;
			value1 = 10;
			value2 = 11;
			value3 = 21;
			break;
		case 14:
			value0 = 10;
			value1 = 11;
			value2 = 11;
			value3 = 22;
			break;
	}
	
	if (step == 14)
	{
		step = 3;
	}
	else step++;
	*/
}


/**
 * ISR starts when Timer/Counter0 overflows. 
 * Control communication with 7-segment display.
 */
ISR(TIMER0_OVF_vect)
{
	static uint8_t pos = 0;
	switch (pos){
		case 0:
			SEG_update_shift_regs(value0, pos);
			break;
		case 1:
			SEG_update_shift_regs(value1, pos);
			break;
		case 2:
			SEG_update_shift_regs(value2, pos);
			break;
		case 3:
			SEG_update_shift_regs(value3, pos);
			break;
	}
	
	if (pos == 3)
	{
		pos = 0;
	}
	else pos++;
	
}
