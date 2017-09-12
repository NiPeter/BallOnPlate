/*
 * Axis.h
 *
 *  Created on: 12 wrz 2017
 *      Author: Peter
 */

#ifndef AXIS_H_
#define AXIS_H_


#include "../PID/PID.hpp"
#include "../TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"


/***	INTERFACES TO 		TOUCH PANEL	***/

/**
 * @brief Virtual interface class to access Touch Screen's axes
 */
class Axis : public IPerceptible{
protected:
	TouchPanel4W &Panel;

public:
	Axis( TouchPanel4W &panel) : Panel(panel) {};
	virtual ~Axis(){};
	virtual double Get() = 0;
};
/********************************************************/



/**
 * @brief Interface class to access Touch Screen's X axis
 */
class XAxis : public Axis{
public:

	XAxis( TouchPanel4W &panel) : Axis(panel) {};
	virtual ~XAxis(){};
	double Get() { return (double)Panel.GetX(); };
};
/********************************************************/



/**
 * @brief Interface class to access Touch Screen's Y axis
 */
class YAxis : public Axis{
public:

	YAxis( TouchPanel4W &panel) : Axis(panel) {};
	virtual ~YAxis(){};
	double Get() { return (double)Panel.GetY(); };
};
/********************************************************/



#endif /* AXIS_H_ */
