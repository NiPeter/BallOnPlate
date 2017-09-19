/*
 * Master.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "StewardPlatform.h"


#include "Command/CommandFactory.h"
#include "Command/CommandInclude.h"


/**
 *
 */
StewardPlatform::StewardPlatform() {

	Mode = NULL;
	CommunicationCenter.StartBroadcast();

	/* creation of communicationTask */
	communicationTaskHandle = osThreadCreate(osThread(StewardPlatformCommunicationTask), this);
}
/********************************************************/



/**
 *
 */
StewardPlatform::~StewardPlatform() {
	delete Mode;

	osThreadTerminate(communicationTaskHandle);

}



/**
 *
 * @param modeType
 */
void StewardPlatform::SetMode(ModeType_e modeType) {
	if(Mode){
		delete Mode;
		Mode = NULL;
	}

	switch(modeType){

	case pidMode:
		Mode = new PIDMode(this);
		break;

	case ikMode:
		Mode = new IKMode(&this->PlatformSystem.Controller);
		break;

	default:
		break;
	}

}
/********************************************************/



/**
 *
 */
void StewardPlatform::Construct() {


}
/********************************************************/



/**
 *
 * @param cmd
 */
void StewardPlatform::Execute(MessagePacket cmd) {

//	switch(cmd.GetType()){
//	case empty:
//		CommunicationCenter.SendEmpty();
//		break;
//
//	case fail:
//		break;
//
//	case ok:
//		break;
//
//	case startMode:
//		if(Mode) Mode->Start();
//			else CommunicationCenter.SendFail();
//		break;
//
//	case stopMode:
//		if(Mode) Mode->Stop();
//			else CommunicationCenter.SendFail();
//		break;
//
//	case resetMode:
//		if(Mode) Mode->Reset();
//			else CommunicationCenter.SendFail();
//		break;
//
//	case setMode:
//		SetMode((ModeType_e)cmd.GetParam());
//		break;
//
//	default:
//		if(Mode) Mode->Execute(cmd);
//			else CommunicationCenter.SendFail();
//		break;
//
//	}
}
/********************************************************/



/**
 *
 * @param argument
 */
void StewardPlatform::CommunicationTask(const void* argument) {
	StewardPlatform* stewardPlatform = (StewardPlatform*)argument;
	PlatformCommunicationCenter* communicationCenter = &stewardPlatform->CommunicationCenter;


	while(true){
		bool isPacket = false;

		MessagePacket packet = communicationCenter->Comm.ReceivePacket(&isPacket);
		if(isPacket){

			communicationCenter->Comm.SendPacket(packet);

			Command* cmd = CommandFactory::GetCommand(packet);
			cmd -> Execute(stewardPlatform);

		}else
		osDelay(10);

	}
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
