/*
 * Master.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "../StewardPlatform/StewardPlatform.h"

StewardPlatform::StewardPlatform() {

	this->Construct();

}

StewardPlatform::~StewardPlatform() {

}

void StewardPlatform::Construct() {
	/* definition and creation of rxTask */
	osThreadDef(StewardPlatformRxTask, RxTask, osPriorityRealtime, 0, 128);
	rxTaskHandle = osThreadCreate(osThread(StewardPlatformRxTask), &CommunicationCenter);

	/* definition and creation of txTask */
	osThreadDef(StewardPlatformTxTask, TxTask, osPriorityRealtime, 0, 128);
	txTaskHandle = osThreadCreate(osThread(StewardPlatformTxTask), &CommunicationCenter);

	/* definition and creation of touchPanelTask */
	osThreadDef(StewardPlatformTouchPanelTask, TouchPanelTask, osPriorityAboveNormal, 0, 128);
	touchPanelTaskHandle = osThreadCreate(osThread(StewardPlatformTouchPanelTask), &TouchPanel);

}

void StewardPlatform::Execute(Command cmd) {
}

void StewardPlatform::TouchPanelTask(const void* argument) {
	PlatformTouchPanel* touchPanel;

	touchPanel = (PlatformTouchPanel*) argument;
	touchPanel->TouchPanelTask(NULL);
}

void StewardPlatform::TxTask(const void* argument) {
	PlatformCommunicator* communicationCenter;

	communicationCenter = (PlatformCommunicator*) argument;
	communicationCenter->TxTask(NULL);
}

void StewardPlatform::RxTask(const void* argument) {
	PlatformCommunicator* communicationCenter;

	communicationCenter = (PlatformCommunicator*) argument;
	communicationCenter->RxTask(NULL);
}

void StewardPlatform::UARTRxCpltCallback(UART_HandleTypeDef* huart) {
	CommunicationCenter.UARTRxCpltCallback(huart);
}

void StewardPlatform::UARTTxCpltCallback(UART_HandleTypeDef* huart) {
	CommunicationCenter.UARTTxCpltCallback(huart);
}


