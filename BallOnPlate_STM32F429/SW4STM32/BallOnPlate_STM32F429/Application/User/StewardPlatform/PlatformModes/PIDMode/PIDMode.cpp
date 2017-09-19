/*
 * PIDMode.cpp
 *
 *  Created on: 17 wrz 2017
 *      Author: Peter
 */

#include "PIDMode.h"
#include "../../StewardPlatform.h"
#include "cpu_utils.h"


/**
 *
 */
PIDMode::~PIDMode() {

	Stop();

	osThreadTerminate(pidTaskHandle);

	delete XPid;
	delete YPid;

	delete XPos;
	delete YPos;
	delete Roll;
	delete Pitch;
}
/********************************************************/



/**
 *
 * @param master
 * @param samplingInterval_ms
 */
PIDMode::PIDMode(StewardPlatform* master, TickType_t samplingInterval_ms)
: xSamplingInterval(samplingInterval_ms){

	movable = true;

	Master = master;
	this->Construct();

	Master->PlatformSystem.Controller.Start();

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

	XPid->Reset();
	YPid->Reset();
}
/********************************************************/



/**
 *
 * @param cmd
 */
//void PIDMode::Execute(MessagePacket cmd) {
//
//	switch(CommunicationState.State){
//
//	case normal:
//		ExecuteNormalState(cmd);
//		break;
//
//	case setSetpoint:
//		ExecuteSetSetpointState(cmd);
//		break;
//
//	case setParameter:
//		ExecuteSetParamState(cmd);
//		break;
//
//	}
//}
/********************************************************/




//TODO Achtung Aqusition!
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

	xLastWakeTime = xTaskGetTickCount();

	bool previousTouchDetect,touchDetect;
	while(true){
		extern float cpuUsage;
		extern float osGetCPUUsage();
		cpuUsage = osGetCPUUsage();

		vTaskDelayUntil( &xLastWakeTime, Mode->GetSamplingInterval() );

		previousTouchDetect = touchDetect;
		touchDetect = Mode->Master->TouchPanelSystem.TouchPanel.IsTouched();

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
void PIDMode::Construct() {


//	XPidSettings.Kp = 0.04;
//	XPidSettings.Ki = 0.02;
//	XPidSettings.Kd = 0.035;
//	XPidSettings.N = 10;

		XPidSettings.Kp = 0.035;
		XPidSettings.Ki = 0.013;
		XPidSettings.Kd = 0.065;
		XPidSettings.N = 8;

	YPidSettings.Kp = -XPidSettings.Kp;
	YPidSettings.Ki = -XPidSettings.Ki;
	YPidSettings.Kd = -XPidSettings.Kd;
	YPidSettings.N = XPidSettings.N;



	XPos = new XAxis(Master->TouchPanelSystem.TouchPanel);
	YPos = new YAxis(Master->TouchPanelSystem.TouchPanel);
	Roll = new RollDOF(Master->PlatformSystem.Controller);
	Pitch= new PitchDOF(Master->PlatformSystem.Controller);


	XPid = new DiscreteTimePID(&XPidSettings,xSamplingInterval/(double)1000.0,XPos,Pitch);
	YPid = new DiscreteTimePID(&YPidSettings,xSamplingInterval/(double)1000.0,YPos,Roll);

	pidTaskHandle = osThreadCreate(osThread(PIDTask), this);

}
/********************************************************/
