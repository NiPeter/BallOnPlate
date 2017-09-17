/*
 * DiscreteTimePID.h
 *
 *  Created on: 8 wrz 2017
 *      Author: Peter
 */

#ifndef DISCRETETIMEPID_H_
#define DISCRETETIMEPID_H_

#include "../PID.hpp"
#include "math.h"

// http://controlsystemslab.com/discrete-time-pid-controller-implementation/

typedef struct {
	double Kp;
	double Ki;
	double Kd;
	double N;
} pidSettings;

/*
 *
 */
class DiscreteTimePID : public PID{

public:
	DiscreteTimePID(double kp, double ki, double kd, double n, double ts,
			IPerceptible* sensor, IControlable* actuator);
	DiscreteTimePID(pidSettings* settings,double ts,
			IPerceptible* sensor, IControlable* actuator);

	void Process();

	void Start();
	void Stop();
	void Reset();

	void Tune(double kp, double ki, double kd, double n);
	void Tune(pidSettings* settings);

	void SetDeadband( double deadband){
		if(deadband<0) deadband = -deadband;
		Deadband = deadband;
	}

	void SetOutputLimits( double max, double min ){
		if( min<max ){
			Max = max;
			Min = min;
		}
	}

	double GetTs() const {
		return Ts;
	}

	bool IsWorking() const {
		return Working;
	}

	double GetN() const {
		return N;
	}

	double GetError() const {
		return e0;
	}

private:

	double Ts,N;

	double ku1,ku2,ke0,ke1,ke2;
	double e2, e1, e0, u2, u1;  // variables used in PID computation

	double Max, Min;
	double Deadband;

	volatile bool Working;	// True if working

	void Construct(double kp, double ki, double kd, double n, double ts,
			IPerceptible* sensor, IControlable* actuator);

};

#endif /* DISCRETETIMEPID_H_ */
