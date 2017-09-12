/*
 * TouchPanelTasks.cpp
 *
 *  Created on: 12 wrz 2017
 *      Author: Peter
 */

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "../TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"


extern TouchPanel4W		Panel;




/**
 *
 * @param argument
 */
void StartTouchPanelTask(void const * argument){
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5;

	xLastWakeTime = xTaskGetTickCount();

	while(true){

		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		Panel.Process();

	}
}
/********************************************************/
