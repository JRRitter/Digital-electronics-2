/************************************************************************
 * 
 * Project
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) Ritter, John Richard
 * 
 **********************************************************************/

/**
 * @mainpage
 * Project creating a signal generator using an 8-bit R2R ladder as DAC.
 * @author John Richard Ritter
 * 
 *
 *  @file
 *  @defgroup KM_main Program file <main.c>
 * 
 *
 *  @brief	Generating analog signal through a 8-bit R2R ladder with keyboard control and LCD display.
 *
 *	This program immitates a signal generator. It is able to create 3 different waveforms. The whole program is controlled by a 4x3 keyboard
 *  and an LCD display is used. Useful information is sent to a remote device via uart. LCD and uart control are managed with libraries 
 *  created by PEter Fleury. 
 

 *  @author John Richard Ritter
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include "kpd.h"
#include "uart.h"
#include "wave.h"
#include <stdlib.h>         // C library. Needed for conversion function

#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif

/* Variables ---------------------------------------------------------*/
volatile uint8_t gen_type = 255;
volatile uint16_t gen_frequency = 0;
volatile uint8_t gen_out_on = 0;
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
	
	lcd_gotoxy(0,0);
	lcd_puts("SIGNAL GENERATOR");
	lcd_gotoxy(0,1);
	lcd_puts("Press # to start");
	
	// Initialize keypad
	kpd_init();
	
	// Configure 8-bit Timer/Counter2 for project
	// Set pre scaler and enable overflow interrupt every 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	
	// Configure 16-bit Timer/Counter1 for project
	// Set to CTC mode with frequency of interrupts 100 kHz
	TCCR1B |= ((1<<WGM12) | (1<<CS11));
	TCCR1B &= ~((1<<WGM13) | (1<<CS12) | (1<<CS10));
	TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
	TIMSK1 |= (1<<OCIE1A);
	OCR1AH = 0b00000001; OCR1AL = 0;
	
	// Set portB to output
	DDRB = 0b11111111;
	
	// Initialize UART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	
	// Enables interrupts by setting the global interrupt mask
	sei();
	
    while (1) 
    {
		/* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }
	
	// Will never reach this
	return 0;
}

/* Interrupt service routines ----------------------------------------*/
ISR(TIMER1_COMPA_vect)  // keypad, display, uart, program logic
{
	if (gen_out_on==1)
	{
		PORTB = wave_calculate();
	}
	else
	{
		PORTB = 0b00000000;
		wave_reset();
	}
}


ISR(TIMER2_OVF_vect)  // keypad, display, uart, program logic
{
	// Variables definition
		// for KEY DETECTION
	static uint8_t key_history[] = {255,255,255};
	static uint8_t key_num_overflow = 0;
	static uint8_t key_hold = 0;
	uint8_t key_pressed = 255;
		// for LCD
	char lcd_string[4] = "    ";
		// for MENU NAVIGATION
	static uint8_t menu_selection_on = 0;
	static uint8_t menu_selection_phase = 0;
	static uint8_t menu_program_started = 0;
	static uint8_t menu_freq_select[] = {0,0,0,0};
	
	// KEY DETECTION ------------------------------------------   
	// detecting pressed key with implemented de-bouncing
	if (key_num_overflow < 2) 
	{
		key_num_overflow++;
	}
	else // every 3*16 ms = 48 ms
	{
		key_num_overflow = 0;
		key_history[2] = key_history[1];
		key_history[1] = key_history[0];
		key_history[0] = kpd_scan();
	}
	
	if(key_history[0]==key_history[1] && key_history[1]==key_history[2] && key_history[0] != 255 && key_hold == 0) // key pressed
	{
		key_hold = 1; // indicates a key is being held
	}
	else if (key_history[0]!=key_history[1] && key_history[1]==key_history[2] && key_history[2] != 255 && key_hold == 1) // key released
	{
		key_hold = 0;					// the key has been released
		key_pressed = key_history[1];	// key_pressed is then further used in menu navigation
		for (uint8_t i = 0; i < 3; i++) // reset history
		{
			key_history[i] = 255;
		}
		
	}
	
	// MENU NAVIGATION ------------------------------------
	if (menu_program_started == 1)
	{
		if (menu_selection_on == 0)
		{
			if (key_pressed == 10)
			{
				if (gen_out_on == 0)
				{
					gen_out_on = 1;
					lcd_gotoxy(13,1);
					lcd_puts("ON ");
					uart_puts("Output: ON\r\n");
				}
				else
				{
					gen_out_on = 0;
					lcd_gotoxy(13,1);
					lcd_puts("OFF ");
					uart_puts("Output: OFF\r\n");
				}
			}
			if (key_pressed == 11)
			{
				menu_selection_on = 1;
				gen_out_on = 0;
				uart_puts("Output: OFF\r\n");
				uart_puts("Selecting:\r\n");
			}
		}
		else					// SELECTION MENU
		{
			switch(menu_selection_phase) {

				case 0:			// Waveform selection
					lcd_gotoxy(0,0);
					lcd_puts("SELECT:  1 SIN  ");
					lcd_gotoxy(0,1);
					lcd_puts("  2 TRI  3 SQR  ");
					switch(key_pressed){
						case 1:
							gen_type = 1;
							menu_selection_phase++;
							break;
						case 2:
							gen_type = 2;
							menu_selection_phase++;
							break;
						case 3:
							gen_type = 3;
							menu_selection_phase++;
							break;
					}
					break;
				
				case 1:			// select frequency - first digit
					lcd_gotoxy(0,0);
					lcd_puts("TYPE FREQUENCY  ");
					lcd_gotoxy(0,1);
					lcd_puts(" 15-1000 Hz     ");
					if (key_pressed < 10)
					{
						menu_freq_select[0] = key_pressed;
						menu_selection_phase++;
						lcd_gotoxy(0,1);
						lcd_puts("                ");
						lcd_gotoxy(6,1);
						lcd_puts("Hz");
						lcd_gotoxy(2,1);
						itoa(menu_freq_select[0],lcd_string,10);
						lcd_puts(lcd_string);
					}
					break; 
				
				case 2:
					if (key_pressed < 10)
					{
						menu_freq_select[1] = key_pressed;
						menu_selection_phase++;
						lcd_gotoxy(3,1);
						itoa(menu_freq_select[1],lcd_string,10);
						lcd_puts(lcd_string);
					}
					break;
				
				case 3:
					if (key_pressed < 10)
					{
						menu_freq_select[2] = key_pressed;
						menu_selection_phase++;
						lcd_gotoxy(4,1);
						itoa(menu_freq_select[2],lcd_string,10);
						lcd_puts(lcd_string);
					}
					break;
				
				case 4:			// select last digit
					if (key_pressed < 10)
					{
						menu_freq_select[3] = key_pressed;
						menu_selection_phase++;
						lcd_gotoxy(4,1);
						itoa(menu_freq_select[3],lcd_string,10);
						lcd_puts(lcd_string);
					}
					break;
				
				case 5:			// Confirm selection
					lcd_gotoxy(0,0);
					lcd_puts("CONFIRM    * NO ");
					lcd_gotoxy(0,1);
					switch(gen_type){
						case 1:
							lcd_puts("SIN");
							break;
						case 2:
							lcd_puts("TRI");
							break;
						case 3:
							lcd_puts("SQR");
							break;
					}
					lcd_puts(" ");
					if (menu_freq_select[0] == 0) 
					{
						lcd_puts(" ");
						if (menu_freq_select[1] == 0)
						{
							lcd_puts(" ");
							if (menu_freq_select[2] == 0)
							{
								lcd_puts(" ");
								itoa(menu_freq_select[3],lcd_string,10);
								lcd_puts(lcd_string);
							}
							else
							{
								for (uint8_t i=2; i < 4 ;i++)
								{
									itoa(menu_freq_select[i],lcd_string,10);
									lcd_puts(lcd_string);
								}
							}
						}
						else
						{
							for (uint8_t i=1; i < 4 ;i++)
							{
								itoa(menu_freq_select[i],lcd_string,10);
								lcd_puts(lcd_string);
							}
						}
					}
					else
					{
						for (uint8_t i=0; i < 4 ;i++)
						{
							itoa(menu_freq_select[i],lcd_string,10);
							lcd_puts(lcd_string);
						}
					}
					lcd_puts("Hz # YES");
					switch(key_pressed){
						case 10:
							menu_selection_phase = 0;
							break;
						case 11:
							menu_selection_on = 0;
							menu_selection_phase = 0;
							gen_frequency = 1000*menu_freq_select[0]+100*menu_freq_select[1]+10*menu_freq_select[2]+menu_freq_select[3];
							lcd_gotoxy(0,0);
							lcd_puts("                ");
							lcd_gotoxy(0,1);
							lcd_puts("                ");
							lcd_gotoxy(0,0);
							switch(gen_type){
								case 1:
								lcd_puts("SINE");
								uart_puts("SINE ");
								break;
								case 2:
								lcd_puts("TRIANGLE");
								uart_puts("TRIANGLE ");
								break;
								case 3:
								lcd_puts("SQUARE");
								uart_puts("SQUARE ");
								break;
							}
							lcd_gotoxy(0,1);
							itoa(gen_frequency,lcd_string,10);
							lcd_puts(lcd_string);
							lcd_puts(" Hz");
							uart_puts(lcd_string);
							uart_puts(" Hz\r\n");
							lcd_gotoxy(9,1);
							lcd_puts("OUT:OFF");
							uart_puts("Output: OFF\r\n");
							wave_init(gen_type,gen_frequency);
							break;
					}
					break;
			}
		}
	}
	else						// START WINDOW
	{	
		if (key_pressed == 11)
		{
			menu_program_started = 1;
			menu_selection_on = 1;
			lcd_gotoxy(0,0);
			lcd_puts("                ");
			lcd_gotoxy(0,1);
			lcd_puts("                ");
			uart_puts("Starting...\r\n");
		}
	}
}

