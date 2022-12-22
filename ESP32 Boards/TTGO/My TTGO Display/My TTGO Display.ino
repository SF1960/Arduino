
//
#include <SPI.h>
#include <TFT_eSPI.h>             // Hardware-specific library
//#include <ArduinoJson.h>          // https://github.com/bblanchon/ArduinoJson.git
//#include <NTPClient.h>            // https://github.com/taranais/NTPClient

TFT_eSPI tft = TFT_eSPI();        // Invoke custom library

#define TFT_GREY 0x5AEB
#define lightblue 0x01E9
#define darkred 0xA041
#define blue 0x5D9B
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#include "Orbitron_Medium_20.h"
#include <WiFiUdp.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h> // this library allows for connection to available networks without hardcoding

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

// An array that holds the brightness steps 
int backlight[6] = {10,30,60,120,180,220};  
byte b=3; // a variable that selects the brightness steps and applies them to each objectint
int Landscape = 1;
int Portrait = 0;
bool inv = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(35,INPUT);               // right button
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(WHITE,TFT_BLACK);  tft.setTextSize(1);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, backlight[b]);

  Serial.begin(115200);

  // start up screen text display of connection status
  // default colour and font size
  tft.setRotation(Landscape);       // set LCD orientation
  tft.setTextColor(GREEN,TFT_BLACK);  tft.setTextSize(2);
  tft.println("Check your mobile ");
  tft.println("Connect to TTGO_WiFi");
  tft.println("enter WiFi details");

  // Instead of WiFi.begin() use the more sophisticated WiFiManager library
  WiFiManager wm;
  // Define a text box to get further user information when connecting to a WiFi network
  //WiFiManagerParameter town("TOWN","Enter your town","London",20);
  //wm.addParameter(&town);
  wm.resetSettings();                        // can comment out so that a saved WiFi network will automatically connect
  bool res;
  res = wm.autoConnect("TTGO_WiFi");        // set up a WiFi access point called TTGI_WiFi (no password needed)
  if (!res) {
    Serial.println("Failed to connect.");
    // ESP.restart();
  }

  // loop while trying to connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    tft.print(".");
  }

tft.println("CONNECTED to WiFi");

}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(35)==0){
    inv=!inv;
    tft.invertDisplay(inv);}

  delay(500);

}
