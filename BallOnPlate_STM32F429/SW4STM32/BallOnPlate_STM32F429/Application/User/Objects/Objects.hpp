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


#include <IKController/IKController.hpp>

#include "TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"


#include "PID/DiscreteTimePID/DiscreteTimePID.h"

#include "Communicator/Serial/HC05/HC05.hpp"
#include "Communicator/Communicator.hpp"

/********************************************************/


//
//extern double kpX,kiX,kdX,nX,kpY,kiY,kdY,nY,dt;
//
//extern DiscreteTimePID* XPid;
//extern DiscreteTimePID* YPid;


#endif /* OBJECTS_HPP_ */
