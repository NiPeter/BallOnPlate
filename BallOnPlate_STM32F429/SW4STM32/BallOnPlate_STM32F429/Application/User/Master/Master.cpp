/*
 * Master.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "Master.h"

Master::Master() {

	this->Construct();

}

Master::~Master() {

}

void Master::Construct() {


}

void Master::Execute(Command cmd) {
}

void Master::TxTask(const void* argument) {
	Communicator.TxTask(argument);
}


void Master::RxTask(const void* argument) {
	Communicator.RxTask(argument);
}

void Master::UARTRxCpltCallback(UART_HandleTypeDef* huart) {
	Communicator.UARTRxCpltCallback(huart);
}

void Master::UARTTxCpltCallback(UART_HandleTypeDef* huart) {
	Communicator.UARTTxCpltCallback(huart);
}

void Master::TouchPanelTask(const void* argument) {
	Panel.TouchPanelTask(argument);
}
