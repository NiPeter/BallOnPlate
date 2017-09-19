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
#include <Communicator/MessagePacket/CmdType.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*
 *
 */
class PlatformCommunicationCenter{
	friend class StewardPlatform;
public:

	PlatformCommunicationCenter();
	virtual ~PlatformCommunicationCenter();

	void SendEmpty(){
		MessagePacket msg = MessagePacket(empty);
		SendPacket(msg);
	}
	void SendFail(){
		MessagePacket msg = MessagePacket(fail);
		SendPacket(msg);
	}
	void SendOk(){
		MessagePacket msg = MessagePacket(ok);
		SendPacket(msg);
	}

	void SendPacket(MessagePacket packet){
		Comm.SendPacket(packet);
	}

	void StartBroadcast(){
		Bluetooth.begin();
	}

	void UARTRxCpltCallback(UART_HandleTypeDef *huart);
	void UARTTxCpltCallback(UART_HandleTypeDef *huart);

protected:

	HC05 		Bluetooth;
	Communicator	Comm;

private:

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
