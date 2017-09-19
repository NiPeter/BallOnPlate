/*
 * Command.hpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_COMMUNICATOR_COMMAND_HPP_
#define APPLICATION_USER_COMMUNICATOR_COMMAND_HPP_

#include <Communicator/MessagePacket/CmdType.h>

class MessagePacket
{
private:
	CmdType_e CmdType;
	float Param;

public:
	MessagePacket(CmdType_e cmd, float param=0);
	~MessagePacket();

	CmdType_e GetType();
	float GetParam();
};

#endif /* APPLICATION_USER_COMMUNICATOR_COMMAND_HPP_ */
