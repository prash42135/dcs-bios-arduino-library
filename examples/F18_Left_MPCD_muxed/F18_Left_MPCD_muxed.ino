/* use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *  does not feature an ATMega328 or ATMega2650 controller.
 */
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

#define NUMBER_OF_SHIFT_CHIPS 1
#define DATA_WIDTH NUMBER_OF_SHIFT_CHIPS * 8

/* Declare a Master Caution Reset button on pin 10 */
//String masterCautionBtn("UFC_MASTER_CAUTION", 10);
/* Make the LED connected to pin 13 into a Master Caution Light */
//DcsBios::LED mcLed(0x1012, 0x0800, 13);

//String *keys[4][4];

DcsBios::Switch2Pos leftDdiPb01("LEFT_DDI_PB_01", 1);
DcsBios::Switch2Pos leftDdiPb02("LEFT_DDI_PB_02", 1);
DcsBios::Switch2Pos leftDdiPb03("LEFT_DDI_PB_03", 1);
DcsBios::Switch2Pos leftDdiPb04("LEFT_DDI_PB_04", 1);
DcsBios::Switch2Pos leftDdiPb05("LEFT_DDI_PB_05", 1);

DcsBios::Switch2Pos leftDdiPb06("LEFT_DDI_PB_06", 1);
DcsBios::Switch2Pos leftDdiPb07("LEFT_DDI_PB_07", 1);
DcsBios::Switch2Pos leftDdiPb08("LEFT_DDI_PB_08", 1);
DcsBios::Switch2Pos leftDdiPb09("LEFT_DDI_PB_09", 1);
DcsBios::Switch2Pos leftDdiPb10("LEFT_DDI_PB_10", 1);

DcsBios::Switch2Pos leftDdiPb11("LEFT_DDI_PB_11", 1);
DcsBios::Switch2Pos leftDdiPb12("LEFT_DDI_PB_12", 1);
DcsBios::Switch2Pos leftDdiPb13("LEFT_DDI_PB_13", 1);
DcsBios::Switch2Pos leftDdiPb14("LEFT_DDI_PB_14", 1);
DcsBios::Switch2Pos leftDdiPb15("LEFT_DDI_PB_15", 1);

DcsBios::Switch2Pos leftDdiPb16("LEFT_DDI_PB_16", 1);
DcsBios::Switch2Pos leftDdiPb17("LEFT_DDI_PB_17", 1);
DcsBios::Switch2Pos leftDdiPb18("LEFT_DDI_PB_18", 1);
DcsBios::Switch2Pos leftDdiPb19("LEFT_DDI_PB_19", 1);
DcsBios::Switch2Pos leftDdiPb20("LEFT_DDI_PB_20", 1);

const int ROW_NUM = 5;     //four rows
const int COLUMN_NUM = 4;  //three columns

int hc165_LoadPin_1 = 11;
int hc165_EnablePin_15 = 13;
int hc165_DataPin_10 = 12;
int hc165_ClockPin_2 = 10;

//Pin connected to ST_CP of 74HC595
int hc595_latchPin_12 = 8;
//Pin connected to SH_CP of 74HC595
int hc595_clockPin_11 = 7;
////Pin connected to DS of 74HC595
int hc595_dataPin_14 = 9;

int bit = 0;
int num_to_send = 1;

DcsBios::Switch2Pos keys[COLUMN_NUM][ROW_NUM] = {
  { leftDdiPb01, leftDdiPb02, leftDdiPb03, leftDdiPb04, leftDdiPb05 },
  { leftDdiPb06, leftDdiPb07, leftDdiPb08, leftDdiPb09, leftDdiPb10 },
  { leftDdiPb11, leftDdiPb12, leftDdiPb13, leftDdiPb14, leftDdiPb15 },
  { leftDdiPb16, leftDdiPb17, leftDdiPb18, leftDdiPb19, leftDdiPb20 }
};

void setup() {

  pinMode(hc165_DataPin_10, INPUT);
  pinMode(hc165_ClockPin_2, OUTPUT);
  pinMode(hc165_LoadPin_1, OUTPUT);
  pinMode(hc165_EnablePin_15, OUTPUT);

  pinMode(hc595_latchPin_12, OUTPUT);
  pinMode(hc595_clockPin_11, OUTPUT);
  pinMode(hc595_dataPin_14, OUTPUT);

  digitalWrite(hc165_EnablePin_15, LOW);

  DcsBios::setup();
}

void loop() {
  readKey();
  //delay(3000);
  DcsBios::loop();
  //Serial.println("==============================");
}

long bitVal;
    unsigned long bytesVal = 0;

void readKey() {
  for (int c = 0; c < COLUMN_NUM; c++) {
    num_to_send = 1;
    num_to_send = num_to_send << c;
    //Serial.println(num_to_send);
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(hc595_latchPin_12, LOW);
    // shift out the bits:
    shiftOut(hc595_dataPin_14, hc595_clockPin_11, MSBFIRST, num_to_send);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(hc595_latchPin_12, HIGH);
    delayMicroseconds(10);

    // Now read values from 165:
    digitalWrite(hc165_LoadPin_1, LOW);
    delayMicroseconds(5);
    digitalWrite(hc165_LoadPin_1, HIGH);
    delayMicroseconds(5);
    digitalWrite(hc165_ClockPin_2, HIGH);
    digitalWrite(hc165_EnablePin_15, LOW);
    byte incoming = shiftIn(hc165_DataPin_10, hc165_ClockPin_2, MSBFIRST);
    digitalWrite(hc165_EnablePin_15, HIGH);
    for (byte i=0; i<5; i++) {
      bool state = bitRead(incoming, i);
      if (state) {
        //Serial.println(c); //we dispalay the right symbol
        keys[c][i].pollInput_Matrix(HIGH);
      } else {
        keys[c][i].pollInput_Matrix(LOW);
      }
  }
  }
}