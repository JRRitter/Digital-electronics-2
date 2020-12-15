/*************************************************************************
 * Title	:   C include file for the keypad (4x3) library (kpd.c)
 * Author:    John Richard Ritter
 * Software:  AVR-GCC 4.x
 * Hardware:  ATmega328P
 ***************************************************************************/

/**
 * @mainpage
 * Project creating a signal generator using an 8-bit R2R ladder as DAC.
 * @author John Richard Ritter
 * 
 *
 *  @file
 *  @defgroup KM_kpd Keypad library <kpd.h>
 *  @code #include <kpd.h> @endcode
 *
 *  @brief	Scan keypad for pressed buttons.
 *
 *	This library scans a 4x3 keypad for any pressed buttons.
 *
 *
 *  @author John Richard Ritter
 */

#ifndef KPD_H
#define KPD_H

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "kpd_definitions.h"

/* Functions ---------------------------------------------------------*/
/**@{*/

	/*
	** function prototypes
	*/
/** @brief  Initializing pins specified in kpd_definitions.h
 *  @param  The definitions in kpd_definitions.h are used
 *  @return	none
 */
void kpd_init(void);


/** @brief  Initializing pins specified in kpd_definitions.h
 *  @param  None
 *  @return	Numerical value of pressed button. Returns 10 for * and 11 for #. Returns 255 if no or multiple buttons are pressed.
 */
uint8_t kpd_scan(void);
/**@}*/
#endif /* KPD_H */