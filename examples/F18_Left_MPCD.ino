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

DcsBios::Switch2Pos leftDdiPb01("LEFT_DDI_PB_01");
DcsBios::Switch2Pos leftDdiPb02("LEFT_DDI_PB_02");
DcsBios::Switch2Pos leftDdiPb03("LEFT_DDI_PB_03");
DcsBios::Switch2Pos leftDdiPb04("LEFT_DDI_PB_04");
DcsBios::Switch2Pos leftDdiPb05("LEFT_DDI_PB_05");

DcsBios::Switch2Pos leftDdiPb06("LEFT_DDI_PB_06");
DcsBios::Switch2Pos leftDdiPb07("LEFT_DDI_PB_07");
DcsBios::Switch2Pos leftDdiPb08("LEFT_DDI_PB_08");
DcsBios::Switch2Pos leftDdiPb09("LEFT_DDI_PB_09");
DcsBios::Switch2Pos leftDdiPb10("LEFT_DDI_PB_10");

DcsBios::Switch2Pos leftDdiPb11("LEFT_DDI_PB_11");
DcsBios::Switch2Pos leftDdiPb12("LEFT_DDI_PB_12");
DcsBios::Switch2Pos leftDdiPb13("LEFT_DDI_PB_13");
DcsBios::Switch2Pos leftDdiPb14("LEFT_DDI_PB_14");
DcsBios::Switch2Pos leftDdiPb15("LEFT_DDI_PB_15");

DcsBios::Switch2Pos leftDdiPb16("LEFT_DDI_PB_16");
DcsBios::Switch2Pos leftDdiPb17("LEFT_DDI_PB_17");
DcsBios::Switch2Pos leftDdiPb18("LEFT_DDI_PB_18");
DcsBios::Switch2Pos leftDdiPb19("LEFT_DDI_PB_19");
DcsBios::Switch2Pos leftDdiPb20("LEFT_DDI_PB_20");

const int ROW_NUM = 4;     //four rows
const int COLUMN_NUM = 5;  //three columns

int pinRows[ROW_NUM] = { 18, 5, 10, 17 };
int pinCols[COLUMN_NUM] = { 16, 12, 7, 6, 8 }; //column 1 not working

static int debounce_count[ROW_NUM][COLUMN_NUM];

DcsBios::Switch2Pos keys[ROW_NUM][COLUMN_NUM] = {
  { leftDdiPb01, leftDdiPb02, leftDdiPb03, leftDdiPb04, leftDdiPb05 },
  { leftDdiPb06, leftDdiPb07, leftDdiPb08, leftDdiPb09, leftDdiPb10 },
  { leftDdiPb11, leftDdiPb12, leftDdiPb13, leftDdiPb14, leftDdiPb15 },
  { leftDdiPb16, leftDdiPb17, leftDdiPb18, leftDdiPb19, leftDdiPb20 }
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
  for (int c = 0; c < COLUMN_NUM; c++) {
    pinMode(pinCols[c], OUTPUT);
    for (int r = 0; r < ROW_NUM; r++) {
      if (digitalRead(pinRows[r]) == HIGH) {
        //Serial.println(c); //we dispalay the right symbol
        keys[r][c].pollInput_Matrix(HIGH);
      } else {
        keys[r][c].pollInput_Matrix(LOW);
      }
    }
    pinMode(pinCols[c], INPUT);
  }
}