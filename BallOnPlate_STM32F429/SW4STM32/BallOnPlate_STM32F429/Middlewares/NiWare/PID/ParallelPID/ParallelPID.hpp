/*
 * ParallelPID.hpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_PID_PARALLELPID_PARALLELPID_HPP_
#define APPLICATION_USER_PID_PARALLELPID_PARALLELPID_HPP_

#include "../PID.hpp"

class ParallelPID : public PID{

	static const float maxSumError = 400;

public:

	ParallelPID(double kp, double ki, double kd, double ts, IPerceptible *sensor, IControlable *actuator);

	void Process();

	void Start();
	void Stop();
	void Reset();

	double GetTs() const {
		return Ts;
	}

	bool IsWorking() const {
		return Working;
	}

	double GetdError() const {
		return dError;
	}

	double GetError() const {
		return error;
	}

	double GetPrevError() const {
		return PrevError;
	}

	double GetSumError() const {
		return SumError;
	}

private:

	double Ts;
	double PrevError;
	double SumError;
	double dError;
	double error;
	bool Working;	// True if working

};


#endif /* APPLICATION_USER_PID_PARALLELPID_PARALLELPID_HPP_ */
