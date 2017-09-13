/*
 * Objects.cpp
 *
 *  Created on: 13 wrz 2017
 *      Author: Peter
 */

#include "Objects.hpp"

HC05	Bluetooth(&huart1);
Communicator Comm(&Bluetooth);

Servo Servos[6] = {

		Servo(&htim4,TIM_CHANNEL_2),	// PB7 - Niebieski

		Servo(&htim3,TIM_CHANNEL_1),	// PB4 - Pomara�czowy
		Servo(&htim2,TIM_CHANNEL_2),	// PB3 - Fioletowy

		Servo(&htim9,TIM_CHANNEL_2), 	// PE6 - Br�zowy
		Servo(&htim9,TIM_CHANNEL_1),	// PE5 - ��ty

		Servo(&htim3,TIM_CHANNEL_3),	// PC8 - Bia�y

};
Steward_Struct Steward = {
		{ 0.075, 	0.5236 	}, // Base_Struct {r , alpha}
		{ 0.05,		1.7453	}, // Platform_Struct {r , alpha}
		{ 0.01653,	0.095	}  // Drive_Struct {a , s}
};
PlatformController 	Controller(Servos,&Steward);
RollDOF 			Roll(Controller);
PitchDOF 			Pitch(Controller);

AnalogPin 			XAnalog(&hadc1,X_ADC_GPIO_Port,X_ADC_Pin);
AnalogPin 			YAnalog(&hadc2,Y_ADC_GPIO_Port,Y_ADC_Pin);
Pin					XGnd(X_GND_GPIO_Port,X_GND_Pin);
Pin					YGnd(Y_GND_GPIO_Port,Y_GND_Pin);
TouchPanel4W 		Panel(XAnalog,XGnd,YAnalog,YGnd);

XAxis 				XPos(Panel);
YAxis 				YPos(Panel);


double kpX = 0.05;
double kiX = 0.08;
double kdX = 0.04;
double nX = 8;

double kpY = 0.05;
double kiY = 0.08;
double kdY = 0.04;
double nY = 8;

double dt = 0.02;

DiscreteTimePID XPid(kpX,kiX,kdX,dt,nX,&XPos,&Pitch);
DiscreteTimePID YPid(kpY,kiY,kdY,dt,nY,&YPos,&Roll);
