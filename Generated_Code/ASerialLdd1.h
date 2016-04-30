/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ASerialLdd1.h
**     Project     : BDA_3D
**     Processor   : MKL25Z128VLK4
**     Component   : Serial_LDD
**     Version     : Component 01.188, Driver 01.12, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-04-11, 15:38, # CodeGen: 104
**     Abstract    :
**         This component "Serial_LDD" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial communication channel.
**     Settings    :
**          Component name                                 : ASerialLdd1
**          Device                                         : UART0
**          Interrupt service/event                        : Enabled
**            Interrupt RxD                                : INT_UART0
**            Interrupt RxD priority                       : medium priority
**            Interrupt TxD                                : INT_UART0
**            Interrupt TxD priority                       : medium priority
**            Interrupt Error                              : INT_UART0
**            Interrupt Error priority                     : medium priority
**          Settings                                       : 
**            Data width                                   : 8 bits
**            Parity                                       : None
**            Stop bits                                    : 1
**            Loop mode                                    : Normal
**            Baud rate                                    : 38400 baud
**            Wakeup condition                             : Idle line wakeup
**            Stop in wait mode                            : no
**            Idle line mode                               : Starts after start bit
**            Transmitter output                           : Not inverted
**            Receiver input                               : Not inverted
**            Break generation length                      : 10/11 bits
**            Receiver                                     : Enabled
**              RxD                                        : TSI0_CH2/PTA1/UART0_RX/TPM2_CH0
**              RxD pin signal                             : 
**            Transmitter                                  : Enabled
**              TxD                                        : TSI0_CH3/PTA2/UART0_TX/TPM2_CH1
**              TxD pin signal                             : 
**            Flow control                                 : None
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnBlockSent                                : Enabled
**              OnBlockReceived                            : Enabled
**              OnTxComplete                               : Disabled
**              OnError                                    : Enabled
**              OnBreak                                    : Enabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init         - LDD_TDeviceData* ASerialLdd1_Init(LDD_TUserData *UserDataPtr);
**         SendBlock    - LDD_TError ASerialLdd1_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         ReceiveBlock - LDD_TError ASerialLdd1_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         GetError     - LDD_TError ASerialLdd1_GetError(LDD_TDeviceData *DeviceDataPtr,...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file ASerialLdd1.h
** @version 01.12
** @brief
**         This component "Serial_LDD" implements an asynchronous serial
**         communication. The component supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The component requires one on-chip asynchronous serial communication channel.
*/         
/*!
**  @addtogroup ASerialLdd1_module ASerialLdd1 module documentation
**  @{
*/         

#ifndef __ASerialLdd1_H
#define __ASerialLdd1_H

/* MODULE ASerialLdd1. */


#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif


/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define ASerialLdd1_PRPH_BASE_ADDRESS  0x4006A000U
  
/* Methods configuration constants - generated for all enabled component's methods */
#define ASerialLdd1_Init_METHOD_ENABLED /*!< Init method of the component ASerialLdd1 is enabled (generated) */
#define ASerialLdd1_SendBlock_METHOD_ENABLED /*!< SendBlock method of the component ASerialLdd1 is enabled (generated) */
#define ASerialLdd1_ReceiveBlock_METHOD_ENABLED /*!< ReceiveBlock method of the component ASerialLdd1 is enabled (generated) */
#define ASerialLdd1_GetError_METHOD_ENABLED /*!< GetError method of the component ASerialLdd1 is enabled (generated) */

/* Events configuration constants - generated for all enabled component's events */
#define ASerialLdd1_OnBlockReceived_EVENT_ENABLED /*!< OnBlockReceived event of the component ASerialLdd1 is enabled (generated) */
#define ASerialLdd1_OnBlockSent_EVENT_ENABLED /*!< OnBlockSent event of the component ASerialLdd1 is enabled (generated) */
#define ASerialLdd1_OnBreak_EVENT_ENABLED /*!< OnBreak event of the component ASerialLdd1 is enabled (generated) */
#define ASerialLdd1_OnError_EVENT_ENABLED /*!< OnError event of the component ASerialLdd1 is enabled (generated) */

#define ENABLED_TX_INT        0x01U    /*!< TX interrupt enabled      */
#define BREAK_DETECTED        0x02U    /*!< Break detected            */
#define TX_COMPLETED          0x04U    /*!< Transmission completed    */
#define ENABLE_TX_COMPLETE    0x10U    /*!< Enable/Disable of TX complete detection. Used in the polling mode only */

/*! Device data structure type */
typedef struct {
  uint16_t SerFlag;                    /*!< Flags for serial communication */
  LDD_SERIAL_TError ErrFlag;           /*!< Error flags mirror of SerFlag */
  uint16_t InpRecvDataNum;             /*!< The counter of received characters */
  uint8_t *InpDataPtr;                 /*!< The buffer pointer for received characters */
  uint16_t InpDataNumReq;              /*!< The counter of characters to receive by ReceiveBlock() */
  uint16_t OutSentDataNum;             /*!< The counter of sent characters */
  uint8_t *OutDataPtr;                 /*!< The buffer pointer for data to be transmitted */
  uint16_t OutDataNumReq;              /*!< The counter of characters to be send by SendBlock() */
  LDD_TUserData *UserDataPtr;          /*!< Pointer to user data */
} ASerialLdd1_TDeviceData;

typedef ASerialLdd1_TDeviceData *ASerialLdd1_TDeviceDataPtr ; /*!< Pointer to the device data structure. */

/*
** ===================================================================
**     Method      :  ASerialLdd1_Init (component Serial_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the "Enable
**         in init. code" is set to "yes" value then the device is also
**         enabled(see the description of the Enable() method). In this
**         case the Enable() method is not necessary and needn't to be
**         generated. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* ASerialLdd1_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  ASerialLdd1_ReceiveBlock (component Serial_LDD)
*/
/*!
**     @brief
**         Specifies the number of data to receive. The method returns
**         ERR_BUSY until the specified number of characters is
**         received. Method [CancelBlockReception] can be used to
**         cancel a running receive operation. If a receive operation
**         is not in progress (the method was not called or a previous
**         operation has already finished) all received characters will
**         be lost without any notification. To prevent the loss of
**         data call the method immediately after the last receive
**         operation has finished (e.g. from the [OnBlockReceived]
**         event). This method finishes immediately after calling it -
**         it doesn't wait the end of data reception. Use event
**         [OnBlockReceived] to check the end of data reception or
**         method GetReceivedDataNum to check the state of receiving.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferPtr       - Pointer to a buffer where
**                           received characters will be stored. In case
**                           of 8bit character width each character in
**                           buffer occupies 1 byte. In case of 9 and
**                           more bit long character width each
**                           character in buffer occupies 2 bytes.
**     @param
**         Size            - Number of characters to receive
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration.
**                           ERR_PARAM_SIZE - Parameter Size is out of
**                           expected range.
**                           ERR_DISABLED - The component or device is
**                           disabled.
**                           ERR_BUSY - The previous receive request is
**                           pending.
*/
/* ===================================================================*/
LDD_TError ASerialLdd1_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size);

