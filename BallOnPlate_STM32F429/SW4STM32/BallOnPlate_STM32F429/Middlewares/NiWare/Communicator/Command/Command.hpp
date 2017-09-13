/*
 * Command.hpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_COMMUNICATOR_COMMAND_HPP_
#define APPLICATION_USER_COMMUNICATOR_COMMAND_HPP_

#include "CmdType.h"

class Command
{
private:
	CmdType_e CmdType;
	float Param;

public:
	Command(CmdType_e cmd, float param=0);
	~Command();

	CmdType_e getType();
	float getParam();
};

#endif /* APPLICATION_USER_COMMUNICATOR_COMMAND_HPP_ */
