/*
 * SH7776.c
 *
 *  Created on: 31.03.2016
 *      Author: Cornel Emmenegger
 */

#include "SH7776.h"
#include "GI2C1.h"
#define SH7776_I2C_ADDRESS 0x39
static const uint8_t deviceI2CAddress = SH7776_I2C_ADDRESS;


uint8_t SH_WriteReg8(uint8_t reg, uint8_t val) {

	uint8_t res;

	res = GI2C1_WriteAddress(deviceI2CAddress, &reg, sizeof(reg), &val, sizeof(val));
	return res;
}

uint8_t SH_ReadReg8(uint8_t reg, uint8_t *valP) {

	uint8_t res;
	res = GI2C1_ReadAddress(deviceI2CAddress, &reg, 1, valP, 1);
	return res;

}

uint8_t SH_ReadProximity(uint16_t *ProxiP) {
	uint8_t res;
	uint8_t lsb;
	uint8_t msb;
	uint16_t extendlsb = 0;
	uint16_t extendmsb = 0;

	res = SH_ReadReg8(PS_DATA_LSBs, &lsb);
	if (res != ERR_OK) {
		return res;
	}

	res = SH_ReadReg8(PS_DATA_MSBs, &msb);
	if (res != ERR_OK) {
		return res;
	}

	extendlsb = lsb;
	extendmsb = msb;
	*ProxiP = lsb | (msb << 8);

	return res;
}

uint8_t SH_Init(void) {
	uint8_t res;

	res = SH_WriteReg8(MODE_CONTROL, 0x3F);	// set LED pulse current to 200mA and ALS gain to x128
	res = SH_WriteReg8(ALS_PS_CONTROL, 0x06 );// 0x03 set ALS to standby and PS with 100 ms repetition time

	return res;
}
