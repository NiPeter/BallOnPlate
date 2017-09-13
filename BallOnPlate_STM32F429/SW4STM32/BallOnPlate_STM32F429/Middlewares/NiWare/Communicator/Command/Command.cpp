/*
 * Command.cpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#include "Command.hpp"


Command::Command(CmdType_e cmd, float param):CmdType(cmd),Param(param)
{
}


Command::~Command()
{
}


CmdType_e Command::getType()
{
	return CmdType;
}


float Command::getParam()
{
	return Param;
}
