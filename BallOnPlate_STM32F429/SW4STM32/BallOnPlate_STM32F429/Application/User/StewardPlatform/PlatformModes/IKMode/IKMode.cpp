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
		Q[i] = q[i];
	}
	if(isStarted)
		Controller->Move(Q,Deg);
}
