/*
 * DiscreteTimePID.h
 *
 *  Created on: 8 wrz 2017
 *      Author: Peter
 */

#ifndef DISCRETETIMEPID_H_
#define DISCRETETIMEPID_H_

#include "../PID.hpp"

// http://controlsystemslab.com/discrete-time-pid-controller-implementation/

/*
 *
 */
class DiscreteTimePID : public PID{

public:
	DiscreteTimePID(double kp, double ki, double kd, double ts,double n,
			IPerceptible* sensor, IControlable* actuator);

	void Process();

	void Start();
	void Stop();
	void Reset();

	void Tune(double kp, double ki, double kd, double n);

	void SetLimits( double max, double min ){
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

	bool Working;	// True if working


};

#endif /* DISCRETETIMEPID_H_ */
