/*
 * TouchPanelTasks.cpp
 *
 *  Created on: 12 wrz 2017
 *      Author: Peter
 */

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "../StewardPlatform/StewardPlatform.h"

extern StewardPlatform* master;




/**
 *
 * @param argument
 */
void StartTouchPanelTask(void const * argument){
	master->TouchPanelTask(argument);
}
/********************************************************/
