/*
 * IMode.h
 *
 *  Created on: 17 wrz 2017
 *      Author: Peter
 */

#ifndef PLATFORMMODE_H_
#define PLATFORMMODE_H_

#include <Communicator/MessagePacket/MessagePacket.hpp>

#include "PlatformModeCommon.h"

/*
 *
 */
class PlatformMode {
public:
	virtual ~PlatformMode(){};

	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Reset() = 0;

	virtual void Execute(MessagePacket cmd) = 0;

protected:

	StewardPlatform* Master;
};

#endif /* PLATFORMMODE_H_ */