/*
** ===================================================================
**     Method      :  ASerialLdd1_SendBlock (component Serial_LDD)
*/
/*!
**     @brief
**         Sends a block of characters. The method returns ERR_BUSY
**         when the previous block transmission is not completed.
**         Method [CancelBlockTransmission] can be used to cancel a
**         transmit operation. This method is available only if the
**         transmitter property is enabled. This method finishes
**         immediately after calling it - it doesn't wait the end of
**         data transmission. Use event [OnBlockSent] to check the end
**         of data transmission or method GetSentDataNum to check the
**         state of sending.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferPtr       - Pointer to a buffer from where
**                           data will be sent. In case of 8bit
**                           character width each character in buffer
**                           occupies 1 byte. In case of 9 and more bit
**                           long character width each character in
**                           buffer occupies 2 bytes.
**     @param
**         Size            - Number of characters in the buffer.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration.
**                           ERR_PARAM_SIZE - Parameter Size is out of
**                           expected range.
**                           ERR_DISABLED - The component or device is
**                           disabled.
**                           ERR_BUSY - The previous transmit request is
**                           pending.
*/
/* ===================================================================*/
LDD_TError ASerialLdd1_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size);

/*
** ===================================================================
**     Method      :  ASerialLdd1_Interrupt (component Serial_LDD)
**
**     Description :
**         The ISR function handling the device receive/transmit 
**         interrupt. Calls InterruptTX/InterruptRX methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
/* {FreeRTOS RTOS Adapter} ISR function prototype */
PE_ISR(ASerialLdd1_Interrupt);

/*
** ===================================================================
**     Method      :  ASerialLdd1_GetError (component Serial_LDD)
*/
/*!
**     @brief
**         This method returns a set of asserted flags. The flags are
**         accumulated in the set. After calling this method the set is
**         returned and cleared.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         ErrorPtr        - A pointer to the returned set of
**                           error flags:
**                           LDD_SERIAL_RX_OVERRUN - Receiver overrun.
**                           LDD_SERIAL_PARITY_ERROR - Parity error
**                           (only if HW supports parity feature).
**                           LDD_SERIAL_FRAMING_ERROR - Framing error.
**                           LDD_SERIAL_NOISE_ERROR - Noise error.
**     @return
**                         - Error code (if GetError did not succeed),
**                           possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_DISABLED - Component is disabled
*/
/* ===================================================================*/
LDD_TError ASerialLdd1_GetError(LDD_TDeviceData *DeviceDataPtr, LDD_SERIAL_TError *ErrorPtr);

/* END ASerialLdd1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __ASerialLdd1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
