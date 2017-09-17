/*
 * PlatformTouchPanel.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "../../StewardPlatform/PlatformTouchPanel/PlatformTouchPanel.h"

PlatformTouchPanel::PlatformTouchPanel(	TickType_t period)
	:TouchPanel4W(	new AnalogPin(&hadc3,PF6_GPIO_Port,PF6_Pin), 	// XAnalog
					new Pin(PE2_GPIO_Port,PE2_Pin),					//XGnd
					new AnalogPin(&hadc1,PC3_GPIO_Port,PC3_Pin),	//YAnalog
					new Pin(PE4_GPIO_Port,PE4_Pin)),
					xSamplingInterval(period){				//YGnd
	Construct();
}

PlatformTouchPanel::~PlatformTouchPanel() {
	delete XAnalog;
	delete YAnalog;
	delete XGnd;
	delete YGnd;
}

void PlatformTouchPanel::Construct() {


}

void PlatformTouchPanel::TouchPanelTask(const void* argument) {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	while(true){

		vTaskDelayUntil( &xLastWakeTime, xSamplingInterval );
		Process();

	}
}

