#ifndef __DCSBIOS_POLLINGINPUT_H
#define __DCSBIOS_POLLINGINPUT_H

#include "Arduino.h"

bool tryToSendDcsBiosMessage(const char* msg, const char* args);

static bool messageSentOrQueued;

namespace DcsBios {

	class PollingInput {
		private:
			virtual void pollInput();
		public:
			static PollingInput* arrayInputs[][];
			static void setMessageSentOrQueued() { messageSentOrQueued = true; }
	};
	
}

#endif
