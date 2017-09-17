/*
 * Master.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "StewardPlatform.h"
#include <Communicator/Command/CmdType.h>



/**
 *
 */
StewardPlatform::StewardPlatform() {

	this->Construct();

	Mode = new PIDMode(this,10);

}
/********************************************************/



/**
 *
 */
StewardPlatform::~StewardPlatform() {
	delete Mode;

	osThreadTerminate(rxTaskHandle);
	osThreadTerminate(txTaskHandle);
	osThreadTerminate(touchPanelTaskHandle);
}
/********************************************************/



/**
 *
 */
void StewardPlatform::Construct() {
	/* definition and creation of rxTask */
	osThreadDef(StewardPlatformRxTask, RxTask, osPriorityRealtime, 0, 128);
	rxTaskHandle = osThreadCreate(osThread(StewardPlatformRxTask), &CommunicationCenter);

	/* definition and creation of txTask */
	osThreadDef(StewardPlatformTxTask, TxTask, osPriorityRealtime, 0, 128);
	txTaskHandle = osThreadCreate(osThread(StewardPlatformTxTask), &CommunicationCenter);

	/* definition and creation of touchPanelTask */
	osThreadDef(StewardPlatformTouchPanelTask, TouchPanelTask, osPriorityAboveNormal, 0, 256);
	touchPanelTaskHandle = osThreadCreate(osThread(StewardPlatformTouchPanelTask), &TouchPanel);

}
/********************************************************/



/**
 *
 * @param argument
 */
void StewardPlatform::TouchPanelTask(const void* argument) {
	PlatformTouchPanel* touchPanel;

	touchPanel = (PlatformTouchPanel*) argument;
	touchPanel->TouchPanelTask(NULL);
}
/********************************************************/



/**
 *
 * @param argument
 */
void StewardPlatform::TxTask(const void* argument) {
	PlatformCommunicator* communicationCenter;

	communicationCenter = (PlatformCommunicator*) argument;
	communicationCenter->TxTask(NULL);
}
/********************************************************/



/**
 *
 * @param argument
 */
void StewardPlatform::RxTask(const void* argument) {
	PlatformCommunicator* communicationCenter;

	communicationCenter = (PlatformCommunicator*) argument;
	communicationCenter->RxTask(NULL);
}
/********************************************************/



/**
 *
 * @param huart
 */
void StewardPlatform::UART_RxCpltCallback(UART_HandleTypeDef* huart) {
	CommunicationCenter.UARTRxCpltCallback(huart);
}
/********************************************************/



/**
 *
 * @param huart
 */
void StewardPlatform::UART_TxCpltCallback(UART_HandleTypeDef* huart) {
	CommunicationCenter.UARTTxCpltCallback(huart);
}
/********************************************************/



/**
 *
 * @param cmd
 */
void StewardPlatform::Execute(Command cmd) {
	CmdType_e 	cmdType = cmd.getType();
	float		cmdParam = cmd.getParam();

	switch(cmdType){

	case fail:
		break;
	case ok:
		break;




	default:
		break;
	}
}
/********************************************************/
