/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define LED_RED     PC0
#define PUSHBTN  PD0			
#define BLINK_DELAY 250
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
	/* ORIGINAL VERSION
    // GREEN LED 
    // Set pin as output in Data Direction Register...
    DDRB = DDRB | (1<<LED_GREEN);
    // ...and turn LED off in Data Register
    PORTB = PORTB & ~(1<<LED_GREEN);

    // second LED
    // Setting pin PC0 to output
	DDRC = DDRC | (1<<LED_RED);
	// ...turning  on the led (high output)
	PORTC = PORTC & ~(1<<LED_RED);
	*/
	
	/* pushbutton */
	// Setting pin PD0 to input
	DDRD = DDRD & ~(1<<PUSHBTN);
	// ...and enabling internal pull-up resistor
	PORTD = PORTD | (1<<PUSHBTN);
	
	//Setting pins to output
	DDRC = DDRC | 31; // 0001 1111
	//Turning off LEDs (active low)
	PORTC = PORTC | 31;// 0001 1111
	
	
    // Infinite loop
    while (1)
    {
        /* ORIGINAL VERSION
		
		// Pause several milliseconds
        _delay_ms(BLINK_DELAY);
		if (bit_is_clear(PIND, PUSHBTN)) 
		{
			// inverting LED ports in registers
			PORTB = PORTB ^ (1<<LED_GREEN);
			PORTC = PORTC ^ (1<<LED_RED);
		}
        */
		
		
		// Knight Rider application
		while (bit_is_clear(PIND,PUSHBTN))
		{
			for (int i = 0; i < 5; i++)
			{
				_delay_ms(BLINK_DELAY);
				PORTC = ~(1<<i); // setting only one led on
			}
			for (int i = 0; i < 5; i++)
			{
				_delay_ms(BLINK_DELAY);
				PORTC = ~(16>>i); // setting only one led on
			}
			_delay_ms(BLINK_DELAY);
			PORTC = PORTC | 31;// turning off leds
			
		}
		
		
    }

    // Will never reach this
    return 0;
}

