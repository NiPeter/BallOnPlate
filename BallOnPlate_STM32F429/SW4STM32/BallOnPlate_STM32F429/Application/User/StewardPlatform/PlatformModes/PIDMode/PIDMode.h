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

public:

	~PIDMode();
	PIDMode(StewardPlatform* master,TickType_t samplingInterval_ms = 5);

	void Start();
	void Stop();
	void Reset();

	void Execute(Command cmd);

	static void PIDModeTask(void const * argument);

	TickType_t GetSamplingInterval() const {
		return xSamplingInterval;
	}

//	void SetSamplingInterval(TickType_t samplingInterval) {
//		xSamplingInterval = samplingInterval;
//	}

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

	inline void Construct();
};

#endif /* PIDMODE_H_ */
