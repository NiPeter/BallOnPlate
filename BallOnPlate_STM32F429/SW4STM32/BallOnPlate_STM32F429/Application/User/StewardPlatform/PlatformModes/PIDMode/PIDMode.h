/*
 * PIDMode.h
 *
 *  Created on: 17 wrz 2017
 *      Author: Peter
 */

#ifndef PIDMODE_H_
#define PIDMODE_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "../PlatformMode.h"
#include "BallControl/Axis.h"
#include "BallControl/DOF.h"
#include <PID/DiscreteTimePID/DiscreteTimePID.h>

/*
 *
 */
class PIDMode: public PlatformMode {
	friend class CommandSubmit;

public:

	~PIDMode();
	PIDMode(StewardPlatform* master,TickType_t samplingInterval_ms = 5);

	void Start();
	void Stop();
	void Reset();

//	void Execute(MessagePacket cmd);

	TickType_t GetSamplingInterval() const {
		return xSamplingInterval;
	}

	static void PIDModeTask(void const * argument);

private:
	StewardPlatform* Master;

	osThreadId pidTaskHandle;
	TickType_t xSamplingInterval;

	pidSettings XPidSettings,YPidSettings;

	/* definition and creation of pidTask */
	osThreadDef(PIDTask, PIDModeTask, osPriorityAboveNormal, 0, 512);

	XAxis 				*XPos;
	YAxis 				*YPos;
	RollDOF 			*Roll;
	PitchDOF 			*Pitch;

	DiscreteTimePID* XPid;
	DiscreteTimePID* YPid;





	bool isSetpointCommandType(CmdType_e cmdType){
		return isCommandTypeInRange(cmdType,setSetpointX,setSetpointY);
	}

	bool isSetParameterCommandType(CmdType_e cmdType){
		return isCommandTypeInRange(cmdType,setPidSamplingInterval,setPidDeadband);
	}

	void Construct();

};

#endif /* PIDMODE_H_ */
