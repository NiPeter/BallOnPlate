/*
 * CommTasks.cpp
 *
 *  Created on: 12 wrz 2017
 *      Author: Peter
 */

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


#include "../Communicator/Serial/HC05/HC05.hpp"
#include "../Communicator/Communicator.hpp"



extern osSemaphoreId txSemaphoreHandle;
extern osSemaphoreId rxSemaphoreHandle;

extern HC05 Bluetooth;




/**
 *
 * @param argument
 */
void StartRxTask(void const * argument)
{
	/* USER CODE BEGIN StartRxTask */
	osSemaphoreWait(rxSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(rxSemaphoreHandle,osWaitForever);
		Bluetooth.processRxISR();
	}
	/* USER CODE END StartRxTask */
}
/********************************************************/



/**
 *
 * @param argument
 */
void StartTxTask(void const * argument)
{
	/* USER CODE BEGIN StartTxTask */
	osSemaphoreWait(txSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(txSemaphoreHandle,osWaitForever);
		Bluetooth.processTxISR();
	}
	/* USER CODE END StartTxTask */
}
/********************************************************/



/**
 *
 * @param huart
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(txSemaphoreHandle);

}
/********************************************************/



/*
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(rxSemaphoreHandle);

}
/********************************************************/
