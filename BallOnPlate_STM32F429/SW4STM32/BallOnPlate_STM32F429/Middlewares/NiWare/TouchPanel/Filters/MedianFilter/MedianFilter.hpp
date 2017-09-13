/*
 * MedianFilter.hpp
 *
 *  Created on: 17 sie 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_TOUCHPANEL_MEDIANFILTER_HPP_
#define APPLICATION_USER_TOUCHPANEL_MEDIANFILTER_HPP_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "../IFilter.hpp"
#include "../RingBuffer/RingBuffer.hpp"



class MedianFilter : public IFilter<float,float>{

	uint8_t NToAvg;
	uint8_t Size;

	RingBuffer<float> Buffer;
	float*	pTmpDataBuff;
	float*	pDataToAvg;

public:

	MedianFilter(uint8_t size, uint8_t nToAvg = 3);
	~MedianFilter(void);
	float Filter( float data);
	void Reset( void );

private:

	void SortTable(float tab[], uint8_t lenght);
	float Average(const float* Data, uint8_t length);

	bool isOdd(uint16_t num){ return num%2 == 1; }; // czy nieparzysty

};

#endif /* APPLICATION_USER_TOUCHPANEL_MEDIANFILTER_HPP_ */
