/*
 * PlatformController.hpp
 *
 *  Created on: 9 sie 2017
 *      Author: Peter
 */

#ifndef PLATFORMCONTROLLER_HPP_
#define PLATFORMCONTROLLER_HPP_

/***	MATLAB C Code Includes	***/
#ifdef __cplusplus
extern "C" {
#endif

#include "structInitFnc/structInitFnc.h"
#include "structInitFnc/structInitFnc_terminate.h"
#include "structInitFnc/structInitFnc_initialize.h"

#include "servoIK/servoIK.h"
#include "servoIK/servoIK_terminate.h"
#include "servoIK/servoIK_initialize.h"

#ifdef __cplusplus
}
#endif
/***	MATLAB C End	***/

#include "Servo/Servo.hpp"

/***	Inline coverter functions	***/
inline float rad2deg(float angle){ return (angle * 180) / M_PI; }
inline float deg2rad(float angle){ return ( M_PI / 180 ) * angle; }

class PlatformController{

public:

	PlatformController(Servo servo[6],Steward_Struct* steward);
	PlatformController(Servo* servo1, Servo* servo2, Servo* servo3, Servo* servo4, Servo* servo5, Servo* servo6, Steward_Struct* steward);

	// Units - deg and mm
	void Translate( double x, double y, double z);
	void X( double x);
	void Y( double y);
	void Z( double z);

	void Rotate( double roll, double pitch, double yaw, AngleUnits_e unit = Rad);
	void Roll( double roll, AngleUnits_e unit = Rad);
	void Pitch( double pitch, AngleUnits_e unit = Rad);
	void Yaw( double yaw, AngleUnits_e unit = Rad);

	void Move( double q[6], AngleUnits_e unit = Rad);

	void Start( void );
	void Stop( void );

	void GetAngles(double angles[6], AngleUnits_e unit = Rad);
	void GetQ( double q[6], AngleUnits_e unit = Rad);

private:

	/***	Private Variables	***/
	Servo* servos[6];		// Servos handles
	IK_Struct IK;			// Inverse Kinematic Struct (contains all nessesary platform parameters)

	double Q[6];			// Desired platform Position and Orientation mm and rad
	double Angles[6];		// Desired servo angles rad

	/***	Private Functions	***/
	void IKfun( void );
	void IKinit(Steward_Struct* steward);
	void SetPositions( void );

	double RadianUnitCorrection(double angle, AngleUnits_e unit );

};



#endif /* PLATFORMCONTROLLER_HPP_ */
