/*
 * wave.c
 *
 * Created: 15.12.2020 10:03:16
 *  Author: johnr
 */ 
#include <stdio.h>
#include "wave.h"
#include "wave_LUT.h"
/* Variables ---------------------------------------------------------*/
uint16_t wave_sample_freq = 7812/512;
volatile uint16_t wave_ind = 0;
volatile uint16_t wave_step = 0;
volatile uint16_t wave_rem = 0;
volatile uint16_t wave_rem_level = 0;
volatile uint8_t wave_type = 0;
volatile uint8_t wave_correction_on = 0;

void wave_init(uint8_t type_signal, uint16_t freq_signal);
uint8_t wave_calculate(void);
void wave_reset(void);
uint8_t wave_calc_sine(void);
uint8_t wave_calc_triangle(void);
uint8_t wave_calc_square(void);
void walk(void);
void walk_correction(void);


void wave_init(uint8_t type_signal, uint16_t freq_signal){
	wave_step = freq_signal/wave_sample_freq;
	wave_rem = freq_signal-wave_step*wave_sample_freq;
	wave_rem_level = wave_sample_freq;
	wave_type = type_signal;
}


uint8_t wave_calculate(void){
	uint8_t output = 0;
	walk_correction();
	walk();
	switch(wave_type){
		case 1:
			output = wave_calc_sine();
			break;
		case 2:
			output = wave_calc_triangle();
			break;
		case 3:
			output = wave_calc_square();
			break;
		default:
			output = 0b10000000;
			break;
	}
	return output;
}

void wave_reset(void){
	wave_ind = 0;
	wave_rem_level = wave_sample_freq;
	wave_correction_on = 0;
}


uint8_t wave_calc_sine(void){
 	uint8_t output = 0;
	output = wave_lut_sine[wave_ind];
 	return output;
}

uint8_t wave_calc_triangle(void){
	uint8_t output = 0;
	if (wave_ind<256)
	{
		output = wave_ind;
	}
	else 
	{
		output = 511-wave_ind;	
	}

	return output;
}

uint8_t wave_calc_square(void){
	uint8_t output = 0;
	if (wave_ind<256)
	{
		output = 0b11111111;
	}
	else output = 0b00000000;
	return output;
}


void walk(void){
	if (wave_correction_on==1)
	{
		wave_ind += wave_step+1;
		wave_correction_on = 0;
	}
	else wave_ind += wave_step;
	if(wave_ind > 511)
	{
		wave_ind -= 511;
	}
}


void walk_correction(void){
	if (wave_rem_level<wave_rem)
	{
		wave_rem_level = wave_sample_freq-wave_rem+wave_rem_level;
		wave_correction_on = 1;
	}
	else
	{
		wave_rem_level -=  wave_rem;
	}
}

