/*
 * Master.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef STEWARDPLATFORM_H_
#define STEWARDPLATFORM_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "PlatformCommunicator/PlatformCommunicator.h"
#include "PlatformControlSystem/PlatformControlSystem.h"
#include "PlatformTouchPanel/PlatformTouchPanel.h"
#include "PlatformModes/PIDMode/PIDMode.h"

/**
 *
 */
class StewardPlatform {

public:

	StewardPlatform();
	virtual ~StewardPlatform();

	void Execute(Command cmd);

	void SetMode(ModeType_e modeType);


	static void TxTask(void const * argument);
	static void RxTask(void const * argument);
	static void TouchPanelTask(void const * argument);
	static void CommunicationTask(void const * argument);



	void UART_RxCpltCallback(UART_HandleTypeDef *huart);
	void UART_TxCpltCallback(UART_HandleTypeDef *huart);

public:


	PlatformControlSystem		Platform;
	PlatformTouchPanel			TouchPanel;
	PlatformCommunicator		CommunicationCenter;

	PlatformMode*				Mode;

	osThreadId rxTaskHandle;
	osThreadId txTaskHandle;
	osThreadId touchPanelTaskHandle;
	osThreadId communicationTaskHandle;

	void Construct();
};

#endif /* STEWARDPLATFORM_H_ */
