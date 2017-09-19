/*
 * PlatformTouchPanel.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "../../StewardPlatform/PlatformTouchPanel/PlatformTouchPanel.h"

PlatformTouchPanel::PlatformTouchPanel(	TickType_t period)
	:TouchPanel( 	new AnalogPin(&hadc3,PF6_GPIO_Port,PF6_Pin), 	// XAnalog
					new Pin(PE2_GPIO_Port,PE2_Pin),					//XGnd
					new AnalogPin(&hadc1,PC3_GPIO_Port,PC3_Pin),	//YAnalog
					new Pin(PE4_GPIO_Port,PE4_Pin)) ,
					xSamplingInterval(period){				//YGnd
	Construct();
}

PlatformTouchPanel::~PlatformTouchPanel() {
	osThreadTerminate(touchPanelTaskHandle);

	delete TouchPanel.GetXAnalog();
	delete TouchPanel.GetYAnalog();
	delete TouchPanel.GetXGnd();
	delete TouchPanel.GetYGnd();
}

void PlatformTouchPanel::Construct() {

	/* creation of touchPanelTask */
	touchPanelTaskHandle = osThreadCreate(osThread(PlatformTouchPanelTask), this);

}

void PlatformTouchPanel::TouchPanelTask(const void* argument) {
	PlatformTouchPanel* touchPanel;
	TickType_t xLastWakeTime;

	touchPanel = (PlatformTouchPanel*) argument;
	xLastWakeTime = xTaskGetTickCount();
	while(true){

		vTaskDelayUntil( &xLastWakeTime, touchPanel->xSamplingInterval );
		touchPanel->TouchPanel.Process();

	}
}

