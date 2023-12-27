/* use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *  does not feature an ATMega328 or ATMega2650 controller.
 */
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TCAADDR 0x70

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t oled_array[] = { 7, 6, 5, 3, 2 };
String displayOne;
String displayTwo;
String displayThree;
String displayFour;
String displayFive;
String cueOne;
String cueTwo;
String cueThree;
String cueFour;
String cueFive;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void displaytext(uint8_t i, String newValue) {
  tcaselect(i);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(newValue);
  display.display();
}

void onUfcOptionDisplay1Change(char* newValue) {
    /* your code here */
    displayOne = String(newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);

void onUfcOptionCueing1Change(char* newValue) {
    /* your code here */
    cueOne = String(newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing1Buffer(0x7428, onUfcOptionCueing1Change);

void onUfcOptionDisplay2Change(char* newValue) {
    /* your code here */
    displayTwo = String(newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay2Buffer(0x7436, onUfcOptionDisplay2Change);

void onUfcOptionCueing2Change(char* newValue) {
    /* your code here */
    cueTwo = String(newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing2Buffer(0x742a, onUfcOptionCueing2Change);

void onUfcOptionDisplay3Change(char* newValue) {
    /* your code here */
    displayThree = String(newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay3Buffer(0x743a, onUfcOptionDisplay3Change);

void onUfcOptionCueing3Change(char* newValue) {
    /* your code here */
    cueThree = String(newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing3Buffer(0x742c, onUfcOptionCueing3Change);

void onUfcOptionDisplay4Change(char* newValue) {
    /* your code here */
    displayFour = String(newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay4Buffer(0x743e, onUfcOptionDisplay4Change);

void onUfcOptionCueing4Change(char* newValue) {
    /* your code here */
    cueFour = String(newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing4Buffer(0x742e, onUfcOptionCueing4Change);

void onUfcOptionDisplay5Change(char* newValue) {
    /* your code here */
    displayFive = String(newValue);
}
DcsBios::StringBuffer<4> ufcOptionDisplay5Buffer(0x7442, onUfcOptionDisplay5Change);

void onUfcOptionCueing5Change(char* newValue) {
    /* your code here */
    cueFive = String(newValue);
}
DcsBios::StringBuffer<1> ufcOptionCueing5Buffer(0x7430, onUfcOptionCueing5Change);

void setup() {
  Wire.begin();
  //Serial.begin(115200);
  int8_t i;
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  for(i=0; i<5; i++) {
    tcaselect(oled_array[i]);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
      //Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }
    display.setTextSize(3); // Draw 4X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.display();
  }

  DcsBios::setup();
}

String ufc1 = String("");
String ufc2 = String("");
String ufc3 = String("");
String ufc4 = String("");
String ufc5 = String("");

void loop() {
  DcsBios::loop();
  if(!ufc1.equals(String(cueOne + displayOne))) {
    ufc1 = String(cueOne + displayOne);
    displaytext(7, ufc1);
  }
  if(!ufc2.equals(String(cueTwo + displayTwo))) {
    ufc2 = String(cueTwo + displayTwo);
    displaytext(6, ufc2);
  }
  if(!ufc3.equals(String(cueThree + displayThree))) {
    ufc3 = String(cueThree + displayThree);
    displaytext(5, ufc3);
  }
  if(!ufc1.equals(String(cueFour + displayFour))) {
    ufc4 = String(cueFour + displayFour);
    displaytext(3, ufc4);
  }
  if(!ufc1.equals(String(cueFive + displayFive))) {
    ufc5 = String(cueFive + displayFive);
    displaytext(2, ufc5);
  }

}

