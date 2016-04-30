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
#if HAS_RTOS
#include "FRTOS1.h"
#endif
CLS1_ConstStdIOType *io;
uint32_t cap[4];

void Init_Measure(void) {

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
	//uint32_t cap[4];

	for (;;) {
		result = FDC_ReadMeasurmentResults(cap);
		if (result != ERR_OK) {
			CLS1_SendStr("ERROR Capacity: ", io->stdErr);
			CLS1_SendNum8u(result, io->stdErr);
		} else {
//			for(int i = 0; i<4;i++){
//			CLS1_SendStr("   Capacity: "  , io->stdOut);
//			CLS1_SendNum32u(cap[i], io->stdOut);
//			}
			CLS1_SendNum32u(cap[3], io->stdOut);
		}
		CLS1_SendStr(";\r\n", io->stdOut);
#if HAS_RTOS
		FRTOS1_vTaskDelay(40/portTICK_RATE_MS);
#else
		WAIT1_Waitms(500);
#endif
		LED1_Neg();

	}

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
