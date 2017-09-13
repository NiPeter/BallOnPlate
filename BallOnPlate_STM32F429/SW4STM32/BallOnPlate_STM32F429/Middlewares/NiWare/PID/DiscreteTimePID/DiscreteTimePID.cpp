/*
 * DiscreteTimePID.cpp
 *
 *  Created on: 8 wrz 2017
 *      Author: Peter
 */

#include "DiscreteTimePID.h"


DiscreteTimePID::DiscreteTimePID(double kp, double ki, double kd, double ts,double n,
		IPerceptible* sensor, IControlable* actuator) {
	Tune(kp,ki,kd,n);
	SetLimits(100,-100);
	SetDeadband(0);
	Sensor = sensor;
	Actuator = actuator;

	if(ts <= 0) Ts = 0.01; //TODO dT <= 0 then EXCEPTON!
	else Ts = ts;

	Stop();
	Reset();
}

void DiscreteTimePID::Process() {
	if( Working == false ) return;

	e2=e1; e1=e0; u2=u1; u1=ControlVariable; // update variables

	double y = Sensor->Get();  // read plant output

	e0 = Setpoint - y;
	if( fabs(e0) < Deadband ) return;	// Deadband

	ControlVariable = -ku1*u1 - ku2*u2 + ke0*e0 + ke1*e1 + ke2*e2;

	if (ControlVariable > Max) ControlVariable = Max;  // limit to DAC or PWM range
	if (ControlVariable < Min) ControlVariable = Min;

	Actuator->Set(ControlVariable);   // sent to output
}

void DiscreteTimePID::Start() {
	Working = true;
}

void DiscreteTimePID::Stop() {
	Working = false;
}

void DiscreteTimePID::Reset() {
	Setpoint = 0;
	ControlVariable = 0;
	e2 = 0;
	e1 = 0;
	e0 = 0;
	u2 = 0;
	u1 = 0;
	ControlVariable = 0;
}

void DiscreteTimePID::Tune(double kp, double ki, double kd, double n) {
	Kp = kp; Ki = ki; Kd = kd; N = n; // Store variables

	double a0 = (1+N*Ts);
	double a1 = -(2 + N*Ts);
	double a2 = 1;
	double b0 = Kp*(1+N*Ts) + Ki*Ts*(1+N*Ts) + Kd*N;
	double b1 = -(Kp*(2+N*Ts) + Ki*Ts + 2*Kd*N);
	double b2 = Kp + Kd*N;

	ku1 = a1/a0;
	ku2 = a2/a0;
	ke0 = b0/a0;
	ke1 = b1/a0;
	ke2 = b2/a0;

}
