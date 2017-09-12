/*
 * DOF.h
 *
 *  Created on: 7 wrz 2017
 *      Author: Peter
 */

#ifndef DOF_H_
#define DOF_H_

#include "../PID/PID.hpp"
#include "../PlatformController/PlatformController.hpp"
#include "../TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"

/**
 *
 */
class DOF: public IControlable {
protected:
	PlatformController &Controller;

public:
	DOF( PlatformController &controller ):Controller(controller){};

	virtual ~DOF(){};
	virtual void Set( double value ) = 0;
};
/********************************************************/



/**
 *
 */
class RollDOF : public DOF{
public:
	RollDOF( PlatformController &controller ):DOF(controller){};

	virtual ~RollDOF(){};
	void Set( double value ) { Controller.Roll(value, Deg); };
};
/********************************************************/



/**
 *
 */
class PitchDOF : public DOF{
public:
	PitchDOF( PlatformController &controller ):DOF(controller){};

	virtual ~PitchDOF(){};
	void Set( double value ) { Controller.Pitch(value,Deg); };
};
/********************************************************/



class Plate : public IPerceptible{
protected:
	TouchPanel4W &Panel;

public:
	Plate( TouchPanel4W &panel) : Panel(panel) {};
	virtual ~Plate(){};
	virtual double Get() = 0;
};

class XPlate : public Plate{
public:

	XPlate( TouchPanel4W &panel) : Plate(panel) {};
	virtual ~XPlate(){};
	double Get() { return (double)Panel.GetX(); };
};

class YPlate : public Plate{
public:

	YPlate( TouchPanel4W &panel) : Plate(panel) {};
	virtual ~YPlate(){};
	double Get() { return (double)Panel.GetY(); };
};

#endif /* DOF_H_ */
