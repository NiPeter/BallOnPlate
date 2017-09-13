/*
 * PlatformController.cpp
 *
 *  Created on: 9 sie 2017
 *      Author: Peter
 */

#include "PlatformController.hpp"



/********************************************************/



/**
 * @brief PlatformController contructor
 * @param servo
 * @param steward
 */
PlatformController::PlatformController(Servo servo[6],Steward_Struct* steward){
	for(int i=0;i<6;i++) servos[i] = &servo[i];

	IKinit(steward);

}
/********************************************************/



/**
 * @brief PlatformController contructor
 * @param servo1
 * @param servo2
 * @param servo3
 * @param servo4
 * @param servo5
 * @param servo6
 * @param steward
 */
PlatformController::PlatformController(Servo* servo1, Servo* servo2, Servo* servo3, Servo* servo4, Servo* servo5, Servo* servo6,Steward_Struct* steward){
	servos[0] = servo1;
	servos[1] = servo2;
	servos[2] = servo3;
	servos[3] = servo4;
	servos[4] = servo5;
	servos[5] = servo6;

	Stop();
	IKinit(steward);
}
/********************************************************/



/**
 * @brief Move platform along XYZ axis.
 * @note Distance unit is mm!
 * @param x
 * @param y
 * @param z
 */
void PlatformController::Translate( double x, double y, double z){
	Q[0] = x;
	Q[1] = y;
	Q[2] = z;

	IKfun();
	SetPositions();
}
/********************************************************/
void PlatformController::X(double x){
	Translate(x,Q[1],Q[2]);
}
void PlatformController::Y(double y){
	Translate(Q[0],y,Q[2]);
}
void PlatformController::Z(double z){
	Translate(Q[0],Q[1],z);
}
/********************************************************/



/**
 * @brief Rotate platform around XYZ axis.
 * @note Angle unit is degree!
 * @param roll
 * @param pitch
 * @param yaw
 */
void PlatformController::Rotate( double roll, double pitch, double yaw, AngleUnits_e unit){
	Q[3] = RadianUnitCorrection(roll,unit);
	Q[4] = RadianUnitCorrection(pitch,unit);
	Q[5] = RadianUnitCorrection(yaw,unit);

	if(Q[3] >= 0.17453) Q[3] = 0.17453;
	if(Q[4] >= 0.17453) Q[4] = 0.17453;
	if(Q[3] <= -0.17453) Q[3] = -0.17453;
	if(Q[4] <= -0.17453) Q[4] = -0.17453;

	IKfun();
	SetPositions();
}
/********************************************************/
void PlatformController::Roll( double roll , AngleUnits_e unit){
	Rotate(RadianUnitCorrection(roll,unit),Q[4],Q[5]);
}
void PlatformController::Pitch( double pitch , AngleUnits_e unit){
	Rotate(Q[3],RadianUnitCorrection(pitch,unit),Q[5]);
}
void PlatformController::Yaw( double yaw , AngleUnits_e unit){
	Rotate(Q[3],Q[4],RadianUnitCorrection(yaw,unit));
}
/********************************************************/



/**
 * @brief Move and rotate platform relative to XYZ.
 * @note Distance unit is mm! Angle unit is degree!
 * @param q - vector 6x1 [X Y Z Roll Pitch Yaw]';
 */
void PlatformController::Move( double q[6], AngleUnits_e unit){

	for(uint8_t i=0; i<6 ; i++)
		Q[i] = q[i];

	Q[3] = RadianUnitCorrection(Q[3],unit);
	Q[4] = RadianUnitCorrection(Q[4],unit);
	Q[5] = RadianUnitCorrection(Q[5],unit);

	IKfun();
	SetPositions();
}
/********************************************************/



/**
 * @brief Start all servo motors.
 */
void PlatformController::Start( void ){
	for( uint8_t i=0 ; i<6 ; i++) servos[i]->Start();
}
/**
 * @brief Stop all servo motors.
 */
void PlatformController::Stop( void ){
	for( uint8_t i=0 ; i<6 ; i++) servos[i]->Stop();
}
/********************************************************/



/**
 *
 * @param angles
 */
/********************************************************/
void PlatformController::GetAngles( double angles[6], AngleUnits_e unit){
	for( uint8_t i=0; i<6; i++) angles[i] = ( unit == Rad ) ? Angles[i] : rad2deg(Angles[i]);
}
void PlatformController::GetQ( double q[6], AngleUnits_e unit){
	for( uint8_t i=0; i<6; i++){
		q[i] = Q[i];
		if( i>=3 ) q[i] = (unit == Rad) ? q[i] : rad2deg(q[i]);
	}
}
/********************************************************/




/***	PRIVATE FUNCTIONS	***/

/**
 *
 */
/********************************************************/
void PlatformController::IKfun(){


//	for(int i=0; i<3 ; i++) Q[i] = Q[i]/1000.0;

//	for(uint8_t i=3; i<6 ; i++) Q[i] = deg2rad(Q[i]);

	servoIK(Q, &IK, Angles);

	for(int i =0;i<6;i++){
		if((i==0) || (i==2) ||(i==4)){ //nieparzyste
			Angles[i] = -Angles[i] + M_PI_2;
		}else{
			Angles[i] = Angles[i] - M_PI_2;
			Angles[i] = M_PI - Angles[i];
		}
	}

}
/********************************************************/



/**
 *
 */
/********************************************************/
void PlatformController::SetPositions( void ){

	for( uint8_t i=0; i<6; i++)
		servos[i]->SetPos(Angles[i]);

}
/********************************************************/



/**
 *
 * @param steward
 */
/********************************************************/
void PlatformController::IKinit(Steward_Struct* steward){



	structInitFnc_initialize();
	servoIK_initialize();

	structInitFnc(steward,(struct0_T*)&IK);

	for (int i = 0; i < 6; ++i) {
		Q[i] = 0.0;
	}
}
/********************************************************/


/**
 *
 * @param angle
 * @param unit
 * @return
 */
double PlatformController::RadianUnitCorrection(double angle,
		AngleUnits_e unit) {
	return (unit == Rad) ? angle : deg2rad(angle);
}
/********************************************************/
