/*
 * Command.h
 *
 *  Created on: 19 wrz 2017
 *      Author: Peter
 */

#ifndef GENERALCOMMAND_H_
#define GENERALCOMMAND_H_

#include "Command.h"

class CommandEmpty : public Command{
	void Execute(StewardPlatform* platform){
		platform->CommunicationCenter.SendEmpty();
		selfDelete();
	}
};

class CommandOk : public Command{

	void Execute(StewardPlatform* platform){
		platform->CommunicationCenter.SendOk();
		selfDelete();
	}
};

class CommandFail : public Command{

	void Execute(StewardPlatform* platform){
		platform->CommunicationCenter.SendFail();
		selfDelete();
	}
};

class CommandSubmit : public Command{

	void Execute(StewardPlatform* platform){
		platform->CommunicationCenter.SendPacket(MessagePacket(submit));
		selfDelete();
	}
};

class CommandStartMode : public Command{

	void Execute(StewardPlatform* platform){
		if(platform->Mode) platform->Mode->Start();
		else platform->CommunicationCenter.SendFail();
		selfDelete();
	}

};

class CommandStopMode : public Command{
	void Execute(StewardPlatform* platform){
		if(platform->Mode) platform->Mode->Stop();
		else platform->CommunicationCenter.SendFail();
		selfDelete();
	}
};

class CommandResetMode : public Command{

	void Execute(StewardPlatform* platform){
		if(platform->Mode) platform->Mode->Reset();
		else platform->CommunicationCenter.SendFail();
		selfDelete();
	}

};

class CommandSetMode : public Command{

	ModeType_e ModeType;

public:
	CommandSetMode( ModeType_e modeType ) : ModeType(modeType) {};

	void Execute(StewardPlatform* platform){
		platform->SetMode(ModeType);
		selfDelete();
	}
};


#endif /* GENERALCOMMAND_H_ */
