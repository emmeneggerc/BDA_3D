/*
 * FDC1004.c
 *
 *  Created on: 20.04.2016
 *      Author: Cornel Emmenegger
 */

#include "FDC1004.h"
#include "GI2C1.h"
#include "Application.h"
#include "FRTOS1.h"
#define FDC1004_I2C_ADDRESS 0x50  // b101 0000
static const uint8_t deviceI2CAddress = FDC1004_I2C_ADDRESS;

uint8_t FDC_WriteReg16(uint8_t reg, uint16_t val) {

	  uint8_t v[2];
	  uint8_t res;

	  v[0] = val>>8;
	  v[1] = val&0xff;
	  res = GI2C1_WriteAddress(deviceI2CAddress, &reg, sizeof(reg), &v[0], sizeof(v));
	  return res;

	return res;
}

uint8_t FDC_ReadReg16(uint8_t reg, uint16_t *valP) {

	uint8_t res;
	uint16_t value;
	uint16_t* pvalue = &value;
	res =  GI2C1_ReadAddress(deviceI2CAddress, &reg, 1, (uint8_t*)pvalue, 2); //res =  GI2C1_ReadAddress(deviceI2CAddress, &reg, 1, (uint8_t*)valP, 2);
	*valP = ((value<<8)|(value>>8));
	return res;

}



uint8_t FDC_ReadMeasurmentResults(uint32_t *result) {
	uint8_t res;
	uint16_t lsb = 0;
	uint16_t msb = 0;
	uint16_t state;
	uint32_t mainresult;

//	res = FDC_WriteReg16(FDC_CONF, (uint16_t)0b0000010111110000); // Init measure: 100S/s, repeat mode, measure 1-4  0b 0000 0101 1111 0000
//
//	do {
//
//		res = FDC_ReadReg16(FDC_CONF, &state);
//
//	} while ((state & ((uint16_t)0x000F))!= ((uint16_t)0x000F));	// wait until the measure is done


	res = FDC_ReadReg16(MEAS1_MSB, &msb);
	res = FDC_ReadReg16(MEAS1_LSB, &lsb);
	*result = ((((uint32_t)msb)<<16)|((uint32_t)lsb))>>8;	//read CH1
	res = FDC_ReadReg16(MEAS2_MSB, &msb);
	res = FDC_ReadReg16(MEAS2_LSB, &lsb);
	*(result+1) = ((((uint32_t)msb)<<16)|((uint32_t)lsb))>>8;	//read CH2
	res = FDC_ReadReg16(MEAS3_MSB, &msb);
	res = FDC_ReadReg16(MEAS3_LSB, &lsb);
	*(result+2) = ((((uint32_t)msb)<<16)|((uint32_t)lsb))>>8;	//read CH3
	res = FDC_ReadReg16(MEAS4_MSB, &msb);
	res = FDC_ReadReg16(MEAS4_LSB, &lsb);
	mainresult = (((((uint32_t)msb)<<8)|((uint32_t)lsb))>>8);
	*(result+3) = (((((uint32_t)msb)<<8)|((uint32_t)lsb))>>8);	//read CH4   524288


	//res = FDC_WriteReg16(FDC_CONF, (uint8_t) 0b0100010100000000); // Deinit measure: disable repeat mode
	return res;
}

uint8_t FDC_Init(void) {
	uint8_t res;

	res = FDC_WriteReg16(FDC_CONF, (uint16_t)0b1000000000000000);

	res = FDC_WriteReg16(CONF_MEAS1, (uint16_t) 0b0001110000000000);
	res = FDC_WriteReg16(CONF_MEAS2, (uint16_t) 0b0011110000000000);
	res = FDC_WriteReg16(CONF_MEAS3, (uint16_t) 0b0101110000000000);
	res = FDC_WriteReg16(CONF_MEAS4, (uint16_t) 0b0111000000000000);	//0b011 100 00010 00000 Offset 2*3.125pF

	res = FDC_WriteReg16(OFFSET_CAL_CIN4, (uint16_t) 0b11000100000000);   //  0b11000 11010000000 //0b11000 0100000000

	res = FDC_WriteReg16(GAIN_CAL_CIN4, (uint16_t) 0b1111111111111111); // 0b11 11 1111 1111 1111

	res = FDC_WriteReg16(FDC_CONF, (uint16_t)0b0000010111110000);

	return res;
}

