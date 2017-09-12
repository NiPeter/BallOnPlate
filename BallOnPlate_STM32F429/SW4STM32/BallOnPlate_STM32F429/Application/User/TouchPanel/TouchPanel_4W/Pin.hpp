/*
 * Pin.hpp
 *
 *  Created on: 29 sie 2017
 *      Author: Peter
 */

#ifndef DRIVERS_TOUCHPANEL_4W_PIN_HPP_
#define DRIVERS_TOUCHPANEL_4W_PIN_HPP_

#include "stm32f4xx_hal.h"

/**
 * @note FIRSTLY ALL GPIOS SHOULD BE INITIALISED IN CUBE MX MSP_INIT!!!
 */

class Pin;
class AnalogPin;

enum  	PushPull_e	{ NoPull = GPIO_NOPULL, PullUp = GPIO_PULLUP, PullDown = GPIO_PULLDOWN};
enum 	PinMode_e	{ None, Analog , Input, Output };

class Pin{

public:

	Pin(GPIO_TypeDef* hgpio, uint16_t pin, PinMode_e mode = Input, PushPull_e  pull = NoPull);
	Pin(Pin &pin);

	void Write(bool state);
	void Toggle(void);
	bool Read(void);

	PinMode_e GetMode() {return Mode;};

	void SetOutputMode(  PushPull_e pull = NoPull);
	void SetInputMode(  PushPull_e pull = NoPull );

protected:

	GPIO_TypeDef*		hGPIO;	// GPIO handle
	uint16_t			nPIN;	// Pin handle

	PinMode_e			Mode;	// Pin Mode

};




/********************************************************/
class AnalogPin : public Pin{

public:

	AnalogPin(ADC_HandleTypeDef* hadc, GPIO_TypeDef* hgpio, uint16_t pin);

	void SetAnalogMode(void);

	void Measure_IT(void);
	void Measure(void);

	uint32_t GetADCValue(void);
	ADC_HandleTypeDef* GetADC_Handle(void);

private:

	ADC_HandleTypeDef* 					hADC; // ADC handle


};
/********************************************************/

#endif /* DRIVERS_TOUCHPANEL_4W_PIN_HPP_ */
