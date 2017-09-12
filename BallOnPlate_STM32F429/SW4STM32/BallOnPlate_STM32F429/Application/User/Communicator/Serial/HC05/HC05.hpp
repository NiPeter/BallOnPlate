/*
 * HC05.hpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_SERIAL_HC05_HPP_
#define APPLICATION_USER_SERIAL_HC05_HPP_

#include "../Serial.hpp"
#include "List/List.hpp"

/***	Hardware STM32	***/
#include "stm32f4xx_hal.h"
#include "usart.h"



class HC05 : public Serial{
private:

	// Hardware handles
	UART_HandleTypeDef* hUART = NULL;
	GPIO_TypeDef* hKeyPort = NULL;
	uint16_t keyPin;

	// Tx and Rx Buffers
	List<char> RxBuffer;
	List<char> TxBuffer;

	// Tx and Rx Bytes
	unsigned char rxByte;	// Receive Byte
	unsigned char txByte;	// Transmit Byte

	bool txOn; // True when transmition is on

public:

	HC05(UART_HandleTypeDef* huart, GPIO_TypeDef* key_port = NULL, uint16_t key_pin = 0);
	virtual ~HC05();


	virtual void begin();
	virtual void flush();

	virtual void writeChar(char c);
	virtual void writeStr(const char* str);

	virtual char readChar();

	virtual bool isAvailable();

	USART_TypeDef* getUARTInstance(){ return hUART->Instance; };

	void processRxISR();
	void processTxISR();

private:

	void receiveIT();
	void transmitIT( char data );

};

#endif /* APPLICATION_USER_SERIAL_HC05_HPP_ */
