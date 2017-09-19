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



//TODO REFACTOR
class CommandSubmit : public Command{

	void Execute(StewardPlatform* platform){

		switch( stateHandler.Mode ){

		case none:
			platform->CommunicationCenter.SendEmpty();
			break;

		case pidMode:
			if(platform->Mode){

				PIDMode* pidmode = reinterpret_cast<PIDMode*> (platform->Mode);//dynamic_cast<PIDMode*> (platform->Mode);
				if(pidmode){

					switch(stateHandler.State){
					case moveToState:
						pidmode->XPid->SetSetpoint(stateHandler.Pos.X);
						pidmode->YPid->SetSetpoint(stateHandler.Pos.Y);
						break;

					case setParameterState:
						break;

					default:
						platform->CommunicationCenter.SendEmpty();
						break;
					}

				} else platform->CommunicationCenter.SendFail();


			} else platform->CommunicationCenter.SendFail();
			break;

		case ikMode:
			if(platform->Mode){

				IKMode* ikmode = reinterpret_cast<IKMode*> (platform->Mode);//dynamic_cast<PIDMode*> (platform->Mode);
				if(ikmode){

					switch(stateHandler.State){
					case moveToState:
						ikmode->MoveTo(stateHandler.Pos.X,stateHandler.Pos.Y,stateHandler.Pos.Z,
								stateHandler.Pos.Roll,stateHandler.Pos.Pitch,stateHandler.Pos.Yaw);
						break;

					case setParameterState:
						break;

					default:
						platform->CommunicationCenter.SendEmpty();
						break;
					}

				} else platform->CommunicationCenter.SendFail();


			} else platform->CommunicationCenter.SendFail();
			break;

		default:
			platform->CommunicationCenter.SendEmpty();
			break;
		}

		stateHandler.State = normalState;

		selfDelete();
	}
};



class CommandStartMode : public Command{

	void Execute(StewardPlatform* platform){
		if(platform->Mode)
			platform->Mode->Start();
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}

};



class CommandStopMode : public Command{

	void Execute(StewardPlatform* platform){
		if(platform->Mode)
			platform->Mode->Stop();
		else platform->CommunicationCenter.SendFail();

		selfDelete();
	}
};



class CommandResetMode : public Command{

	void Execute(StewardPlatform* platform){
		if(platform->Mode)
			platform->Mode->Reset();
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

		stateHandler.State = normalState;
		stateHandler.Mode = ModeType;

		stateHandler.Pos.X = 0;
		stateHandler.Pos.Y = 0;
		stateHandler.Pos.Z = 0;
		stateHandler.Pos.Roll = 0;
		stateHandler.Pos.Pitch = 0;
		stateHandler.Pos.Yaw = 0;


		selfDelete();
	}
};


#endif /* GENERALCOMMAND_H_ */
