#ifndef __DCSBIOS_POLLINGINPUT_H
#define __DCSBIOS_POLLINGINPUT_H

#include "Arduino.h"

bool tryToSendDcsBiosMessage(const char* msg, const char* args);

static bool messageSentOrQueued;

namespace DcsBios {

	class PollingInput {
		private:
			virtual void pollInput();
			int colCount = 0;
			int rowCount = 0;
		public:
			static PollingInput* arrayInputs[][];
			static void setMessageSentOrQueued() { messageSentOrQueued = true; }
			static void pollInputs() {
				for (int colIndex=0; colIndex < colCount; colIndex++) {
					// col: set to output to low
					byte curCol = cols[colIndex];
					pinMode(curCol, OUTPUT);
					digitalWrite(curCol, LOW);

					// row: interate through the rows
					for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
						byte rowCol = rows[rowIndex];
						pinMode(rowCol, INPUT_PULLUP);
						arrayInputs[colIndex][rowIndex]->pollInput(digitalRead(rowCol));
						pinMode(rowCol, INPUT);
						
					}
					// disable the column
					pinMode(curCol, INPUT);
	}
			}
	};
	
}

#endif
