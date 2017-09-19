/*
 * PlatformTouchPanel.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef PLATFORMTOUCHPANEL_H_
#define PLATFORMTOUCHPANEL_H_

#include <TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp>
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"
#include "usart.h"

#ifdef __cplusplus
}
#endif

/*
 *
 */
class PlatformTouchPanel{
	friend class StewardPlatform;

public:

	PlatformTouchPanel(	TickType_t period = 1);
	virtual ~PlatformTouchPanel();

	TickType_t GetSamplingInterval() const {
		return xSamplingInterval;
	}

//	void SetSamplingInterval(TickType_t samplingInterval) {
//		xSamplingInterval = samplingInterval;
//	}

//protected:

	TouchPanel4W TouchPanel;

private:

	TickType_t xSamplingInterval;

	osThreadDef(PlatformTouchPanelTask, TouchPanelTask, osPriorityAboveNormal, 0, 256);
	osThreadId touchPanelTaskHandle;

	static void TouchPanelTask(void const * argument);

	void Construct();
};

#endif /* PLATFORMTOUCHPANEL_H_ */
