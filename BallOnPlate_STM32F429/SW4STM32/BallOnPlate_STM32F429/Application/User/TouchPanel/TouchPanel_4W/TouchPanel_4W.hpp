/*
 * TouchPanel_4W.hpp
 *
 *  Created on: 29 sie 2017
 *      Author: Peter
 */

#ifndef DRIVERS_TOUCHPANEL_4W_TOUCHPANEL_4W_HPP_
#define DRIVERS_TOUCHPANEL_4W_TOUCHPANEL_4W_HPP_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"


#include "../Filters/MedianFilter/MedianFilter.hpp"
#include "../ITouchPanel.hpp"
#include "Pin.hpp"



class TouchPanel4W : public ITouchPanel{
	struct Corr{
		float adc_min;
		float adc_max;
		float size;
	};

public:
	TouchPanel4W(AnalogPin &x_analog, Pin &x_gnd, AnalogPin &y_analog, Pin &y_gnd);

	void Process(void);
	void ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc);

private:

	static const uint8_t 	settlingTimeMs = 2;	// TouchPanel settling time after polarisation change.

	static const struct Corr	sXCorr;
	static const struct Corr	sYCorr;

	AnalogPin 		&XAnalog,	&YAnalog;
	Pin				&XGnd,		&YGnd;

	IFilter<float,float>		*XFilter;
	IFilter<float,float>		*YFilter;

	void PrepareTouchDetection();
	void PrepareMeasurement(AnalogPin &analog, Pin &vcc, Pin &gnd, Pin &hiZ);
	void PrepareXMeasurement();
	void PrepareYMeasurement();

	uint32_t MeasureX();
	uint32_t MeasureY();

	float FCorr(float value, const struct Corr * corr);

	void InitFilters();

};


#endif /* DRIVERS_TOUCHPANEL_4W_TOUCHPANEL_4W_HPP_ */
