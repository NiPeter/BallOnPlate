/*
 * CmdType.h
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_
#define APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_

typedef enum {

/**
 * General <0,249>
 */
	fail = 0,
	ok,
	submit,
	abort,
	startMode,
	stopMode,
	resetMode,



/**
 * Selector <250,499>
 */
	moveTo = 250,
	selectPid,



/**
 * Setter <500,749>
 */
	setMode = 500,
	setSetpointX,
	setSetpointY,
	setPidSamplingInterval,
	setKp,
	setKi,
	setKd,
	setN,
	setPidUpperLimit,
	setPidLowerLimit,
	setPidDeadband,
	setIkX,
	setIkY,
	setIkZ,
	setIkRoll,
	setIkPitch,
	setIkYaw,



/**
 * Getter <750,999>
 */
	getMode = 750,
	isModeWorking,
	getSetpointX,
	getSetpointY,
	getErrorX,
	getErrorY,
	getPidSamplingInterval,
	getPid,
	getKp,
	getKi,
	getKd,
	getN,
	getPidUpperLimit,
	getPidLowerLimit,
	getPidDeadband,
	isPidWorking,
	getIkX,
	getIkY,
	getIkZ,
	getIkRoll,
	getIkPitch,
	getIkYaw,




} CmdType_e;

typedef enum {

};


#endif /* APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_ */
