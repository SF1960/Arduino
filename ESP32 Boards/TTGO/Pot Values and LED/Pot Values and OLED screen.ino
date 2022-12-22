/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial

  Updated by Steve Fuller Dec 2022

  Display a potentiometers value on an OLED screen
  Connect the wiper from a potentiometer to pin 36
  Connect either side to VCC and GND
*/
//#include <TFT_eSPI.h>            // Hardware-specific library
#include "TFT_eSPI.h"
#include "knob_icon.h"           // a potentiometer image Use http://www.rinkydinkelectronics.com/
#include "font.h"                // add a custom font file Use http://oleddisplay.squix.ch/#/home
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

// define screen colour constants
#define TFT_GREY    0x5AEB
#define TFT_LIGHTBLUE 0x2D18
#define TFT_ORANGE  0xFB60
#define TFT_PURPLE  0xFB9B
#define TFT_BLACK   0x0000
#define TFT_GRAY    0x8410
#define TFT_WHITE   0xFFFF
#define TFT_RED     0xF800
#define TFT_ORANGE  0xFA60
#define TFT_YELLOW  0xFFE0  
#define TFT_LIME    0x07FF
#define TFT_GREEN   0x07E0
#define TFT_CYAN    0x07FF
#define TFT_AQUA    0x04FF
#define TFT_BLUE    0x001F
#define TFT_MAGENTA 0xF81F
#define TFT_PINK    0xF8FF

// define scree constants
#define Portrait  0  // Portrait Screen
#define Landscape 1  // Landscape Screen

// text line positions
#define Pot_line 130
#define Pot_bar 157
#define Map_line 185

// define the potentiometer variables
int oldpotValue = 0;
int oldmapValue = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // set up on board push buttons - although this sketch does not use the buttons
  pinMode(0, INPUT);
  pinMode(35,INPUT);

  // initialise the screen
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(Portrait);
  tft.setSwapBytes(true);

  // display image
  tft.pushImage(20,40,96,96,knob_icon);

  tft.setFreeFont(&Rock_Salt_Regular_20);

  // configure the screen
  tft.setCursor(20, 20, 2);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  tft.drawString("Potentiometer",0,0);
  //tft.println("POTENTIOMETER");
  tft.drawLine(20, 40, 120, 40, TFT_GREEN);

  tft.setCursor(25, 220, 2);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.print("(C) SGF 2022");
  tft.drawLine(20, 215, 120, 215, TFT_AQUA);

  // default screen background and text colour
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int potValue = analogRead(A0);
  int mapValue = map(potValue, 0, 4095, 0, 100);

  // print out the value you read on the serial monitor:
  Serial.println(potValue);
  Serial.println(mapValue);

  // the OLED screen does not overwrite previous text or values
  // this if statement checks whether the value has changed
  // and clears the value so that old digits aren't displayed in error
  if (oldpotValue != potValue){
    tft.setCursor(10, Pot_line, 4); tft.print("POT:            ");           // clear old pot value
    tft.setCursor(10, Pot_line, 4); tft.println("POT: " + String(potValue)); // write new value
    tft.fillRect(20, Pot_bar, 200, 20, TFT_BLACK);                          // erase previous bar
    tft.fillRect(20, Pot_bar, mapValue, 20, TFT_AQUA);                      // display new bar
    oldpotValue = potValue;                                             // reset oldpotValue
  }
  else{
    tft.setCursor(10, Pot_line, 4);    
    tft.println("POT: " + String(potValue)); 
  }

  // the OLED screen does not overwrite previous text or values
  // this if statement checks whether the value has changed
  // and clears the value so that old digits aren't displayed in error
  if (oldmapValue != mapValue){
    tft.setCursor(10, Map_line, 4); tft.print("MAP:          ");                 // clear old map value
    tft.setCursor(10, Map_line, 4); tft.println("MAP: "+ String(mapValue, DEC)); // write new value
    oldmapValue = mapValue;
  }
  else{
    tft.setCursor(10, Map_line, 4);
    tft.println("MAP: "+ String(mapValue, DEC));
  }

  delay(100);  // delay in between reads for stability
}
