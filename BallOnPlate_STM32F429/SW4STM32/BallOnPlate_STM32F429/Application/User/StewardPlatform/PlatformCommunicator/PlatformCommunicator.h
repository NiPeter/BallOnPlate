/*
 * PlatformCommunicator.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef PLATFORMCOMMUNICATOR_H_
#define PLATFORMCOMMUNICATOR_H_

#include <Communicator/Serial/HC05/HC05.hpp>
#include <Communicator/Communicator.hpp>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*
 *
 */
class PlatformCommunicator : public Communicator{
public:
	HC05 		Bluetooth;

	PlatformCommunicator();
	virtual ~PlatformCommunicator();

	void SendEmpty(){
		Command cmd = Command(empty);
		SendCommand(cmd);
	}
	void SendFail(){
		Command cmd = Command(fail);
		SendCommand(cmd);
	}
	void SendOk(){
		Command cmd = Command(ok);
		SendCommand(cmd);
	}

	void UARTRxCpltCallback(UART_HandleTypeDef *huart);
	void UARTTxCpltCallback(UART_HandleTypeDef *huart);

	void TxTask(void const * argument);
	void RxTask(void const * argument);

private:

	osSemaphoreId txSemaphoreHandle;
	osSemaphoreId rxSemaphoreHandle;

};

#endif /* PLATFORMCOMMUNICATOR_H_ */
