/***********************************************************************
 * 
 * GPIO library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif
#include "kpd.h"


/* Macros -------------------------------------------------------------*/
#define DDR(x) (*(&x - 1)) ///< address of data direction register of port x 
#define PIN(x) (*(&x - 2)) ///< address of input register of port x          


/* Function definitions ----------------------------------------------*/

/**
 * Configures the defined row pins as inputs with pull-up resistors
 * and the column ports as outputs and sets them to high.
 * 
 */	

void kpd_init(void){
	// Set row pins to inputs with pull-up resistors
	// DDR = 0; PORT = 1;
	DDR(KPD_ROW_PORT) &= ~(1 << KPD_ROW_1);
	DDR(KPD_ROW_PORT) &= ~(1 << KPD_ROW_2);
	DDR(KPD_ROW_PORT) &= ~(1 << KPD_ROW_3);
	DDR(KPD_ROW_PORT) &= ~(1 << KPD_ROW_4);
	KPD_ROW_PORT      |=  (1 << KPD_ROW_1);
	KPD_ROW_PORT      |=  (1 << KPD_ROW_2);
	KPD_ROW_PORT      |=  (1 << KPD_ROW_3);
	KPD_ROW_PORT      |=  (1 << KPD_ROW_4);
	
	// Set column pins to outputs with default value HIGH
	// DDR = 1; PORT = 1;
	DDR(KPD_COL_PORT) |=  (1 << KPD_COL_1);
	DDR(KPD_COL_PORT) |=  (1 << KPD_COL_2);
	DDR(KPD_COL_PORT) |=  (1 << KPD_COL_3);
	KPD_COL_PORT	  |=  (1 << KPD_COL_1);
	KPD_COL_PORT	  |=  (1 << KPD_COL_2);
	KPD_COL_PORT	  |=  (1 << KPD_COL_3);
} // end kpd_init();
/**
 * Configures the defined row pins as inputs with pull-up resistors
 * and the column ports as outputs and sets them to high.
 * 
 * @param[out] numerical value of pressed button (10 is *, 11 is #)
 */	
uint8_t kpd_scan(void){
	uint8_t key_pressed = 255;
	
	// Set KPD_COL_1 low and detect if a ROW is low
	KPD_COL_PORT	  &=  ~(1 << KPD_COL_1);
	
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_1)){ // pressed 1
		if (key_pressed == 255){
			key_pressed = 1; 
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_2)){ // pressed 4
		if (key_pressed == 255){
			key_pressed = 4;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_3)){ // pressed 7
		if (key_pressed == 255){
			key_pressed = 7;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_4)){ // pressed *
		if (key_pressed == 255){
			key_pressed = 10;
		} else return 255;							// more buttons are pressed
	}
	KPD_COL_PORT	  |=   (1 << KPD_COL_1);
	
	// Set KPD_COL_2 low and detect if a ROW is low
	KPD_COL_PORT	  &=  ~(1 << KPD_COL_2);
	
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_1)){ // pressed 2
		if (key_pressed == 255){
			key_pressed = 2;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_2)){ // pressed 5
		if (key_pressed == 255){
			key_pressed = 5;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_3)){ // pressed 8
		if (key_pressed == 255){
			key_pressed = 8;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_4)){ // pressed 0
		if (key_pressed == 255){
			key_pressed = 0;
		} else return 255;							// more buttons are pressed
	}
	KPD_COL_PORT	  |=   (1 << KPD_COL_2);
	
	// Set KPD_COL_3 low and detect if a ROW is low
	KPD_COL_PORT	  &=  ~(1 << KPD_COL_3);
	
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_1)){ // pressed 3
		if (key_pressed == 255){
			key_pressed = 3;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_2)){ // pressed 6
		if (key_pressed == 255){
			key_pressed = 6;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_3)){ // pressed 9
		if (key_pressed == 255){
			key_pressed = 9;
		} else return 255;							// more buttons are pressed
	}
	if(bit_is_clear(PIN(KPD_ROW_PORT),KPD_ROW_4)){ // pressed #
		if (key_pressed == 255){
			key_pressed = 11;
		} else return 255;							// more buttons are pressed
	}
	KPD_COL_PORT	  |=   (1 << KPD_COL_3);
	
	return key_pressed;
} // end kpd_scan();