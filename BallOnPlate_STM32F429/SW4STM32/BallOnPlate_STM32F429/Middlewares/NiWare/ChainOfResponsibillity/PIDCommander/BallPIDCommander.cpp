/*
 * PIDCommander.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: peter
 */

#include <ChainOfResponsibillity/PIDCommander/BallPIDCommander.h>


/**
 *
 * @param pidx
 * @param pidy
 * @param next
 */
BallPIDCommander::BallPIDCommander(PID& pidx, PID& pidy, ICommander& next)
	: Next(next),XPid(pidx),YPid(pidy){
}
/********************************************************/



/**
 *
 */
BallPIDCommander::~BallPIDCommander() {
	// TODO Auto-generated destructor stub
}

