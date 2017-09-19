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

		case submit:
			return new CommandSubmit;

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

		case moveTo:
			return new CommandMoveTo();

		case setSetpointX:
			return new CommandSetSetpointX(msg.GetParam());

		case setSetpointY:
			return new CommandSetSetpointY(msg.GetParam());

		case setIkX:
			return new CommandSetIkX(msg.GetParam());

		case setIkY:
			return new CommandSetIkY(msg.GetParam());

		case setIkZ:
			return new CommandSetIkZ(msg.GetParam());

		case setIkRoll:
			return new CommandSetIkRoll(msg.GetParam());

		case setIkPitch:
			return new CommandSetIkPitch(msg.GetParam());

		case setIkYaw:
			return new CommandSetIkYaw(msg.GetParam());


		default:
			return new CommandEmpty;
		}
	}

};

#endif /* COMMANDFACTORY_H_ */
