/*
 * PIDTask.cpp
 *
 *  Created on: 12 wrz 2017
 *      Author: Peter
 */

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "PID/DiscreteTimePID/DiscreteTimePID.h"



extern DiscreteTimePID	XPid;
extern DiscreteTimePID	YPid;



/**
 *
 * @param argument
 */
void StartPIDTask(void const * argument){
	TickType_t xLastWakeTime;
	TickType_t xFrequency = (( XPid.GetTs() + YPid.GetTs() ) * configTICK_RATE_HZ) /2.0;

	xLastWakeTime = xTaskGetTickCount();

	while(true){

		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		XPid.Process();
		YPid.Process();

	}

}
/********************************************************/
