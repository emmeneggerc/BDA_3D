/*
 * FDC1004.h
 *
 *  Created on: 20.04.2016
 *      Author: Cornel Emmenegger
 */

#ifndef SOURCES_FDC1004_H_
#define SOURCES_FDC1004_H_

#include <stdint.h>
#include "Detection.h"

uint8_t FDC_Init(void);
uint8_t FDC_ReadMeasurmentResults(int32_t *result);
uint8_t FDC_ReadRawValues(struct cap_val *data);
float FDC_Calc_Fixpoint(uint16_t val);

enum FDC_regAddr {

	MEAS1_MSB						= 0x00,
	MEAS1_LSB						= 0x01,
	MEAS2_MSB						= 0x02,
	MEAS2_LSB 						= 0x03,
	MEAS3_MSB						= 0x04,
	MEAS3_LSB 						= 0x05,
	MEAS4_MSB  						= 0x06,
	MEAS4_LSB 						= 0x07,
	CONF_MEAS1 						= 0x08,
	CONF_MEAS2 						= 0x09,
	CONF_MEAS3						= 0x0A,
	CONF_MEAS4 						= 0x0B,
	FDC_CONF 						= 0x0C,
	OFFSET_CAL_CIN1 				= 0x0D,
	OFFSET_CAL_CIN2					= 0x0E,
	OFFSET_CAL_CIN3 				= 0x0F,
	OFFSET_CAL_CIN4 				= 0x10,
	GAIN_CAL_CIN1 					= 0x11,
	GAIN_CAL_CIN2	 				= 0x12,
	GAIN_CAL_CIN3 					= 0x13,
	GAIN_CAL_CIN4 					= 0x14,

};

// registers from 0x15 to 0xFD are reserved and should not be written to





#endif /* SOURCES_FDC1004_H_ */
