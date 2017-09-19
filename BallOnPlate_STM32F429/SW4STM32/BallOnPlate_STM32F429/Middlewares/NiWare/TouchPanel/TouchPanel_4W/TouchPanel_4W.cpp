
#include "TouchPanel_4W.hpp"


const TouchPanel4W::Corr TouchPanel4W::sXCorr  = {
		430, 3717, 229
};

const TouchPanel4W::Corr TouchPanel4W::sYCorr = {
		248, 3830, 304
};


TouchPanel4W::TouchPanel4W(AnalogPin *x_analog,Pin *x_gnd,AnalogPin *y_analog,Pin *y_gnd)
:XAnalog(x_analog),YAnalog(y_analog),XGnd(x_gnd),YGnd(y_gnd){
	X = 0;
	Y = 0;
	Touched = false;
	InitFilters();
}



TouchPanel4W::~TouchPanel4W() {
	delete XFilter;
	delete YFilter;
}

/**
 * @brief Initialise TouchPanel filters
 */
void TouchPanel4W::InitFilters(){ //TODO User shoud be able to attach own IFilter!!
	XFilter = new MedianFilter(21,3);
	YFilter = new MedianFilter(21,3);
}
/********************************************************/

struct TPanelAQ{
	float X;
	float Y;
	int T;
} TPanel;

/**
 * @brief Process function
 * @note Should be called periodicaly!
 */
void TouchPanel4W::Process(void){
	const uint8_t size = 100;
	static uint8_t touch_inc = 0;

	PrepareTouchDetection();
	osDelay(settlingTimeMs);
	bool analogRead = XAnalog->Read();

	if( analogRead != false){
		if(touch_inc){
			touch_inc--;
			return;
		}
		else {
			XFilter->Reset();
			YFilter->Reset();
			Touched = false;

			touch_inc = size;
			return;
		}
	} else {
		touch_inc = size;
	}



	//	if(touch_inc == 0){
	//		XFilter->Reset();
	//		YFilter->Reset();
	//		Touched = false;
	//		return;
	//	}

	float tmpX = XFilter->Filter(MeasureX());
	float corrX = FCorr(tmpX,&sXCorr);

	float tmpY = YFilter->Filter(MeasureY());
	float corrY = FCorr(tmpY,&sYCorr);

	taskENTER_CRITICAL();{
		if(tmpX && tmpY){
			X= corrX;
			Y= -corrY;
			Touched = true;
			TPanel.X = X;
			TPanel.Y = Y;
			TPanel.T = Touched;
		}
	}taskEXIT_CRITICAL();

}
/********************************************************/





/********************************************************/
/********************************************************/

uint32_t TouchPanel4W::MeasureX(){
	PrepareXMeasurement();
	osDelay(settlingTimeMs);
	YAnalog->Measure();
	HAL_ADC_PollForConversion(YAnalog->GetADC_Handle(),100);
	return YAnalog->GetADCValue();

}
uint32_t TouchPanel4W::MeasureY(){
	PrepareYMeasurement();
	osDelay(settlingTimeMs);
	XAnalog->Measure();
	HAL_ADC_PollForConversion(XAnalog->GetADC_Handle(),100);
	return XAnalog->GetADCValue();

}

/**
 * @details Function prepares pins to measurement.
 * @param analog
 * @param vcc
 * @param gnd
 * @param hiZ
 */
/********************************************************/
void TouchPanel4W::PrepareMeasurement(AnalogPin *analog, Pin *vcc, Pin *gnd, Pin *hiZ){
	analog->SetAnalogMode();

	hiZ->SetInputMode();

	vcc->SetOutputMode();
	vcc->Write(true);

	gnd->SetOutputMode();
	gnd->Write(false);
}

void TouchPanel4W::PrepareXMeasurement(){
	PrepareMeasurement(YAnalog,XAnalog,XGnd,YGnd);
}
void TouchPanel4W::PrepareYMeasurement(){
	PrepareMeasurement(XAnalog,YAnalog,YGnd,XGnd);
}

void TouchPanel4W::PrepareTouchDetection(){
	XAnalog->SetInputMode(PullUp);
	YGnd->SetOutputMode(PullDown);

	YAnalog->SetInputMode();
	XGnd->SetInputMode();
}
/********************************************************/



float TouchPanel4W::FCorr(float value, const struct Corr * corr) {

	//	return ((value - corr->adc_min)*corr->size)/(corr->adc_max-corr->adc_min);

	float dm = corr->adc_max - corr->adc_min;

	return ( ( value - dm/2 ) * corr->size / 2 )/( corr->adc_max - dm/2 );

}


