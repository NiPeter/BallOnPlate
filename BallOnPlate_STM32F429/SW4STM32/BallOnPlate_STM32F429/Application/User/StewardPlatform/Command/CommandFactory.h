/*
 * CommandFactory.h
 *
 *  Created on: 19 wrz 2017
 *      Author: Peter
 */

#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

#include "CommandInclude.h"

class CommandFactory{
public:

	static Command* GetCommand(MessagePacket msg){

		switch(msg.GetType()){

		case empty:
			return new CommandEmpty;

		case fail:
			return new CommandFail;

		case ok:
			return new CommandOk;

		case submit: //TODO
			return new CommandEmpty;

		case cancel: //TODO
			return new CommandEmpty;

		case startMode:
			return new CommandStartMode;

		case stopMode:
			return new CommandStopMode;

		case resetMode:
			return new CommandResetMode;

		case setMode:
			return new CommandSetMode((ModeType_e) msg.GetParam());

		default:
			return new CommandEmpty;
		}
	}

};

#endif /* COMMANDFACTORY_H_ */
