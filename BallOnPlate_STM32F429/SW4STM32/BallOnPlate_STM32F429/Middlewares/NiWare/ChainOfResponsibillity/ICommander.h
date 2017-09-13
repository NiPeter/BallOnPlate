/*
 * ChainOfResponsibillity.h
 *
 *  Created on: Sep 13, 2017
 *      Author: peter
 */

#ifndef MIDDLEWARES_NIWARE_CHAINOFRESPONSIBILLITY_ICOMMANDER_H_
#define MIDDLEWARES_NIWARE_CHAINOFRESPONSIBILLITY_ICOMMANDER_H_



#include "../Communicator/Command/Command.hpp"


class ICommander {

	ICommander &Next;

public:
	virtual ~ICommander() {};

	virtual void Execute(Command cmd) = 0;
	void PassNext(Command cmd){
		Next.Execute(cmd);
	}

};

#endif /* MIDDLEWARES_NIWARE_CHAINOFRESPONSIBILLITY_ICOMMANDER_H_ */
