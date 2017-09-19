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

#include "PlatformCommunicationCenter/PlatformCommunicationCenter.h"
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

	void Execute(MessagePacket cmd);

	void SetMode(ModeType_e modeType);

	void UART_RxCpltCallback(UART_HandleTypeDef *huart);
	void UART_TxCpltCallback(UART_HandleTypeDef *huart);

protected:


	PlatformControlSystem			Platform;
	PlatformTouchPanel				TouchPanel;
	PlatformCommunicationCenter		CommunicationCenter;

	PlatformMode*					Mode;

private:

	osThreadDef(StewardPlatformCommunicationTask, CommunicationTask, osPriorityNormal, 0, 512);
	osThreadId communicationTaskHandle;

	static void CommunicationTask(void const * argument);

	void Construct();
};

#endif /* STEWARDPLATFORM_H_ */
