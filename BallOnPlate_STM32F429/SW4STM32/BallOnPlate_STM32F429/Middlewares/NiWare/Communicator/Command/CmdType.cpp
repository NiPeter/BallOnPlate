/*
 * CmdType.cpp
 *
 *  Created on: Sep 17, 2017
 *      Author: peter
 */

#include "CmdType.h"

bool isCommandTypeInRange(CmdType_e cmdType, CmdType_e lower, CmdType_e upper){

	if(lower<upper){
		CmdType_e tmp = upper;
		upper = lower;
		lower = tmp;
	}

	return ( (cmdType<=upper) && (cmdType>=lower) );
}



