/*
 * PIDMode.cpp
 *
 *  Created on: 17 wrz 2017
 *      Author: Peter
 */

#include "PIDMode.h"
#include "../../StewardPlatform.h"

PIDMode::~PIDMode() {

	delete XPos;
	delete YPos;
	delete Roll;
	delete Pitch;

	delete XPid;
	delete YPid;

	osThreadTerminate(pidTaskHandle);
}


PIDMode::PIDMode(StewardPlatform* master, TickType_t samplingInterval_ms)
: xSamplingInterval(samplingInterval_ms){

	Master = master;
	this->Construct();

}

void PIDMode::Start() {
	XPid->Start();
	YPid->Start();
}

void PIDMode::Stop() {
}

void PIDMode::Reset() {
}

void PIDMode::Execute(Command cmd) {
}

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
				pidMode->XPid->Reset();
				pidMode->XPid->Reset();
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

inline void PIDMode::Construct() {

	XPidSettings.Kp = 0.02;
	XPidSettings.Ki = 0.00;
	XPidSettings.Kd = 0.06;
	XPidSettings.N = 8;
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
