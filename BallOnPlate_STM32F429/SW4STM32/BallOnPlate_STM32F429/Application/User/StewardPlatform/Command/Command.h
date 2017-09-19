/*
 * Command.h
 *
 *  Created on: 19 wrz 2017
 *      Author: Peter
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "../StewardPlatform.h"
#include <Communicator/MessagePacket/CmdType.h>


/*
 *
 */
class Command {

protected:

	void selfDelete(){
		delete this;
	}

public:

	virtual ~Command(){
//		selfDelete();
	};
	virtual void Execute(StewardPlatform* platform) = 0;

};

#endif /* COMMAND_H_ */
