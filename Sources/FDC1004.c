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
#include "Detection.h"

#define FDC1004_I2C_ADDRESS 0x50  // b101 0000
static const uint8_t deviceI2CAddress = FDC1004_I2C_ADDRESS;

uint8_t FDC_WriteReg16(uint8_t reg, uint16_t val) {

	uint8_t v[2];
	uint8_t res;

	v[0] = val >> 8;
	v[1] = val & 0xff;
	res = GI2C1_WriteAddress(deviceI2CAddress, &reg, sizeof(reg), &v[0],
			sizeof(v));
	return res;

	return res;
}

uint8_t FDC_ReadReg16(uint8_t reg, uint16_t *valP) {

	uint8_t res;
	uint16_t value;
	uint16_t* pvalue = &value;
	res = GI2C1_ReadAddress(deviceI2CAddress, &reg, 1, (uint8_t*) pvalue, 2); //res =  GI2C1_ReadAddress(deviceI2CAddress, &reg, 1, (uint8_t*)valP, 2);
	*valP = ((value << 8) | (value >> 8));
	return res;

}

uint8_t FDC_ReadMeasurmentResults(int32_t *result) {
	uint8_t res;
	uint16_t lsb = 0;
	uint16_t msb = 0;
	uint16_t state;
	int32_t mainresult;
	uint32_t shiftmsb;
	uint32_t shiftlsb;

//	res = FDC_WriteReg16(FDC_CONF, (uint16_t)0b0000010111110000); // Init measure: 100S/s, repeat mode, measure 1-4  0b 0000 0101 1111 0000
//
//	do {
//
//		res = FDC_ReadReg16(FDC_CONF, &state);
//
//	} while ((state & ((uint16_t)0x000F))!= ((uint16_t)0x000F));	// wait until the measure is done

	res = FDC_ReadReg16(MEAS1_MSB, &msb);
	res = FDC_ReadReg16(MEAS1_LSB, &lsb);
	*(result) = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));
	if ((0x0800000 & *(result)) == 0x0800000) {	//read CH1
		*(result) = (*(result) | 0xFF000000);
	}

	res = FDC_ReadReg16(MEAS2_MSB, &msb);
	res = FDC_ReadReg16(MEAS2_LSB, &lsb);
	*(result + 1) = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));
	if ((0x0800000 & *(result + 1)) == 0x0800000) {	//read CH2
		*(result + 1) = (*(result + 1) | 0xFF000000);
	}

	res = FDC_ReadReg16(MEAS3_MSB, &msb);
	res = FDC_ReadReg16(MEAS3_LSB, &lsb);
	*(result + 2) = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));
	if ((0x0800000 & *(result + 2)) == 0x0800000) {	//read CH3
		*(result + 2) = (*(result + 2) | 0xFF000000);
	}

	res = FDC_ReadReg16(MEAS4_MSB, &msb);
	res = FDC_ReadReg16(MEAS4_LSB, &lsb);
//	shiftmsb = (((uint32_t)msb)<<8);
//	shiftlsb = (((uint32_t)lsb)>>8);
//	mainresult = ((((uint32_t)msb)<<8)|(((uint32_t)lsb)>>8));					//  (((((uint32_t)msb)<<8)|((uint32_t)lsb))>>8);
	*(result + 3) = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));//read CH4   524288
	if ((0x0800000 & *(result + 3)) == 0x0800000) {
		*(result + 3) = (*(result + 3) | 0xFF000000);
	}

	//res = FDC_WriteReg16(FDC_CONF, (uint8_t) 0b0100010100000000); // Deinit measure: disable repeat mode
	return res;
}

uint8_t FDC_ReadRawValues(struct cap_val *data) {
	uint8_t res;
	uint16_t lsb = 0;
	uint16_t msb = 0;

	res = FDC_ReadReg16(MEAS1_MSB, &msb);
	res = FDC_ReadReg16(MEAS1_LSB, &lsb);
	data->bottom = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));
	if ((0x0800000 & data->bottom) == 0x0800000) {	//read CH1
		data->bottom = (data->bottom | 0xFF000000);
	}

	res = FDC_ReadReg16(MEAS2_MSB, &msb);
	res = FDC_ReadReg16(MEAS2_LSB, &lsb);
	data->left = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));
	if ((0x0800000 & data->left) == 0x0800000) {	//read CH2
		data->left = (data->left | 0xFF000000);
	}

	res = FDC_ReadReg16(MEAS3_MSB, &msb);
	res = FDC_ReadReg16(MEAS3_LSB, &lsb);
	data->top = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));//read CH4   524288
	if ((0x0800000 & data->top) == 0x0800000) {
		data->top = (data->top | 0xFF000000);
	}

	res = FDC_ReadReg16(MEAS4_MSB, &msb);
	res = FDC_ReadReg16(MEAS4_LSB, &lsb);
	data->right = ((((uint32_t) msb) << 8) | (((uint32_t) lsb) >> 8));
		if ((0x0800000 & data->right) == 0x0800000) {	//read CH3
			data->right = (data->right | 0xFF000000);
		}

	return res;
}

