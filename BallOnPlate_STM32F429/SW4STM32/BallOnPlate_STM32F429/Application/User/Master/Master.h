/*
 * Master.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef MASTER_H_
#define MASTER_H_

#include "PlatformControlSystem/PlatformControlSystem.h"
#include "PlatformTouchPanel/PlatformTouchPanel.h"
#include "PlatformCommunicator/PlatformCommunicator.h"


/**
 *
 */
class Master {

public:
	Master();
	virtual ~Master();

	void Execute(Command cmd);



	void TouchPanelTask(void const * argument);

	void TxTask(void const * argument);
	void RxTask(void const * argument);
	void UARTRxCpltCallback(UART_HandleTypeDef *huart);
	void UARTTxCpltCallback(UART_HandleTypeDef *huart);

public:

	PlatformControlSystem		Platform;
	PlatformTouchPanel			Panel;
	PlatformCommunicator		Communicator;

	//IMode&

	void Construct();

};

#endif /* MASTER_H_ */
