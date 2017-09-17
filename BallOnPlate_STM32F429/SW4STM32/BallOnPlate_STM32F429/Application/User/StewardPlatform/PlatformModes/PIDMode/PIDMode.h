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

	typedef enum{
		normal,
		setSetpoint,
		setParameter,
	}State_e;

public:

	~PIDMode();
	PIDMode(StewardPlatform* master,TickType_t samplingInterval_ms = 5);

	void Start();
	void Stop();
	void Reset();

	void Execute(Command cmd);

	TickType_t GetSamplingInterval() const {
		return xSamplingInterval;
	}

	static void PIDModeTask(void const * argument);

private:

	osThreadId pidTaskHandle;
	TickType_t xSamplingInterval;

	pidSettings XPidSettings,YPidSettings;

	XAxis 				*XPos;
	YAxis 				*YPos;
	RollDOF 			*Roll;
	PitchDOF 			*Pitch;

	DiscreteTimePID* XPid;
	DiscreteTimePID* YPid;


	struct{
		State_e 			State;
		DiscreteTimePID*	selectedPid;
	}CommunicationState;


	void ExecuteNormalState(Command cmd);
	void ExecuteSetSetpointState(Command cmd);
	void ExecuteSetParamState(Command cmd);

	bool isSetpointCommandType(CmdType_e cmdType){
		return isCommandTypeInRange(cmdType,setSetpointX,setSetpointY);
	}

	bool isSetParameterCommandType(CmdType_e cmdType){
		return isCommandTypeInRange(cmdType,setPidSamplingInterval,setPidDeadband);
	}

	inline void Construct();

};

#endif /* PIDMODE_H_ */