uint8_t FDC_Init(void) {
	uint8_t res;

	res = FDC_WriteReg16(FDC_CONF, (uint16_t) 0b1000000000000000);

	res = FDC_WriteReg16(CONF_MEAS1, (uint16_t) 0b0001110000000000);
	res = FDC_WriteReg16(CONF_MEAS2, (uint16_t) 0b0011110000000000);
	res = FDC_WriteReg16(CONF_MEAS3, (uint16_t) 0b0101110000000000);
	res = FDC_WriteReg16(CONF_MEAS4, (uint16_t) 0b0111110000000000);//0b011 100 00010 00000 Offset 2*3.125pF

//	Ohne GND Plane
	float gain = FDC_Calc_Fixpoint((uint16_t) 0b1011111110000000);
	res = FDC_WriteReg16(OFFSET_CAL_CIN4, (uint16_t) 0b1101111110000000);   // Testaufbau 0b11001 11110000000
	res = FDC_WriteReg16(OFFSET_CAL_CIN3, (uint16_t) 0b1101111110000000);
	res = FDC_WriteReg16(OFFSET_CAL_CIN2, (uint16_t) 0b1101111110000000);
	res = FDC_WriteReg16(OFFSET_CAL_CIN1, (uint16_t) 0b1101111110000000);

//	//	Mit GND Plane
//	float gain = FDC_Calc_Fixpoint((uint16_t) 0b1000011110000000);
//	res = FDC_WriteReg16(OFFSET_CAL_CIN4, (uint16_t) 0b1011111110000000); // Testaufbau 0b11001 11110000000
//	res = FDC_WriteReg16(OFFSET_CAL_CIN3, (uint16_t) 0b1011111110000000);
//	res = FDC_WriteReg16(OFFSET_CAL_CIN2, (uint16_t) 0b1011111110000000);
//	res = FDC_WriteReg16(OFFSET_CAL_CIN1, (uint16_t) 0b1011111110000000);


	res = FDC_WriteReg16(GAIN_CAL_CIN4, (uint16_t) 0b0111111111111111); // 0b11 11 1111 1111 1111  // 0b0111111111111111
	res = FDC_WriteReg16(GAIN_CAL_CIN3, (uint16_t) 0b0111111111111111);
	res = FDC_WriteReg16(GAIN_CAL_CIN2, (uint16_t) 0b0111111111111111);
	res = FDC_WriteReg16(GAIN_CAL_CIN1, (uint16_t) 0b0111111111111111);

	res = FDC_WriteReg16(FDC_CONF, (uint16_t) 0b0000010111110000); // start continuous measure   0b0000 0101 1111 0000

	return res;
}

float FDC_Calc_Fixpoint(uint16_t val) {
	float result = 0;

	if ((val & (((uint16_t) 1) << 15)) == (((uint16_t) 1) << 15)) {
		result += -16;
	}
	if ((val & (((uint16_t) 1) << 14)) == (((uint16_t) 1) << 14)) {
		result += 8;
	}
	if ((val & (((uint16_t) 1) << 13)) == (((uint16_t) 1) << 13)) {
		result += 4;
	}
	if ((val & (((uint16_t) 1) << 12)) == (((uint16_t) 1) << 12)) {
		result += 2;
	}
	if ((val & (((uint16_t) 1) << 11)) == (((uint16_t) 1) << 11)) {
		result += 1;
	}
	if ((val & (((uint16_t) 1) << 10)) == (((uint16_t) 1) << 10)) {
		result += (float) 1 / (float) 2;
	}
	if ((val & (((uint16_t) 1) << 9)) == (((uint16_t) 1) << 9)) {
		result += (float) 1 / (float) 4;
	}
	if ((val & (((uint16_t) 1) << 8)) == (((uint16_t) 1) << 8)) {
		result += (float) 1 / (float) 8;
	}
	if ((val & (((uint16_t) 1) << 7)) == (((uint16_t) 1) << 7)) {
		result += (float) 1 / (float) 16;
	}
	if ((val & (((uint16_t) 1) << 6)) == (((uint16_t) 1) << 6)) {
		result += (float) 1 / (float) 32;
	}
	if ((val & (((uint16_t) 1) << 5)) == (((uint16_t) 1) << 5)) {
		result += (float) 1 / (float) 64;
	}
	if ((val & (((uint16_t) 1) << 4)) == (((uint16_t) 1) << 4)) {
		result += (float) 1 / (float) 128;
	}
	if ((val & (((uint16_t) 1) << 3)) == (((uint16_t) 1) << 3)) {
		result += (float) 1 / (float) 256;
	}
	return result;

}

