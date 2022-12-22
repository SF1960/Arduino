/*

Code to turn on a bank of LEDS based on the position of a potentiometer

*/

#include <WiFiNINA.h>           // needed for on board LEDs

#define LED_RED 12              // connect a Red LED to pin 12
#define LED_GREEN 11            // connect a Green LED to pin 11
#define LED_BLUE 10             // connect a Blue LED to pin 10
#define LED_YELLOW 9            // connect a Yellow LED to pin 9
#define LED_WHITE 8             // connect a White LED to pin 8

#define POTENTIOMETER_PIN A0    // connect the swipe pin of a potentiometer to pin AO

void setup()
{
  //define external LEDs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  
  //define builtin LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  //define RGB LEDs
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
 
  //initialise the monitor
  Serial.begin(9600);
}

void loop()
{
  // get the potentiometer value and map it
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  int mode = map(potentiometerValue, 10, 1010, 0, 6);
  
  delay(100);
  
  // select the code to run based on the value of mode that is returned by the map function
  switch (mode) {
    case 0:
      // all LEDs OFF
      digitalWriteRGB_OFF();
      digitalWrite(LED_BUILTIN, LOW);
      
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW); 
      digitalWrite(LED_WHITE, LOW);
  
      break;
      
    case 1:
      // Red and Inbuilt LED on
      digitalWriteRGB_RED();
      digitalWrite(LED_BUILTIN, HIGH);
      
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW); 
      digitalWrite(LED_WHITE, LOW);

      break;
      
    case 2:
      // Green LED on
      digitalWriteRGB_GREEN();
      
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW); 
      digitalWrite(LED_WHITE, LOW);
    
      break;
      
    case 3:
      // Blue LED on
      digitalWriteRGB_BLUE();
      
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_YELLOW, LOW); 
      digitalWrite(LED_WHITE, LOW);
      
      break;
      
    case 4:
      // Yellow LED on
      digitalWriteRGB_YELLOW();
      
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, HIGH); 
      digitalWrite(LED_WHITE, LOW);
      
      break;
      
    case 5:
      // White LED on
      digitalWriteRGB_WHITE();
      
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW); 
      digitalWrite(LED_WHITE, HIGH);
      
      break;  
      
    case 6:
      // All LEDs on
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_YELLOW, HIGH); 
      digitalWrite(LED_WHITE, HIGH);
      
      break;     
      
    default:
      //digitalWriteRGB(LOW, LOW, LOW);
      //Serial.println("Mode default");
      break;
  }
}

/*
functions to control the RGB LED
*/

void digitalWriteRGB_OFF(){
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
    
}

void digitalWriteRGB_RED(){
  
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  
}

void digitalWriteRGB_GREEN(){
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
    
}

void digitalWriteRGB_BLUE(){
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
    
}

void digitalWriteRGB_YELLOW(){
  
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
    
}

void digitalWriteRGB_WHITE(){
  
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
    
}