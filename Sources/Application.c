/*
 * Application.c
 *
 *  Created on: 30.03.2016
 *      Author: Cornel Emmenegger
 */

#include "Application.h"
#include "VL6180X.h"
#include "CLS1.h"
#include "LED1.h"
#include "WAIT1.h"
#include "SH7776.h"
#include "FDC1004.h"
#include "Detection.h"
#if HAS_RTOS
#include "FRTOS1.h"
#endif

#include <stdio.h>

/************************************************************************/
/* Variables                                                            */
/************************************************************************/
CLS1_ConstStdIOType *io;
int32_t cap[4];
uint32_t testval = 44;
int32_t valX;
int32_t valY;

/************************************************************************/
/* Functions                                                            */
/************************************************************************/
void Test_Sensors_MeanVal(void);
void Test_Sensors_Derivation(void);
void Test_Sensors_RawVal(void);
void Test_Sensors_Motion(void);
void Init_Measure(void);

void Init_App(void) {

	io = CLS1_GetStdio();
	LED1_On();
	CLS1_SendStr("Initialisation", io->stdOut);
	CLS1_SendStr("\r\n", io->stdOut);

#if IS_VL6180
	VL_Init();
#endif

#if IS_SH7776
	SH_Init();
#endif

#if IS_FDC
	FDC_Init();
#endif

}

#if IS_VL6180

#if HAS_RTOS
static void AppTask(void* param)
#else
void APP_Run(void)
#endif
{
	Init_Measure();
	uint8_t distance, result;

	for (;;) {
		VL_ReadRangeSingle(&distance);
		if (result != ERR_OK) {
			CLS1_SendStr("ERROR Distance: ", io->stdErr);
			CLS1_SendNum8u(result, io->stdErr);
		} else {
			CLS1_SendStr("Distance: ", io->stdOut);
			CLS1_SendNum8u(distance, io->stdOut);
		}
		CLS1_SendStr("\r\n", io->stdOut);
#if HAS_RTOS
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
#else
		WAIT1_Waitms(50);
#endif
		LED1_Neg();

	}

}
#endif

#if IS_SH7776
#if HAS_RTOS
static void AppTask(void* param)
#else
void APP_Run(void)
#endif
{

	Init_Measure();
#if HAS_RTOS
	FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#else
	WAIT1_Waitms(100);
#endif

	uint8_t result;
	uint16_t distance;

	for (;;) {
		result = SH_ReadProximity(&distance);
		if (result != ERR_OK) {
			CLS1_SendStr("ERROR Distance: ", io->stdErr);
			CLS1_SendNum8u(result, io->stdErr);
		} else {
			CLS1_SendStr("Distance: ", io->stdOut);
			CLS1_SendNum16u(distance, io->stdOut);
		}
		CLS1_SendStr("\r\n", io->stdOut);
#if HAS_RTOS
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
#else
		WAIT1_Waitms(500);
#endif
		LED1_Neg();

	}

}
#endif

#if IS_FDC
static void AppTask(void* param) {

	Init_App();
#if HAS_RTOS
	FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#endif

	//Test_Sensors_MeanVal();
	//Test_Sensors_Derivation();
	Test_Sensors_Motion();
}
#endif

#if HAS_RTOS
void RTOS_Run(void) {
	FRTOS1_vTaskStartScheduler(); /* does usually not return! */
}

void APP_Run(void) {
	/*! \App Task */

	if (FRTOS1_xTaskCreate(AppTask, (signed portCHAR *)"App",
			configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1,
			NULL) != pdPASS) {
		for (;;) { /*error*/
		}
	}
	RTOS_Run();
}
#endif

void Test_Sensors_MeanVal(void) {
	uint8_t result;
	uint32_t sum = 0;

	for (;;) {

		for (int i = 0; i < 200; i++) {
			result = FDC_ReadMeasurmentResults(cap);
			sum += cap[3];

#if HAS_RTOS
			FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
#endif

		}
		sum = sum / 200;
		CLS1_SendStr("mean:   ", io->stdOut);
		CLS1_SendNum32u(sum, io->stdOut);
		CLS1_SendStr("\r\n", io->stdOut);
		sum = 0;
	}

}

void Test_Sensors_Derivation(void) {
	uint8_t result;
	uint32_t oldValue = 0;
	int32_t actDeriv;
	int32_t highestDeriv = 0;

	result = FDC_ReadMeasurmentResults(cap);
	oldValue = cap[3];

	for (int i = 0;; i++) {

		result = FDC_ReadMeasurmentResults(cap);
		actDeriv = cap[3] - oldValue;

		if (actDeriv > highestDeriv) {
			highestDeriv = actDeriv;
		}

		CLS1_SendStr("Deriv:   ", io->stdOut);
		CLS1_SendNum32s(highestDeriv, io->stdOut);
		CLS1_SendStr("\r\n", io->stdOut);

		oldValue = cap[3];

#if HAS_RTOS
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
#endif

		if (i > 20) {
			i = 0;
			highestDeriv = 0;
			result = FDC_ReadMeasurmentResults(cap);
			oldValue = cap[3];
		}

	}

}

void Test_Sensors_RawVal(void) {

	uint8_t result;

	for (;;) {
		result = FDC_ReadMeasurmentResults(cap);

		if (result != ERR_OK) {
			CLS1_SendStr("ERROR Capacity: ", io->stdErr);
			CLS1_SendNum8u(result, io->stdErr);
		} else {
			for (int i = 0; i < 4; i++) {
				CLS1_SendStr("   Capacity: ", io->stdOut);
				CLS1_SendNum32s(cap[i], io->stdOut);

			}

		}
		CLS1_SendStr(";\r\n", io->stdOut);
#if HAS_RTOS
		FRTOS1_vTaskDelay(30/portTICK_RATE_MS);
#endif
		LED1_Neg();

	}
}

void Test_Sensors_Motion(void) {

	coordinates actPosition;
	char buf[100];
	char* string = &buf[0];
	int i = 0;

	for (int i = 0; i < 100; i++) {
		DECT_ReadSample();
	}

	DECT_Calib();

	for (;;) {

		//for (int i = 0; i < 50; i++) {

		DECT_ReadSample();
		DECT_CalcPosition();
		DECT_CalcDirectionalDerivation((uint8_t) 20);
		//DECT_GetPosition(&actPosition);
		DECT_GetDirectionalDerivation(&actPosition);
		DECT_CheckMotion();
		//sprintf(string, "X:  %.3f", actPosition.x);
//		sprintf(string, "X:  %d", actPosition.x);
//		CLS1_SendStr(string, io->stdOut);
		valX = (int32) actPosition.x;
//		CLS1_SendStr("X: ", io->stdOut);
//		CLS1_SendNum32s(valX, io->stdOut);
		valY = (int32) actPosition.y;
//		CLS1_SendStr("    Y: ", io->stdOut);
//		CLS1_SendNum32s(valY, io->stdOut);
//		CLS1_SendStr("\r\n", io->stdOut);

		FRTOS1_vTaskDelay(20/portTICK_RATE_MS);

		if (i > 1000) {
			i = 0;
			DECT_Calib();
			LED1_Neg();
		}
		i++;
	}
//	LED1_Off();
//	DECT_Calib();
//
//	for (int i = 0; i < 50; i++) {
//		valX = (int32) actPosition[i].x;
//		CLS1_SendNum32s(valX, io->stdOut);
//		CLS1_SendStr(";\r\n", io->stdOut);
//		FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
//	}
//
//	}

}

