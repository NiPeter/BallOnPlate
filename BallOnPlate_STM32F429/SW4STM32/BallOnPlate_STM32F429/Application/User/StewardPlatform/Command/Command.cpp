/*
 * Command.cpp
 *
 *  Created on: Sep 19, 2017
 *      Author: peter
 */

#include "Command.h"

StateHandler Command::stateHandler{
			normalState,
			none,
			{ 0, 0, 0, 0, 0, 0},
			NULL,
	};
