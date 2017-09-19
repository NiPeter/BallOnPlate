/*
 * Communicator.cpp
 *
 *  Created on: 24 lip 2017
 *      Author: Peter
 */

#include "Communicator.hpp"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"


/***	static functions	***/

static float floatFrom2Ints(int intPart, int fracPart, unsigned int nZeros = 0);
static unsigned int orderOfMagnitude(int number,unsigned int nZeros = 0);

/***						***/


/********************************************************/
/***	Public Functions
 *********************************************************/

/**
 * Constructor
 * @param serial
 */
/********************************************************/
Communicator::Communicator(Serial* serial) :SerialPort(serial)
{
}
/********************************************************/



/**
 * Destructor
 */
/********************************************************/
Communicator::~Communicator()
{
}
/********************************************************/



/**
 * Receive command via Serial interface
 * @return
 */
/********************************************************/
MessagePacket Communicator::ReceivePacket(bool *isPacketReceived)
{

	char c;
	static char msg[CP_MSG_SIZE];
	static int index=0;

	while( index<CP_MSG_SIZE ){

		if( SerialPort->isAvailable() != true ) break;

		c = SerialPort->readChar();

		if(c == '\n'){
			// Terminate string with null character
			msg[index] = '\0';
			index = 0;
			//			strcat(msg,'\0');
			if(isPacketReceived != NULL)	*isPacketReceived = true;
			return unpackMsg(msg);

		}else if(c != '\r'){
			//Receive byte and save it to data_buffer
			//			strcat(msg,&c);
			msg[index++] = c;
		}
		//index++;
	}

	if(index==CP_MSG_SIZE) index = 0;

	if(isPacketReceived != NULL)	*isPacketReceived = false;
	return MessagePacket(fail);
}
/********************************************************/



/**
 * Send command via Serial interface
 * @param cmd
 */
/********************************************************/
void Communicator::SendPacket(MessagePacket packet)
{
	char msg[CP_MSG_SIZE+2]; // +2 for terminating characters store
	SerialPort->writeStr(packMsg(packet,msg));
}
/********************************************************/





/********************************************************/
/***	Private Functions
 *********************************************************/

/**
 * Unpack command from msg string
 * @param msg
 * @return
 */
/********************************************************/
MessagePacket Communicator::unpackMsg(const char * msg)
{
	CmdType_e cmdType = cmdTypeFromMsg(msg); // Pobierz typ komendy
	float param = paramFromMsg(msg); // Pobierz parametr

	return MessagePacket(cmdType, param);
}
/********************************************************/



/**
 * Pack command into msg string
 * @param cmd
 * @param msg
 * @return
 */
/********************************************************/
char * Communicator::packMsg(MessagePacket packet, char * msg)
{
	const char CMDSTR_SIZE = 3;
	char cmdStr[CMDSTR_SIZE];
	char paramStr[CP_MSG_SIZE-CMDSTR_SIZE-3]; // -3 for = and \r\n

	itoa(packet.GetType(),cmdStr,10);
	//strFromFloat(cmd.getParam(),paramStr);
	ftostr(packet.GetParam(),paramStr);

	sprintf(msg,"%s=%s\r\n",cmdStr,paramStr);

	return msg;
}
/********************************************************/



/**
 * Get command type from msg string
 * @param msg
 * @return
 */
/********************************************************/
CmdType_e Communicator::cmdTypeFromMsg(const char* msg){
	return (CmdType_e)(atoi(msg));
}
/********************************************************/



/**
 * Get parameter from msg string
 * @param msg
 * @return
 */
/********************************************************/
float Communicator::paramFromMsg(const char* msg){
	const char * token = msg;

	token += strcspn(msg, "="); // Szukaj znaku "=" i przesu� tam token

	if (*token != '=') return 0; // Brak "=" w wiadomo�ci

	if (*(++token) == '\0') return 0; // Jest "=" ale nic za nim

	int param_int = atoi(token); // pobierz warto�� ca�kowit� parametru

	token += strcspn(token, "."); // Szukaj kropki i  przesu� na ni� wska�nik
	if (*token != '\0') {	// Je�eli wska�nik NIE wskazuje koniec stringa to szukamy warto�ci u�amkowej
		int param_frac;

		token++;	// Przesu� wska�nik na warto�� u�amkow� i...
		param_frac = atoi(token); // pobierz warto�� u�amkow� parametru

		unsigned int nZeros = 0;
		while (*token == '0') {
			token++;
			nZeros++;
		}

		return floatFrom2Ints(param_int, param_frac,nZeros);	// Z�� dwa inty w floata
	}

	return (float)param_int; // Je�eli nie ma warto�ci po . to parametr jest ca�kowity, zapisz go
}
/********************************************************/






/********************************************************/
/***	Static Functions
 *********************************************************/
char * ftostr(float num, char * str){

	const char *tmpSign = (num < 0) ? "-" : "";
	float tmpVal = (num < 0) ? -num : num;

	int tmpInt1 = tmpVal;                  	// Get the integer (678).
	float tmpFrac = tmpVal - tmpInt1;      	// Get fraction (0.0123).
	int tmpInt2 = int(tmpFrac * 10000);  	// Turn into integer (123).

	sprintf (str, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);

	return str;
}

static float floatFrom2Ints(int intPart, int fracPart, unsigned int nZeros) {
	int sign = 1;
	if (intPart < 0) sign = -1;

	return intPart + sign * fracPart / (float)pow(10.0, orderOfMagnitude(fracPart,nZeros)); // oblicz parametr jako float
}

static unsigned int orderOfMagnitude(int number,unsigned int nZeros) {
	unsigned int result = 0;
	while (number) {
		result++;
		number /= 10;
	}
	return result + nZeros;
}
