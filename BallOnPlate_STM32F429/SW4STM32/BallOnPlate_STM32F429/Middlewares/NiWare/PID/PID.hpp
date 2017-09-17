/*
 * PID.hpp
 *
 *  Created on: 6 wrz 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_PID_PID_HPP_
#define APPLICATION_USER_PID_PID_HPP_

#ifndef NULL
#define NULL   ((void *) 0)
#endif

class IPerceptible;
class IControlable;


class IPerceptible{
public:
	virtual ~IPerceptible(){};
	virtual double Get() = 0;
};


class IControlable{
public:
	virtual ~IControlable(){};
	virtual void Set(double value) = 0;
};



class PID{

public:

	virtual ~PID(){};

	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Reset() = 0;

	void SetSetpoint(double setpoint) {
		Setpoint = setpoint;
	};

	double GetSetpoint() const {
		return Setpoint;
	}

	double GetOutput() const {
		return ControlVariable;
	};

	void Tune(double kp,double ki,double kd) {
		Kp = kp;
		Ki = ki;
		Kd = kd;
	}

	double GetKd() const {
		return Kd;
	}

	double GetKi() const {
		return Ki;
	}

	double GetKp() const {
		return Kp;
	}

protected:

	double Kp;
	double Ki;
	double Kd;

	volatile double Setpoint;				// r(t)
	volatile double ControlVariable;		// u(t)

	IPerceptible *Sensor;		//
	IControlable *Actuator;		// Plant / Process

};


#endif /* APPLICATION_USER_PID_PID_HPP_ */
