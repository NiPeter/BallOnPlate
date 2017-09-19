/*
 * BoPModeCommand.h
 *
 *  Created on: Sep 19, 2017
 *      Author: peter
 */

#ifndef APPLICATION_USER_STEWARDPLATFORM_COMMAND_MODECOMMAND_H_
#define APPLICATION_USER_STEWARDPLATFORM_COMMAND_MODECOMMAND_H_


#include "Command.h"




class CommandMoveTo : public Command{
	void Execute(StewardPlatform* platform){

		if(platform->Mode) {

			if(stateHandler.State == normalState){

				if( platform->Mode->IsMovable() )
					stateHandler.State = moveToState;
				else platform->CommunicationCenter.SendFail();

			}else {
				stateHandler.State = normalState;
				platform->CommunicationCenter.SendFail();
			}


		}else platform->CommunicationCenter.SendFail();


		selfDelete();
	}
};



class PosSetterCommand : public Command{
protected:

	float PosParam;

public:

	PosSetterCommand(float posParam) : PosParam(posParam) {};

};



class CommandSetSetpointX : public PosSetterCommand{

public:

	CommandSetSetpointX(float x) : PosSetterCommand(x) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.X = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}
};



class CommandSetSetpointY : public PosSetterCommand{

public:

	CommandSetSetpointY(float y) :  PosSetterCommand(y) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.Y = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}
};




class CommandSetIkX : public PosSetterCommand{

public:

	CommandSetIkX(float x) : PosSetterCommand(x) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.X = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};

class CommandSetIkY : public PosSetterCommand{

public:

	CommandSetIkY(float y) : PosSetterCommand(y) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.Y = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};

class CommandSetIkZ : public PosSetterCommand{

public:

	CommandSetIkZ(float z) : PosSetterCommand(z) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.Z = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};

class CommandSetIkRoll : public PosSetterCommand{

public:

	CommandSetIkRoll(float roll) : PosSetterCommand(roll) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.Roll = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};

class CommandSetIkPitch : public PosSetterCommand{

public:

	CommandSetIkPitch(float pitch) : PosSetterCommand(pitch) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.Pitch = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};

class CommandSetIkYaw : public PosSetterCommand{

public:

	CommandSetIkYaw(float yaw) : PosSetterCommand(yaw) {};

	void Execute(StewardPlatform* platform){
		if(stateHandler.State == moveToState)
			stateHandler.Pos.Yaw = PosParam;
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};


#endif /* APPLICATION_USER_STEWARDPLATFORM_COMMAND_MODECOMMAND_H_ */
