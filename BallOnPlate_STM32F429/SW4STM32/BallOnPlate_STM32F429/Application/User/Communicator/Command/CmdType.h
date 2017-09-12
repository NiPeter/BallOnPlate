/*
 * CmdType.h
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_
#define APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_

typedef enum {
	Fail = 0,
	Ok,
	Stop,
	Start,
	Set,
	Get,
	SetX = 30,
	SetY,
	GetX,
	GetY
} CmdType_e;


#endif /* APPLICATION_USER_COMMUNICATOR_CMDTYPE_H_ */
