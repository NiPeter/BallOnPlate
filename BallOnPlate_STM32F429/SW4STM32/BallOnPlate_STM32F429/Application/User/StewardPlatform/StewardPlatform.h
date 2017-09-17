/*
 * Master.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef STEWARDPLATFORM_H_
#define STEWARDPLATFORM_H_

#include "../StewardPlatform/PlatformCommunicator/PlatformCommunicator.h"
#include "../StewardPlatform/PlatformControlSystem/PlatformControlSystem.h"
#include "../StewardPlatform/PlatformTouchPanel/PlatformTouchPanel.h"


/**
 *
 */
class StewardPlatform {

public:
	StewardPlatform();
	virtual ~StewardPlatform();

	void Execute(Command cmd);

	static void TxTask(void const * argument);
	static void RxTask(void const * argument);
	static void TouchPanelTask(void const * argument);

	void UART_RxCpltCallback(UART_HandleTypeDef *huart);
	void UART_TxCpltCallback(UART_HandleTypeDef *huart);

public:

	PlatformControlSystem		Platform;
	PlatformTouchPanel			TouchPanel;
	PlatformCommunicator		CommunicationCenter;

	//IMode&

	osThreadId rxTaskHandle;
	osThreadId txTaskHandle;
	osThreadId touchPanelTaskHandle;

	void Construct();

};

#endif /* STEWARDPLATFORM_H_ */
