/*
 * PIDMode.cpp
 *
 *  Created on: 17 wrz 2017
 *      Author: Peter
 */

#include "PIDMode.h"
#include "../../StewardPlatform.h"


/**
 *
 */
PIDMode::~PIDMode() {

	Stop();

	osThreadTerminate(pidTaskHandle);

	delete XPos;
	delete YPos;
	delete Roll;
	delete Pitch;

	delete XPid;
	delete YPid;
}
/********************************************************/



/**
 *
 * @param master
 * @param samplingInterval_ms
 */
PIDMode::PIDMode(StewardPlatform* master, TickType_t samplingInterval_ms)
: xSamplingInterval(samplingInterval_ms){

	Master = master;
	this->Construct();

}
/********************************************************/



/**
 *
 */
void PIDMode::Start() {
	XPid->Start();
	YPid->Start();
}
/********************************************************/



/**
 *
 */
void PIDMode::Stop() {
	XPid->Stop();
	YPid->Stop();
}
/********************************************************/



/**
 *
 */
void PIDMode::Reset() {
}
/********************************************************/



/**
 *
 * @param cmd
 */
void PIDMode::Execute(Command cmd) {

	switch(CommunicationState.State){

	case normal:
		ExecuteNormalState(cmd);
		break;

	case setSetpoint:
		ExecuteSetSetpointState(cmd);
		break;

	case setParameter:
		ExecuteSetParamState(cmd);
		break;

	}
}
/********************************************************/


void PIDMode::ExecuteNormalState(Command cmd) {
	CmdType_e 	cmdType = cmd.getType();
	float		cmdParam = cmd.getParam();

	switch (cmdType) { // Only two commands accepted

	case moveTo:
		CommunicationState.State = setSetpoint;
		break;

	case selectPid:{

		CommunicationState.State = setParameter;
		PidSelect_e pid = (PidSelect_e)cmdParam;

		if( pid == selectPidX) {
			CommunicationState.selectedPid = XPid;
			return;
		}
		else if ( pid == selectPidY ){
			CommunicationState.selectedPid = YPid;
			return;
		}
		else {
			// Wrong command parameter, return to normal state
			CommunicationState.State = normal;
			Master->CommunicationCenter.SendFail();
			return;
		}
		break;
	}
	default:
		// Not recognized command
		Master->CommunicationCenter.SendEmpty();
		break;
	}
}

void PIDMode::ExecuteSetSetpointState(Command cmd) {
	CmdType_e 	cmdType = cmd.getType();
	float		cmdParam = cmd.getParam();

	// At first, remember setpoints
//	static float setpointX = XPid->GetSetpoint();
//	static float setpointY = YPid->GetSetpoint();
		static float setpointX = 0;
		static float setpointY = 0;

	switch (cmdType) {
		case setSetpointX:
			// store setpoint x
			setpointX = (double)cmdParam;
			XPid->SetSetpoint(23+setpointX);

//			Master->CommunicationCenter.sendCmd(cmd);
			break;

		case setSetpointY:
			// store setpoint y
			setpointY = (double)cmdParam;
			YPid->SetSetpoint(19+setpointY);
//			Master->CommunicationCenter.sendCmd(cmd);
			break;

		case submit:
			// write setpoints and return normal state

			CommunicationState.State = normal;
//			Master->CommunicationCenter.sendCmd(cmd);

			break;

		default:
			// Ups forbidden command, cancel unsubmitted changes
//			setpointX = XPid->GetSetpoint();
//			setpointY = YPid->GetSetpoint();
			CommunicationState.State = normal;

			Master->CommunicationCenter.SendFail();
			break;
	}


}

void PIDMode::ExecuteSetParamState(Command cmd) {
}


/**
 *
 * @param argument
 */
void PIDMode::PIDModeTask(const void* argument) {
	TickType_t 	xLastWakeTime;
	PIDMode*	pidMode;

	pidMode = (PIDMode*) argument;
	bool previousTouchDetect,touchDetect;

	pidMode->XPid->SetDeadband(0.3);
	pidMode->YPid->SetDeadband(0.3);

	xLastWakeTime = xTaskGetTickCount();
	while(true){

		vTaskDelayUntil( &xLastWakeTime, pidMode->GetSamplingInterval() );

		previousTouchDetect = touchDetect;
		touchDetect = pidMode->Master->TouchPanel.IsTouched();

		if( ((previousTouchDetect == true) && (touchDetect == false))  ){
//			pidMode->XPid->Reset();
//			pidMode->XPid->Reset();
			pidMode->XPid->Stop();
			pidMode->XPid->Stop();

			pidMode->Roll->Set(0);
			pidMode->Pitch->Set(0);
			continue;
		}

		if(touchDetect){
			pidMode->YPid->Start();
			pidMode->XPid->Start();
			pidMode->XPid->Process();
			pidMode->YPid->Process();
		}
	}

}
/********************************************************/



/**
 *
 */
inline void PIDMode::Construct() {

	CommunicationState.State = normal;
	CommunicationState.selectedPid = NULL;

	XPidSettings.Kp = 0.04;
	XPidSettings.Ki = 0.00;
	XPidSettings.Kd = 0.01;
	XPidSettings.N = 10;
	YPidSettings = XPidSettings;


	XPos = new XAxis(Master->TouchPanel);
	YPos = new YAxis(Master->TouchPanel);
	Roll = new RollDOF(Master->Platform.Controller);
	Pitch= new PitchDOF(Master->Platform.Controller);


	XPid = new DiscreteTimePID(&XPidSettings,xSamplingInterval/(double)1000.0,XPos,Pitch);
	YPid = new DiscreteTimePID(&YPidSettings,xSamplingInterval/(double)1000.0,YPos,Roll);

	/* definition and creation of pidTask */
	osThreadDef(PIDTask, PIDModeTask, osPriorityAboveNormal, 0, 256);
	pidTaskHandle = osThreadCreate(osThread(PIDTask), this);

}
/********************************************************/
