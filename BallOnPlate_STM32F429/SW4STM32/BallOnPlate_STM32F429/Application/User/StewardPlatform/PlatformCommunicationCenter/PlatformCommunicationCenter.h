/*
 * PlatformCommunicator.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef PLATFORMCOMMUNICATIONCENTER_H_
#define PLATFORMCOMMUNICATIONCENTER_H_

#include <Communicator/Serial/HC05/HC05.hpp>
#include <Communicator/Communicator.hpp>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*
 *
 */
class PlatformCommunicationCenter{
public:

	PlatformCommunicationCenter();
	virtual ~PlatformCommunicationCenter();

	void SendEmpty(){
		MessagePacket cmd = MessagePacket(empty);
		Comm.SendPacket(cmd);
	}
	void SendFail(){
		MessagePacket cmd = MessagePacket(fail);
		Comm.SendPacket(cmd);
	}
	void SendOk(){
		MessagePacket cmd = MessagePacket(ok);
		Comm.SendPacket(cmd);
	}

	void StartBroadcast(){
		Bluetooth.begin();
	}

	void UARTRxCpltCallback(UART_HandleTypeDef *huart);
	void UARTTxCpltCallback(UART_HandleTypeDef *huart);

//private:

	HC05 		Bluetooth;
	Communicator	Comm;

	osThreadDef(CommCenterRxTask, RxTask, osPriorityRealtime, 0, 128);
	osThreadDef(CommCenterTxTask, TxTask, osPriorityRealtime, 0, 128);

	osThreadId rxTaskHandle;
	osThreadId txTaskHandle;
	osSemaphoreId txSemaphoreHandle;
	osSemaphoreId rxSemaphoreHandle;

	static void TxTask(void const * argument);
	static void RxTask(void const * argument);

};

#endif /* PLATFORMCOMMUNICATIONCENTER_H_ */
