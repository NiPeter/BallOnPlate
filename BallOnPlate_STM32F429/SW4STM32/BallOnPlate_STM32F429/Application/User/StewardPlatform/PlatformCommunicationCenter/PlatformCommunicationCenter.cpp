/*
 * PlatformCommunicator.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "../PlatformCommunicationCenter/PlatformCommunicationCenter.h"

PlatformCommunicationCenter::PlatformCommunicationCenter():Bluetooth(&huart1),Comm(&Bluetooth){

	  /* definition and creation of txSemaphore */
	  osSemaphoreDef(txSemaphore);
	  txSemaphoreHandle = osSemaphoreCreate(osSemaphore(txSemaphore), 1);

	  /* definition and creation of rxSemaphore */
	  osSemaphoreDef(rxSemaphore);
	  rxSemaphoreHandle = osSemaphoreCreate(osSemaphore(rxSemaphore), 1);

		/* creation of rxTask */
		rxTaskHandle = osThreadCreate(osThread(CommCenterRxTask), this);

		/* creation of txTask */
		txTaskHandle = osThreadCreate(osThread(CommCenterTxTask), this);

}

PlatformCommunicationCenter::~PlatformCommunicationCenter() {
	osThreadTerminate(rxTaskHandle);
	osThreadTerminate(txTaskHandle);
}

void PlatformCommunicationCenter::TxTask(const void* argument) {
	PlatformCommunicationCenter* communicationCenter;
	communicationCenter = (PlatformCommunicationCenter*)argument;

	osSemaphoreWait(communicationCenter->txSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(communicationCenter->txSemaphoreHandle,osWaitForever);
		communicationCenter->Bluetooth.processTxISR();
	}
}

void PlatformCommunicationCenter::RxTask(const void* argument) {
	PlatformCommunicationCenter* communicationCenter;
	communicationCenter = (PlatformCommunicationCenter*)argument;

	osSemaphoreWait(communicationCenter->rxSemaphoreHandle,osWaitForever);
	/* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(communicationCenter->rxSemaphoreHandle,osWaitForever);
		communicationCenter->Bluetooth.processRxISR();
	}
}

void PlatformCommunicationCenter::UARTRxCpltCallback(UART_HandleTypeDef* huart) {
	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(rxSemaphoreHandle);
}

void PlatformCommunicationCenter::UARTTxCpltCallback(UART_HandleTypeDef* huart) {
	if(huart->Instance == Bluetooth.getUARTInstance())
		osSemaphoreRelease(txSemaphoreHandle);
}

