/*
 * Communicator.hpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_COMMUNICATOR_COMMUNICATOR_HPP_
#define APPLICATION_USER_COMMUNICATOR_COMMUNICATOR_HPP_

#include <Communicator/MessagePacket/MessagePacket.hpp>
#include "Serial/Serial.hpp"

#include "stdlib.h"

char * ftostr(float num, char * str);

class Communicator
{
protected:
	static const char CP_MSG_SIZE = 30;
	Serial* SerialPort;

public:

	Communicator(Serial* serial);
	Communicator(){SerialPort = NULL;};
	~Communicator();

	MessagePacket ReceivePacket(bool *cmdReceived = NULL);
	void SendPacket(MessagePacket packet);

private:
	MessagePacket unpackMsg(const char* msg);
	char*  packMsg(MessagePacket packet, char * msg);

	CmdType_e cmdTypeFromMsg(const char* msg);
	float paramFromMsg(const char* msg);
};


#endif /* APPLICATION_USER_COMMUNICATOR_COMMUNICATOR_HPP_ */
