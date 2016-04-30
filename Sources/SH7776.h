/*
 * SH7776.h
 *
 *  Created on: 31.03.2016
 *      Author: Cornel Emmenegger
 */

#ifndef SOURCES_SH7776_H_
#define SOURCES_SH7776_H_


#include <stdint.h>

enum SH_regAddr {

	SYSTEM_CONTROL						= 0x40,	// control the software reset and the interrupt function
	MODE_CONTROL						= 0x41,	// control of PS and ALS operating modes and time settings
	ALS_PS_CONTROL						= 0x42,	// ALS and PS control of set the PS output mode, the ALS gain and the LED current
	INTERRUPT_CONTROL_PERSISTENCE 		= 0x43,
	PS_DATA_LSBs						= 0x44,	// PS data low byte
	PS_DATA_MSBs 						= 0x45,	// PS data high byte
	ALS_VIS_DATA_LSBs  					= 0x46,	// ALS VIS data low byte
	ALS_VIS_DATA_MSBs 					= 0x47,	// ALS VIS data high byte
	ALS_IR_DATA_LSBs 					= 0x48,	// ALS IR data low byte
	ALS_IR_DATA_MSBs 					= 0x49,	// ALS IR data high byte
	INTERRUPT_FUNCTION_SETTING			= 0x4A,

	PS_TH_LSBs 							= 0x4B, // PS threshold „HIGH“ low byte
	PS_TH_MSBs 							= 0x4C,	// PS threshold „HIGH“ high byte
	PS_TL_LSBs 							= 0x4D,	// PS threshold threshold „LOW“ low byte
	PS_TL_MSBs 							= 0x4E,	// PS threshold threshold „LOW“ high byte

	ALS_VIS_TH_LSBs 					= 0x4F,	// ALS VIS threshold „HIGH“ low byte
	ALS_VIS_TH_MSBs 					= 0x50,	// ALS VIS threshold „HIGH“ high byte
	ALS_VIS_TL_LSBs 					= 0x51,	// ALS VIS threshold „LOW“ low byte
	ALS_VIS_TL_MSBs 					= 0x52,	// ALS VIS threshold „LOW“ high byte
};



uint8_t SH_Init(void);
uint8_t SH_ReadProximity(uint16_t *ProxiP);

#endif /* SOURCES_SH7776_H_ */
