/*
 * Objects.hpp
 *
 *  Created on: 13 wrz 2017
 *      Author: Peter
 */

#ifndef OBJECTS_HPP_
#define OBJECTS_HPP_

/********************************************************/

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


#include "../PlatformController/PlatformController.hpp"
#include "../BallControl/DOF.h"

#include "../TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"
#include "../BallControl/Axis.h"

#include "../PID/DiscreteTimePID/DiscreteTimePID.h"

#include "../Communicator/Serial/HC05/HC05.hpp"
#include "../Communicator/Communicator.hpp"

/********************************************************/

extern HC05					Bluetooth;
extern Communicator 		Comm;

extern PlatformController 	Controller;
extern RollDOF 				Roll;
extern PitchDOF 			Pitch;

extern TouchPanel4W 		Panel;

extern XAxis 				XPos;
extern YAxis 				YPos;

extern double kpX,kiX,kdX,nX,kpY,kiY,kdY,nY,dt;

extern DiscreteTimePID XPid;
extern DiscreteTimePID YPid;


#endif /* OBJECTS_HPP_ */
