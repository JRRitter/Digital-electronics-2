/*
 * wave.h
 *
 * Created: 15.12.2020 10:02:43
 *  Author: johnr
 */ 

/**
 * @mainpage
 * Project creating a signal generator using an 8-bit R2R ladder as DAC.
 * @author John Richard Ritter
 * 
 *
 *  @file
 *  @defgroup KM_wave Signal library <wave.h>
 *  @code #include <wave.h> @endcode
 *
 *  @brief	Calculate values of one of three useful signals.
 *	This library is able to calculate the numerical output values (8-bit unsigned integers)
 *  given the frequency and signal type. Its calculating function has to be continually called
 *  in order for it to function
 *
 *
 *  @author John Richard Ritter
 */

#ifndef WAVE_H_
#define WAVE_H_

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
//#include "wave_LUT.h"



/* Functions ---------------------------------------------------------*/
/* Functions ---------------------------------------------------------*/
/**@{*/

	/*
	** function prototypes
	*/
/** @brief  Initializing values further used for computing.
 *  @param[in]  type_signal takes the signal type (1 for sine, 2 for triangle, 3 for square)
 *  @param[in]  freq_signal takes the signal frequency (15 - 1000 Hz)
 *  @return	none
 */
void wave_init(uint8_t type_signal, uint16_t freq_signal);
/** @brief  Calculates the next value of the given signal.
 *  @param[in]  none
 *  @return	8-bit value signal output
 */
uint8_t wave_calculate(void);
/** @brief  resets all calculations.
 */
void wave_reset(void);
/** @brief  Calculates the next value of sine. Used in wave_calculate()
 *  @param[in]  none
 *  @return	8-bit value signal output
 */
uint8_t wave_calc_sine(void);
/** @brief  Calculates the next value of triangle. Used in wave_calculate()
 *  @param[in]  none
 *  @return	8-bit value signal output
 */
uint8_t wave_calc_triangle(void);
/** @brief  Calculates the next value of square. Used in wave_calculate()
 *  @param[in]  none
 *  @return	8-bit value signal output
 */
uint8_t wave_calc_square(void);
void walk(void);




#endif /* WAVE_H_ */