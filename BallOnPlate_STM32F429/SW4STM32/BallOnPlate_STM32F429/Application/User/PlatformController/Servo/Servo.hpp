/*
 * Servo.hpp
 *
 *  Created on: 7 sie 2017
 *      Author: Peter
 */

#ifndef SERVO_HPP_
#define SERVO_HPP_

/***	Hardware STM32	***/
#include "stm32f4xx_hal.h"
#include "math.h"

enum AngleUnits_e {Deg, Rad};

/**
 * @brief Servo class declaration
 */
class Servo{
public:

	Servo(TIM_HandleTypeDef * htim ,uint16_t channel, unsigned int resolution = 45000, unsigned int freq_pwm = 50);

	void Start( void );
	void Stop( void );

	void SetPos(double angle, AngleUnits_e unit = Rad);
	float GetPos( AngleUnits_e unit = Rad );

	void Calibrate(double min, double max);

private:

	/***	Variables	***/
	TIM_HandleTypeDef* 	hTIM;			// Timer handle
	uint16_t	 		Channel;		// Chanel handle

	double 				ms_min;			// 0 pulse time
	double 				ms_max;			// 180deg pulse time

	unsigned int 		Frequency;		// PWM frequency in HZ
	unsigned int		Resolution;		// PWM resolution

	/***	Functions	***/
	double radToMs( double angle);
	double degToMs( double angle );
	uint16_t msToCCR( double ms);

};
/********************************************************/

#endif /* SERVO_HPP_ */
