/* use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *  does not feature an ATMega328 or ATMega2650 controller.
 */
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

/* Declare a Master Caution Reset button on pin 10 */
//DcsBios::Switch2Pos masterCautionBtn("UFC_MASTER_CAUTION", 10);
/* Make the LED connected to pin 13 into a Master Caution Light */
//DcsBios::LED mcLed(0x1012, 0x0800, 13);

//DcsBios::Switch2Pos *keys[4][4];

DcsBios::Switch2Pos ufc1("UFC_1");
DcsBios::Switch2Pos ufc2("UFC_2");
DcsBios::Switch2Pos ufc3("UFC_3");
DcsBios::Switch2Pos ufcOs1("UFC_OS1");

DcsBios::Switch2Pos ufc4("UFC_4");
DcsBios::Switch2Pos ufc5("UFC_5");
DcsBios::Switch2Pos ufc6("UFC_6");
DcsBios::Switch2Pos ufcOs2("UFC_OS2");

DcsBios::Switch2Pos ufc7("UFC_7");
DcsBios::Switch2Pos ufc8("UFC_8");
DcsBios::Switch2Pos ufc9("UFC_9");
DcsBios::Switch2Pos ufcOs3("UFC_OS3");

DcsBios::Switch2Pos ufcClr("UFC_CLR");
DcsBios::Switch2Pos ufc0("UFC_0");
DcsBios::Switch2Pos ufcEnt("UFC_ENT");
DcsBios::Switch2Pos ufcOs4("UFC_OS4");

int pinRows[4] = { 6, 7, 8, 9 };
int pinCols[3] = { 2, 3, 4 };

int trueCols;
int trueRows;


const int ROW_NUM = 4;     //four rows
const int COLUMN_NUM = 3;  //three columns
static int debounce_count[COLUMN_NUM][ROW_NUM];

DcsBios::Switch2Pos keys[ROW_NUM][COLUMN_NUM] = {
  { ufc1, ufc2, ufc3 },
  { ufc4, ufc5, ufc6 },
  { ufc7, ufc8, ufc9 },
  { ufcClr, ufc0, ufcEnt }
};


void setup() {
  //Serial.begin(9600);
  // button columns
  int i;
  for (i = 0; i < COLUMN_NUM; i++) {
    pinMode(pinCols[i], OUTPUT);

    // with nothing selected by default
    digitalWrite(pinCols[i], HIGH);
  }
  // button row input lines
  for (i = 0; i < ROW_NUM; i++) {
    pinMode(pinRows[i], INPUT_PULLUP);
  }
  for (int i = 0; i < COLUMN_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++) {
      debounce_count[i][j] = 0;
    }
  }

  DcsBios::setup();
}

void loop() {
  readKey();
  DcsBios::loop();
}


void readKey() {
  for (int c = 0; c < 4; c++) {
    pinMode(pinCols[c], OUTPUT);
    for (int r = 0; r < 4; r++) {
      if (digitalRead(pinRows[r]) == HIGH) {
        //Serial.println(keys[r][c]); //we dispalay the right symbol
        keys[r][c].pollInput_Matrix(HIGH);
      } else {
        keys[r][c].pollInput_Matrix(LOW);
      }
    }
    pinMode(pinCols[c], INPUT);
  }
}