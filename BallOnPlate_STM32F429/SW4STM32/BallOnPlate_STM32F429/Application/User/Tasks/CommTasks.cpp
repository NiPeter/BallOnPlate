/*
 * CommTasks.cpp
 *
 *  Created on: 12 wrz 2017
 *      Author: Peter
 */

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


#include "../Master/Master.h"

extern Master* master;

/**
 *
 * @param argument
 */
void StartRxTask(void const * argument)
{
	/* USER CODE BEGIN StartRxTask */
	master->RxTask(argument);
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
	master->TxTask(argument);
	/* USER CODE END StartTxTask */
}
/********************************************************/



/**
 *
 * @param huart
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	master->UARTTxCpltCallback(huart);
}
/********************************************************/



/*
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	master->UARTRxCpltCallback(huart);

}
/********************************************************/
