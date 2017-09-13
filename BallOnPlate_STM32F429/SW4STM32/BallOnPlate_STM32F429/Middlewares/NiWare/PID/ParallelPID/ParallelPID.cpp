/*
 * ParallelPID.cpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#include "ParallelPID.hpp"



/**
 * @brief ParallelPID contructor
 */
ParallelPID::ParallelPID(double kp, double ki, double kd, double ts,
		IPerceptible *sensor, IControlable *actuator){

	Tune(kp,ki,kd);
	Sensor = sensor;
	Actuator = actuator;

	if(ts <= 0) Ts = 0.01; //TODO dT <= 0 then EXCEPTON!
	else Ts = ts;

	Stop();
	Reset();

}
/********************************************************/



/**
 * @brief PID process function
 * @note Process function should be called periodically with dT interval!
 */
void ParallelPID::Process() {

	if(Working == false) return;

	double pv = Sensor->Get(); // Get process Variable

	// Error computing
	error = Setpoint - pv;				// proportional error
	dError = (error - PrevError)/ Ts;	// derivative error
	SumError += error * Ts ;					// integral error

	if(SumError >= maxSumError) SumError = maxSumError;
	if(SumError <= -maxSumError) SumError = -maxSumError;

	// Compute output
	ControlVariable = Kp * error + Ki * SumError + Kd * dError;

	// Store previous error
	PrevError = error;

	// Set output to actuator
	Actuator->Set(ControlVariable);

}
/********************************************************/



/**
 * @brief Start controller
 */
void ParallelPID::Start() {
	Working = true;
}
/********************************************************/



/**
 * @brief Stop controller
 */
void ParallelPID::Stop() {
	Working = false;
}
/********************************************************/



/**
 * @brief Reset controler internal state
 * @note This will not stop the controller!
 */
void ParallelPID::Reset() {
	Setpoint = 0;
	ControlVariable = 0;
	PrevError = 0;
	SumError = 0;
}
/********************************************************/
