/*
 * PIDCommander.h
 *
 *  Created on: Sep 13, 2017
 *      Author: peter
 */

#ifndef MIDDLEWARES_NIWARE_CHAINOFRESPONSIBILLITY_PIDCOMMANDER_BALLPIDCOMMANDER_H_
#define MIDDLEWARES_NIWARE_CHAINOFRESPONSIBILLITY_PIDCOMMANDER_BALLPIDCOMMANDER_H_

#include <ChainOfResponsibillity/ICommander.h>
#include <PID/PID.hpp>

class BallPIDCommander: public ICommander {
public:
	BallPIDCommander( PID &pidx, PID &pidy, ICommander &next );
	virtual ~BallPIDCommander();

	void Execute(Command cmd);
	void PassNext(Command cmd);

};

#endif /* MIDDLEWARES_NIWARE_CHAINOFRESPONSIBILLITY_PIDCOMMANDER_BALLPIDCOMMANDER_H_ */
