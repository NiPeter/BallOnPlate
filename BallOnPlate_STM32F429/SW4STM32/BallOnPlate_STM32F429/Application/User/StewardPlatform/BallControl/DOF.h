/*
 * DOF.h
 *
 *  Created on: 7 wrz 2017
 *      Author: Peter
 */

#ifndef DOF_H_
#define DOF_H_


#include <IKController/IKController.hpp>
#include <PID/PID.hpp>


/***	INTERFACES TO 		PLATFORM CONTROLLER	***/

/**
 * @brief Virtual interface class to access Platform Controller's DOFs
 */
class DOF: public IControlable {
protected:
	IKController &Controller;

public:
	DOF( IKController &controller ):Controller(controller){};

	virtual ~DOF(){};
	virtual void Set( double value ) = 0;
};
/********************************************************/



/**
 * @brief Interface class to access Platform Controller's roll DOF
 */
class RollDOF : public DOF{
public:
	RollDOF( IKController &controller ):DOF(controller){};

	virtual ~RollDOF(){};
	void Set( double value ) { Controller.Roll(value, Deg); };
};
/********************************************************/



/**
 * @brief Interface class to access Platform Controller's pitch DOF
 */
class PitchDOF : public DOF{
public:
	PitchDOF( IKController &controller ):DOF(controller){};

	virtual ~PitchDOF(){};
	void Set( double value ) { Controller.Pitch(value,Deg); };
};
/********************************************************/



#endif /* DOF_H_ */
