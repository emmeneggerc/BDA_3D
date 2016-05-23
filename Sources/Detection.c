/*
 * Detection.c
 *
 *  Created on: 03.05.2016
 *      Author: Cornel Emmenegger
 */

#include "Detection.h"
#include "FRTOS1.h"
#include "FDC1004.h"
#include "Application.h"
#include "CLS1.h"
#include "CS1.h"

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#define RAW_BUFFER_SIZE 100
#define POS_BUFFER_SIZE 100
#define DERV_BUFFER_SIZE 20
#define SAMPLING_TIME_MS 50
/************************************************************************/
/* Variables                                                            */
/************************************************************************/
static float deltaTime = SAMPLING_TIME_MS * 0.001;
cap_val rawData[RAW_BUFFER_SIZE];
uint8_t rawBufIndex = 0;
coordinates positions[POS_BUFFER_SIZE];
uint8_t posBufIndex = 0;
cap_val calibData;

cap_deriv derivation;
coordinates posDerivation[DERV_BUFFER_SIZE];
uint8_t posDerBufIndex = 0;

int16_t maxNoiseX;
int16_t minNoiseX;
int16_t maxNoiseY;
int16_t minNoiseY;
int16_t motionThresholdX = 32000;
int16_t motionThresholdY = 30000;
int posX = 0;
int posY = 0;

/************************************************************************/
/* Functions                                                            */
/************************************************************************/
//void DECT_CalcPosition(void);
//void DECT_CalcDerivation(uint8_t interval);
//void DECT_CalcDirectionalDerivation(uint8_t interval);
//void DECT_ReadSample(void);
//void DECT_Init(void);
//void DECT_Calib(void);
//void DECT_GetPosition(coordinates* actPos);
//void DECT_GetDirectionalDerivation(coordinates* actDerivation);
//void DECT_CheckMotion(void);
static void DECT_Task(void* param) {
	for (;;) {
		DECT_ReadSample();
		DECT_CalcPosition();
		DECT_CalcDirectionalDerivation((uint8_t) 1);
	}
}

/*!
 * \brief Calculates the current position of the object and write the result the position-buffer
 */
void DECT_CalcPosition(void) {

	CS1_CriticalVariable()
	;

	CS1_EnterCritical()
	;
	posBufIndex++;
	if (posBufIndex >= POS_BUFFER_SIZE) {
		posBufIndex = 0;
	}
	positions[posBufIndex].x = (rawData[rawBufIndex].right - calibData.right)
			- (rawData[rawBufIndex].left - calibData.left);
	positions[posBufIndex].y = (rawData[rawBufIndex].top - calibData.top)
			- (rawData[rawBufIndex].bottom - calibData.bottom);
	CS1_ExitCritical()
	;
}

/*!
 * \brief Calculates the current derivation of each capacity
 * * \param interval The interval where the derivation should be calculated
 */
void DECT_CalcDerivation(uint8_t interval) {

	int8_t y2 = rawBufIndex;
	int8_t y1 = y2 - interval;

	if (y1 < 0) {
		y1 = RAW_BUFFER_SIZE + y1;
	}
	derivation.bottom = (float) (rawData[y2].bottom - rawData[y1].bottom)
			/ (interval * deltaTime);
	derivation.left = (float) (rawData[y2].left - rawData[y1].left)
			/ (interval * deltaTime);
	derivation.right = (float) (rawData[y2].right - rawData[y1].right)
			/ (interval * deltaTime);
	derivation.top = (float) (rawData[y2].top - rawData[y1].top)
			/ (interval * deltaTime);
}

/*!
 * \brief Calculates the current directional derivation of the object
 * * \param interval The interval where the directional derivation should be calculated
 */
void DECT_CalcDirectionalDerivation(uint8_t interval) {
	CS1_CriticalVariable()
	;

	int8_t y2 = posBufIndex;
	int8_t y1 = y2 - interval;

	if (y1 < 0) {
		y1 = POS_BUFFER_SIZE + y1;
	}

	CS1_EnterCritical()
	;
	rawBufIndex++;
	if (rawBufIndex >= RAW_BUFFER_SIZE) {
		rawBufIndex = 0;

	}
	CS1_ExitCritical()
	;
	posDerivation[posDerBufIndex].x =
			(float) (positions[y2].x - positions[y1].x)
					/ (interval * deltaTime);
	posDerivation[posDerBufIndex].y =
			(float) (positions[y2].y - positions[y1].y)
					/ (interval * deltaTime);
	CS1_ExitCritical()
	;
}

/*!
 * \brief Checks if there's a motion of an object on the sensor
 */
void DECT_CheckMotion(void) {


	if ((posDerivation[posDerBufIndex].x > motionThresholdX)) {
		posX = 100;
	} else if ((posDerivation[posDerBufIndex].x < -motionThresholdX)) {
		posX = -100;
	} else {
		posX = 0;
	}

	if ((posDerivation[posDerBufIndex].y > motionThresholdY)) {
		posY = 100;
	} else if ((posDerivation[posDerBufIndex].y < -motionThresholdY)) {
		posY = -100;
	} else {
		posY = 0;
	}

}

/*!
 * \brief Reads the current capacity measurement value of each capacity
 */
void DECT_ReadSample(void) {
	cap_val actData;
	CS1_CriticalVariable()
	;

	CS1_EnterCritical()
	;
	rawBufIndex++;
	if (rawBufIndex >= RAW_BUFFER_SIZE) {
		rawBufIndex = 0;
	}
	FDC_ReadRawValues(&actData);
	rawData[rawBufIndex] = actData;
	CS1_ExitCritical()
	;
}

/*!
 * \brief Calibrates the capacity sensors
 */
void DECT_Calib(void) {

	int32_t bottomSum = 0;
	int32_t leftSum = 0;
	int32_t rightSum = 0;
	int32_t topSum = 0;

	for (uint8_t i = 0; i < RAW_BUFFER_SIZE; i++) {

		bottomSum += rawData[i].bottom;
		leftSum += rawData[i].left;
		rightSum += rawData[i].right;
		topSum += rawData[i].top;
	}

	calibData.bottom = (bottomSum / RAW_BUFFER_SIZE);
	calibData.left = (leftSum / RAW_BUFFER_SIZE);
	calibData.right = (rightSum / RAW_BUFFER_SIZE);
	calibData.top = (topSum / RAW_BUFFER_SIZE);

}

void DECT_GetPosition(coordinates* actPos) {
	*actPos = positions[posBufIndex];
}

void DECT_GetDirectionalDerivation(coordinates* actDerivation) {
	*actDerivation = posDerivation[posDerBufIndex];
}

/*!
 * \brief Starts the detection task
 */
void DECT_CreateTask(void) {
	if (FRTOS1_xTaskCreate(DECT_Task, (signed portCHAR *)"Detection",
			configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1,
			NULL) != pdPASS) {
		for (;;) { /*error*/
		}
	}
}

