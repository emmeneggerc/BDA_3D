/*
 * Detection.h
 *
 *  Created on: 03.05.2016
 *      Author: Cornel Emmenegger
 */

#ifndef SOURCES_DETECTION_H_
#define SOURCES_DETECTION_H_

#include <stdint.h>

/************************************************************************/
/* Defines                                                              */
/************************************************************************/


typedef struct cap_val{
int32_t bottom;
int32_t left;
int32_t top;
int32_t right;
}cap_val;


typedef struct cap_deriv{
float bottom;
float left;
float top;
float right;
}cap_deriv;

typedef struct coordinates{
	float x;
	float y;
}coordinates;

/************************************************************************/
/* Functions                                                            */
/************************************************************************/
void DECT_CreateTask(void);

void DECT_CalcPosition(void);
void DECT_CalcDerivation(uint8_t interval);
void DECT_CalcDirectionalDerivation(uint8_t interval);
void DECT_ReadSample(void);
void DECT_Init(void);
void DECT_Calib(void);
void DECT_GetPosition(coordinates* actPos);
void DECT_GetDirectionalDerivation(coordinates* actDerivation);
void DECT_CheckMotion(void);



#endif /* SOURCES_DETECTION_H_ */
