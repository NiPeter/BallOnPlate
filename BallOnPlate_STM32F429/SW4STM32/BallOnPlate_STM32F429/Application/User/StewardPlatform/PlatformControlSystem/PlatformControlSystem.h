/*
 * StewardPlatform.h
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#ifndef PLATFORMCONTROLSYSTEM_H_
#define PLATFORMCONTROLSYSTEM_H_

#include <IKController/IKController.hpp>
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
class PlatformControlSystem{
public:
	Steward_Struct 			StewardConfig;
	Servo					Servos[6];
	IKController			Controller;

	PlatformControlSystem();
	~PlatformControlSystem();

private:
	void Construct();
	void ConfigConstruct();
	void ServosConstruct();

};

#endif /* PLATFORMCONTROLSYSTEM_H_ */
