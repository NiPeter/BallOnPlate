/*
 * MedianFilter.cpp
 *
 *  Created on: 17 sie 2017
 *      Author: Peter
 */

#include "MedianFilter.hpp"


/**
 *
 * @param nToAvg
 */
/********************************************************/
MedianFilter::MedianFilter(uint8_t size, uint8_t nToAvg):Buffer(size){

	if( (isOdd(nToAvg)) != (isOdd(size)) ) nToAvg++;
	if(size<=nToAvg) nToAvg = size;

	NToAvg = nToAvg;
	Size = size;

	pTmpDataBuff = new float[Size];
	pDataToAvg	= new float[NToAvg];

};
/********************************************************/



MedianFilter::~MedianFilter(void){
	delete[] pTmpDataBuff;
	delete[] pDataToAvg;
}



void MedianFilter::Reset( void ){
	while(Buffer.IsEmpty() != true ) Buffer.Read();
}


/**
 *
 * @param data
 * @param size
 * @return
 */
/********************************************************/
float MedianFilter::Filter( float data){


	Buffer.Write(data);

	if( Buffer.IsFull() == false ){
		return 0.0;
	}

	const float* pData = Buffer.GetBufferPtr();

	if(NToAvg==Size) return Average( pData,Size);

	for(uint8_t i=0; i<Size;i++){
		pTmpDataBuff[i] = pData[i];
	}

	SortTable(pTmpDataBuff,Size); // Sortuj tablice

	// Znajdz miejsce mediany
	float medianIndex = (Size-1)/2.0;

	medianIndex += 0.5; // Korekcja do elementu tablicy int

	uint8_t startIndex = medianIndex - NToAvg/2.0; // Index pocz¹tku przedzia³u do uœrednienia

	for(uint8_t i=0; i<NToAvg; i++){	// Wpisz dane do uœrednienia
		pDataToAvg[i] = pTmpDataBuff[(uint16_t)startIndex+i];
	}

	return Average(pDataToAvg,NToAvg);	// Usrednij
}
/********************************************************/


/**
 *
 * @param tab
 * @param lenght
 */
/********************************************************/
void MedianFilter::SortTable(float tab[], uint8_t lenght){

	uint8_t l=0x00, exchange =0x01;
	float tmp=0x00;

	/* Sort tab */
	while(exchange==1)
	{
		exchange=0;
		for(l=0; l<lenght-1; l++)
		{
			if( tab[l] > tab[l+1] )
			{
				tmp = tab[l];
				tab[l] = tab[l+1];
				tab[l+1] = tmp;
				exchange=1;
			}
		}
	}
}
/********************************************************/



/**
 *
 * @param tab
 * @param length
 * @return
 */
/********************************************************/
float MedianFilter::Average(const float* Data, uint8_t length){
	float sum = 0;
	for(uint8_t i=0; i<length; i++) sum += Data[i];

	return sum/length;
}
/********************************************************/

