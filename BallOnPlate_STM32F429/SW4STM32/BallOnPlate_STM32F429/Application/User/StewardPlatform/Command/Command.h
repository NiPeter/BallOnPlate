/*
 * Command.h
 *
 *  Created on: 19 wrz 2017
 *      Author: Peter
 */

#ifndef COMMAND_H_
#define COMMAND_H_

/*
 *
 */
class Command {
public:

	virtual ~Command(){};
	void Execute(StewardPlatform* platform) = 0;

};

class CommandOk : public Command{

	void Execute(StewardPlatform* platform){
		platform->CommunicationCenter.SendOk();
	}


};
#endif /* COMMAND_H_ */
