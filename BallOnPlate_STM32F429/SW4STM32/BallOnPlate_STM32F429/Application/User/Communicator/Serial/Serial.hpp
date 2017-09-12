/*
 * Serial.hpp
 *
 *  Created on: 21 lip 2017
 *      Author: Peter
 */

#ifndef APPLICATION_USER_SERIAL_SERIAL_HPP_
#define APPLICATION_USER_SERIAL_SERIAL_HPP_

/***	SERIAL INTERFACE	***/
class Serial{

public:
	virtual ~Serial(){};

	virtual void begin() = 0;
	virtual void flush() = 0;

	virtual void writeChar(char c) = 0;
	virtual void writeStr(const char* str) = 0;

	virtual char readChar() = 0;

	virtual bool isAvailable() = 0;

};

#endif /* APPLICATION_USER_SERIAL_SERIAL_HPP_ */
