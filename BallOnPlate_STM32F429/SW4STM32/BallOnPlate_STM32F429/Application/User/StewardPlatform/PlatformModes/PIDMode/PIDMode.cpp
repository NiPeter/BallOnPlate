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
	Ready = false;

	Master = master;
	this->Construct();

}
/********************************************************/



/**
 *
 */
void PIDMode::Start() {
	if(!Ready){
		Command Cmd = Command(notReady);
		Master->CommunicationCenter.sendCmd(Cmd);
		return;
	}
	XPid->Start();
	YPid->Start();
}
/********************************************************/



/**
 *
 */
void PIDMode::Stop() {
	if(!Ready){
		Command Cmd = Command(notReady);
		Master->CommunicationCenter.sendCmd(Cmd);
		return;
	}
	XPid->Stop();
	YPid->Stop();
}
/********************************************************/



/**
 *
 */
void PIDMode::Reset() {
	if(!Ready){
		Command Cmd = Command(notReady);
		Master->CommunicationCenter.sendCmd(Cmd);
		return;
	}
	XPid->Reset();
	YPid->Reset();
}
/********************************************************/



/**
 *
 * @param cmd
 */
void PIDMode::Execute(Command cmd) {
	if(!Ready){
		Command Cmd = Command(notReady);
		Master->CommunicationCenter.sendCmd(Cmd);
		return;
	}

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
	static float setpointX = XPid->GetSetpoint();
	static float setpointY = YPid->GetSetpoint();
//		static float setpointX = 0;
//		static float setpointY = 0;

	switch (cmdType) {
		case setSetpointX:
			// store setpoint x
			setpointX = (double)cmdParam;
			break;

		case setSetpointY:
			// store setpoint y
			setpointY = (double)cmdParam;
			break;

		case submit:
			// write setpoints and return normal state
			XPid->SetSetpoint(23+setpointX);
			YPid->SetSetpoint(19+setpointY);
			CommunicationState.State = normal;
			break;

		default:
			// Ups forbidden command, cancel unsubmitted changes
			setpointX = XPid->GetSetpoint();
			setpointY = YPid->GetSetpoint();
			CommunicationState.State = normal;

			Master->CommunicationCenter.SendFail();
			break;
	}


}

void PIDMode::ExecuteSetParamState(Command cmd) {
}

struct PIDMode_AQ{
	double xError;
	double yError;
	double xOutput;
	double yOutput;
}PMode;

/**
 *
 * @param argument
 */
void PIDMode::PIDModeTask(const void* argument) {
	TickType_t 	xLastWakeTime;
	PIDMode*	Mode;

	Mode = (PIDMode*) argument;
	bool previousTouchDetect,touchDetect;

	osDelay(100);
	Mode->Ready = true;

	Mode->XPid->SetDeadband(0.3);
	Mode->YPid->SetDeadband(0.3);

	xLastWakeTime = xTaskGetTickCount();
	while(true){

		vTaskDelayUntil( &xLastWakeTime, Mode->GetSamplingInterval() );

		previousTouchDetect = touchDetect;
		touchDetect = Mode->Master->TouchPanel.IsTouched();

		if( ((previousTouchDetect == true) && (touchDetect == false))  ){
			Mode->XPid->Reset();
			Mode->YPid->Reset();

			Mode->Roll->Set(0);
			Mode->Pitch->Set(0);
			continue;
		}

		if(touchDetect){
			Mode->XPid->Process();
			Mode->YPid->Process();

			PMode.xError = Mode->XPid->GetError();
			PMode.yError = Mode->YPid->GetError();

			PMode.xOutput = Mode->XPid->GetOutput();
			PMode.yOutput = Mode->YPid->GetOutput();


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

	XPidSettings.Kp = 0.045;
	XPidSettings.Ki = 0.01;
	XPidSettings.Kd = 0.02;
	XPidSettings.N = 5;

	YPidSettings.Kp = -XPidSettings.Kp;
	YPidSettings.Ki = -XPidSettings.Ki;
	YPidSettings.Kd = -XPidSettings.Kd;
	YPidSettings.N = XPidSettings.N;



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
