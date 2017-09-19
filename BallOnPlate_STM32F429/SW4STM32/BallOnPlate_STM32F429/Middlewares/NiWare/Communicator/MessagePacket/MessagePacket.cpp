/*
 * Command.cpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#include <Communicator/MessagePacket/MessagePacket.hpp>


MessagePacket::MessagePacket(CmdType_e cmd, float param):CmdType(cmd),Param(param)
{
}


MessagePacket::~MessagePacket()
{
}


CmdType_e MessagePacket::GetType()
{
	return CmdType;
}


float MessagePacket::GetParam()
{
	return Param;
}
