/*
 * StewardPlatform.cpp
 *
 *  Created on: 16 wrz 2017
 *      Author: Peter
 */

#include "../PlatformControlSystem/PlatformControlSystem.h"

PlatformControlSystem::PlatformControlSystem(){
	Construct();
}

PlatformControlSystem::~PlatformControlSystem() {
//	for(uint8_t i=0; i<6; i++) delete Ser
}

void PlatformControlSystem::Construct() {
	ConfigConstruct();
	ServosConstruct();
	Controller = IKController(Servos,&StewardConfig);
}

void PlatformControlSystem::ConfigConstruct() {
	StewardConfig.base.r 			= 	0.075;
	StewardConfig.base.alpha		=	0.5236; // Base_Struct {r , alpha}

	StewardConfig.platform.r		=	0.05;
	StewardConfig.platform.alpha	=	1.7453;	// Platform_Struct {r , alpha}

	StewardConfig.drive.a		=	0.01653;
	StewardConfig.drive.s		=	0.095;  // Drive_Struct {a , s}
}

void PlatformControlSystem::ServosConstruct() {
	Servos[0] =	Servo(&htim9,TIM_CHANNEL_2); 	// PE6 - Br¹zowy
	Servos[1] =	Servo(&htim9,TIM_CHANNEL_1);	// PE5 - ¯ó³ty
	Servos[2] =	Servo(&htim4,TIM_CHANNEL_2);	// PB7 - Niebieski
	Servos[3] =	Servo(&htim2,TIM_CHANNEL_2);	// PB3 - Fioletowy
	Servos[4] =	Servo(&htim3,TIM_CHANNEL_3);	// PC8 - Bia³y
	Servos[5] =	Servo(&htim3,TIM_CHANNEL_1);	// PB4 - Pomarañczowy
}
