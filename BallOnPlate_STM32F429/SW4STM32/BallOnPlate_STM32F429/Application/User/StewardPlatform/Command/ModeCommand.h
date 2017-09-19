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



#endif /* APPLICATION_USER_STEWARDPLATFORM_COMMAND_MODECOMMAND_H_ */
