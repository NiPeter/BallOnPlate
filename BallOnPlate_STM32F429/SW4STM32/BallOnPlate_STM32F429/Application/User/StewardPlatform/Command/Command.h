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


	typedef struct{
		float X;
		float Y;
		float Z;
		float Roll;
		float Pitch;
		float Yaw;
	}DesiredPos;

	typedef enum{
		normalState,
		moveToState,
		setPosState,
		setParameterState,

	}State_e;

	typedef struct {
		State_e 			State;
		ModeType_e			Mode;
		DesiredPos			Pos;
		DiscreteTimePID*	selectedPid;
	}StateHandler;


/*
 *
 */
class Command {
public:



//protected:


	static StateHandler stateHandler;


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
