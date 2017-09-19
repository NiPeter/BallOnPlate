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

#include <Communicator/MessagePacket/CmdType.h>

#include "PlatformCommunicationCenter/PlatformCommunicationCenter.h"
#include "PlatformControlSystem/PlatformControlSystem.h"
#include "PlatformTouchPanel/PlatformTouchPanel.h"
#include "PlatformModes/PIDMode/PIDMode.h"
#include "PlatformModes/IKMode/IKMode.h"

class Command;
class CommandFactory;

/**
 *
 */
class StewardPlatform {

public:

	StewardPlatform();
	virtual ~StewardPlatform();

	void Execute(MessagePacket cmd);

	void SetMode(ModeType_e modeType);

	void StartProcedure(void){
		PlatformSystem.Controller.Start();
		double q[6] = {0,0,0,0,0,0};
		PlatformSystem.Controller.Move(q);
		osDelay(100);

		q[2] = -0.01;
		PlatformSystem.Controller.Move(q);
		osDelay(300);

		q[2] = 0;
		PlatformSystem.Controller.Move(q);
		osDelay(100);

		q[2] = -0.002;
		PlatformSystem.Controller.Move(q);
		osDelay(100);
	}

	void UART_RxCpltCallback(UART_HandleTypeDef *huart);
	void UART_TxCpltCallback(UART_HandleTypeDef *huart);

	PlatformControlSystem			PlatformSystem;
	PlatformTouchPanel				TouchPanelSystem;
	PlatformCommunicationCenter		CommunicationCenter;

	PlatformMode*					Mode;

private:

	osThreadDef(StewardPlatformCommunicationTask, CommunicationTask, osPriorityNormal, 0, 512);
	osThreadId communicationTaskHandle;

	static void CommunicationTask(void const * argument);

	void Construct();
};

#endif /* STEWARDPLATFORM_H_ */
