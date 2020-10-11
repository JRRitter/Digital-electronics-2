/* Defines -----------------------------------------------------------*/
#define PBTN		PD0		// AVR pin where pushbutton is connected
#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"           // GPIO library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle five LEDs 
 * Knight rider style when a pushbutton is pressed. Application is
 * using functions from GPIO library for configuring, writing 
 * and reading pins.
 */
int main(void)
{
	
    /* push button */
    GPIO_config_input_pullup(&DDRD, PBTN);
	
	/* Knight rider LEDs */
	
	for (uint8_t i = 0; i < 5; i++)
	{
		GPIO_config_output(&DDRC, i);
		GPIO_write_high(&PORTC, i);
	}


    // Infinite loop
    while (1)
    {
		// Knight rider sequence using GPIO library
		if (GPIO_read(&PIND, PBTN) == 0)
		{
			// up sequence
			GPIO_write_low(&PORTC, 0);	// ON
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 1);	// ON
			GPIO_write_high(&PORTC, 0);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 2);	// ON
			GPIO_write_high(&PORTC, 1);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 3);	// ON
			GPIO_write_high(&PORTC, 2);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 4);	// ON
			GPIO_write_high(&PORTC, 3);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 3);	// ON
			GPIO_write_high(&PORTC, 4);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 2);	// ON
			GPIO_write_high(&PORTC, 3);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 1);	// ON
			GPIO_write_high(&PORTC, 2);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_low(&PORTC, 0);	// ON
			GPIO_write_high(&PORTC, 1);	// OFF
			
			_delay_ms(BLINK_DELAY);
			GPIO_write_high(&PORTC, 0);	// OFF
				
		}
		
    }

    // Will never reach this
    return 0;
}
