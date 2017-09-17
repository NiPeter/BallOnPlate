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
	empty =0,
	fail,
	ok,
	submit,
	cancel,
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
	isPanelTouched = 750,
	getPanelX,
	getPanelY,
	getMode,
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
	demo = 0,
	pidMode,
	ikMode,
	servoMode,
} ModeType_e;

typedef enum {
	selectPidX,
	selectPidY,
} PidSelect_e;



bool isCommandTypeInRange(CmdType_e cmdType, CmdType_e lower, CmdType_e upper);



#endif /* APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_ */
