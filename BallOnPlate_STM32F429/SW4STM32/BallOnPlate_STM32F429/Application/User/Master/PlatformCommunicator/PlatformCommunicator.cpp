/*
 * PlatformCommunicator.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "PlatformCommunicator.h"

PlatformCommunicator::PlatformCommunicator()
	: Bluetooth(&huart1),Communicator(&Bluetooth){

	  /* definition and creation of txSemaphore */
	  osSemaphoreDef(txSemaphore);
	  txSemaphoreHandle = osSemaphoreCreate(osSemaphore(txSemaphore), 1);

	  /* definition and creation of rxSemaphore */
	  osSemaphoreDef(rxSemaphore);
	  rxSemaphoreHandle = osSemaphoreCreate(osSemaphore(rxSemaphore), 1);


}

PlatformCommunicator::~PlatformCommunicator() {
	// TODO Auto-generated destructor stub
}

void PlatformCommunicator::TxTask(const void* argument) {
	osSemaphoreWait(rxSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(rxSemaphoreHandle,osWaitForever);
		Bluetooth.processRxISR();
	}
}

void PlatformCommunicator::RxTask(const void* argument) {

	osSemaphoreWait(txSemaphoreHandle,osWaitForever);

	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(txSemaphoreHandle,osWaitForever);
		Bluetooth.processTxISR();
	}
}

void PlatformCommunicator::UARTRxCpltCallback(UART_HandleTypeDef* huart) {
	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(txSemaphoreHandle);
}

void PlatformCommunicator::UARTTxCpltCallback(UART_HandleTypeDef* huart) {
	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(rxSemaphoreHandle);
}
