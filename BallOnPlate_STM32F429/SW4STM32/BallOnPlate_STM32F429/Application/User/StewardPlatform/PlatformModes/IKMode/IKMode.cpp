/*
 * IKMode.cpp
 *
 *  Created on: Sep 19, 2017
 *      Author: peter
 */

#include "IKMode.h"


IKMode::~IKMode() {
	Reset();
}

IKMode::IKMode(IKController* controller) : Controller(controller),isStarted(false){
	movable = true;
	for (int i = 0; i < 6; ++i) {
		Q[i] = 0;
	}
	Start();
	Controller->Move(Q,Deg);
}

void IKMode::Start() {

	Controller -> Start();
	isStarted = true;
}

void IKMode::Stop() {
	Controller -> Stop();
	isStarted = false;
}

void IKMode::Reset() {

	if( isStarted == false ) Controller->Start();
	for (int i = 0; i < 6; ++i) {
		Q[i] = 0;
	}
	Controller->Move((double *)Q,Deg);
	Controller -> Stop();

}

void IKMode::MoveTo(float q[6]) {
	for (int i = 0; i < 6; ++i) {
		if (i<3) {
			q[i] = q[i]/1000.0;
		}
		Q[i] = q[i];
	}
	if(isStarted)
		Controller->Move(Q,Deg);
}

void IKMode::MoveTo(float x, float y, float z, float roll, float pitch,
		float yaw) {
	if(isStarted)
		Controller->Move(x/1000.0,y/1000.0,z/1000.0,roll,pitch,yaw,Deg);
}
