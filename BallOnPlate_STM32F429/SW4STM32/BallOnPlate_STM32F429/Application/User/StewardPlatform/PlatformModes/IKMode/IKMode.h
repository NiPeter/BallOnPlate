/*
 * IKMode.h
 *
 *  Created on: Sep 19, 2017
 *      Author: peter
 */

#ifndef APPLICATION_USER_STEWARDPLATFORM_PLATFORMMODES_IKMODE_IKMODE_H_
#define APPLICATION_USER_STEWARDPLATFORM_PLATFORMMODES_IKMODE_IKMODE_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "../PlatformMode.h"

#include <IKController/IKController.hpp>

class IKMode: public PlatformMode {
	friend class CommandSubmit;

	IKController* Controller;

	double Q[6];
	bool isStarted;

public:

	virtual ~IKMode();
	IKMode(IKController* controller);

	void Start();
	void Stop();
	void Reset();

	void MoveTo(float q[6]);
	void MoveTo(float x, float y, float z, float roll, float pitch, float yaw);

};

#endif /* APPLICATION_USER_STEWARDPLATFORM_PLATFORMMODES_IKMODE_IKMODE_H_ */
