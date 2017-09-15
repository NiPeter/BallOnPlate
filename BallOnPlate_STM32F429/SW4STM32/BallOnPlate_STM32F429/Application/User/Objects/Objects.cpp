/*
 * Objects.cpp
 *
 *  Created on: 13 wrz 2017
 *      Author: Peter
 */

#include "Objects.hpp"

//TODO OMFG! What a file?! Close this file in master class or something for God`s sake!

/***	COMMUNICATION	***/
HC05	Bluetooth(&huart1);

Communicator Comm(&Bluetooth);
/********************************************************/
/********************************************************/



/***	CONTROLLER	***/
Servo Servos[6] = {

		Servo(&htim9,TIM_CHANNEL_2), 	// PE6 - Br¹zowy
		Servo(&htim9,TIM_CHANNEL_1),	// PE5 - ¯ó³ty
		Servo(&htim4,TIM_CHANNEL_2),	// PB7 - Niebieski
		Servo(&htim2,TIM_CHANNEL_2),	// PB3 - Fioletowy
		Servo(&htim3,TIM_CHANNEL_3),	// PC8 - Bia³y
		Servo(&htim3,TIM_CHANNEL_1),	// PB4 - Pomarañczowy

};

Steward_Struct Steward = {
		{ 0.075, 	0.5236 	}, // Base_Struct {r , alpha}
		{ 0.05,		1.7453	}, // Platform_Struct {r , alpha}
		{ 0.01653,	0.095	}  // Drive_Struct {a , s}
};

PlatformController 	Controller(Servos,&Steward);
/********************************************************/
/********************************************************/



/***	TOUCH PANEL		***/
AnalogPin 			XAnalog(&hadc3,PF6_GPIO_Port,PF6_Pin);
AnalogPin 			YAnalog(&hadc1,PC3_GPIO_Port,PC3_Pin);
Pin					XGnd(PE2_GPIO_Port,PE2_Pin);
Pin					YGnd(PE4_GPIO_Port,PE4_Pin);

TouchPanel4W 		Panel(XAnalog,XGnd,YAnalog,YGnd);
/********************************************************/
/********************************************************/



/***	PID		***/
double kpX = 0.05;
double kiX = 0.08;
double kdX = 0.04;
double nX = 6;

double kpY = 0.05;
double kiY = 0.08;
double kdY = 0.04;
double nY = 6;

double dt = 0.02;

XAxis 				XPos(Panel);
YAxis 				YPos(Panel);
RollDOF 			Roll(Controller);
PitchDOF 			Pitch(Controller);

DiscreteTimePID XPid(kpX,kiX,kdX,dt,nX,&XPos,&Pitch);
DiscreteTimePID YPid(kpY,kiY,kdY,dt,nY,&YPos,&Roll);
/********************************************************/
/********************************************************/

