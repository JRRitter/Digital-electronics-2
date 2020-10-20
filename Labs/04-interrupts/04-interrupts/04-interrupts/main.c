/***********************************************************************
 * 
 * Control LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_D1  PB5
#define LED_D2  PB4
#define LED_D3  PB3
#define LED_D4  PB2

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

/* Global variables --------------------------------------------------*/
extern volatile int8_t state = 0;
extern volatile int8_t step = 1;

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle three LEDs
 * on Multi-function shield with internal 8- and 16-bit timer modules.
 */
int main(void)
{
    /* Configuration of 4 LEDs */
    GPIO_config_output(&DDRB, LED_D1);
    GPIO_write_high(&PORTB, LED_D1);
	
	GPIO_config_output(&DDRB, LED_D2);
	GPIO_write_high(&PORTB, LED_D2);
	
	GPIO_config_output(&DDRB, LED_D3);
	GPIO_write_high(&PORTB, LED_D3);
	
	GPIO_config_output(&DDRB, LED_D4);
	GPIO_write_high(&PORTB, LED_D4);
    

    /* Configuration of 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
    TIM1_overflow_262ms();
    TIM1_overflow_interrupt_enable();

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
 * ISR starts when Timer/Counter1 overflows. Toggle LED D2 on 
 * Multi-function shield. */
ISR(TIMER1_OVF_vect)
{	
    switch(state){
		case 0:
			GPIO_write_high(&PORTB, LED_D3);
			GPIO_write_low(&PORTB, LED_D4);
			break;
		case 1:
			GPIO_write_high(&PORTB, LED_D4);
			GPIO_write_high(&PORTB, LED_D2);
			GPIO_write_low(&PORTB, LED_D3);
			break;
		case 2:
			GPIO_write_high(&PORTB, LED_D3);
			GPIO_write_high(&PORTB, LED_D1);
			GPIO_write_low(&PORTB, LED_D2);
			break;
		case 3:
			GPIO_write_high(&PORTB, LED_D2);
			GPIO_write_low(&PORTB, LED_D1);
			break;
		default:
			GPIO_write_low(&PORTB, LED_D1);
			GPIO_write_low(&PORTB, LED_D2);
			GPIO_write_low(&PORTB, LED_D3);
			GPIO_write_low(&PORTB, LED_D4);
			break;
	}
	
	if (state == 0)
	{
		step = 1;
	}
	else if (state == 3)
	{
		step = -1;
	}
	
	state += step;
}


