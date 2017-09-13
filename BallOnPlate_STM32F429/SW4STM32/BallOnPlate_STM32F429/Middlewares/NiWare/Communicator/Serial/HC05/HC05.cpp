/*
 * HC05.cpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */


#include "HC05.hpp"


/**
 * HC05 Constructor
 * @param huart
 * @param key_port
 * @param key_pin
 */
/********************************************************/
HC05::HC05(UART_HandleTypeDef* huart, GPIO_TypeDef* key_port, uint16_t key_pin):
				hUART(huart),
				hKeyPort(key_port),
				keyPin(key_pin),
				txOn(false){ rxByte = 0; txByte = 0;};
/********************************************************/

/**
 * HC05 Destructor
 */
/********************************************************/
HC05::~HC05(){

}
/********************************************************/



/**
 * Begin listening
 */
/********************************************************/
void HC05::begin(){

	receiveIT();

}
/********************************************************/



/**
 * Clear RxBuffer
 */
/********************************************************/
void HC05::flush(){
	while( !RxBuffer.IsEmpty())
		RxBuffer.Pop();
}
/********************************************************/



/**
 * Read character
 * @return
 */
/********************************************************/
char HC05::readChar(){

	while( RxBuffer.IsEmpty() ){}; // Wait for data

	return RxBuffer.Pop();
}
/********************************************************/



/**
 * Is data available to read?
 * @return
 */
/********************************************************/
bool HC05::isAvailable(){
	return !RxBuffer.IsEmpty();
}
/********************************************************/



/**
 * Write character to stream
 * @param c
 * @return
 */
/********************************************************/
void HC05::writeChar(char c){

	if( !txOn ) {
		transmitIT(c);
		return;
	}

	TxBuffer.Push(c);
}
/********************************************************/



/**
 * Write string to buffer
 * @param str
 */
/********************************************************/
void HC05::writeStr(const char* str){

	while((*str) != '\0'){
		writeChar(*str);
		str++;
	}



}
/********************************************************/





/**
 * Receive Interrupt Service Routine function
 *
 * Must be called from USART Rx ISR
 */
/********************************************************/
void HC05::processRxISR(){

	RxBuffer.Push(rxByte);
	receiveIT();

}
/********************************************************/



/**
 * Transmit Interrupt Service Routine function
 *
 * Must be called from USART Tx ISR
 */
/********************************************************/
void HC05::processTxISR(){

	if( TxBuffer.IsEmpty() ){
		txOn = false;
		return;
	}
	transmitIT( TxBuffer.Pop() );

}
/********************************************************/




/********************************************************/
/***	Private Functions	***/
/********************************************************/
/********************************************************/


/**
 * Receive char in IT mode
 */
/********************************************************/
void HC05::receiveIT(){

	HAL_UART_Receive_IT(hUART,&rxByte,1);

}
/********************************************************/



/**
 * Transmit char in IT mode
 * @param data
 */
/********************************************************/
void HC05::transmitIT( char data ){

	txOn = true;
	txByte = data;
	HAL_UART_Transmit_IT(hUART,&txByte,1);

}
/********************************************************/

