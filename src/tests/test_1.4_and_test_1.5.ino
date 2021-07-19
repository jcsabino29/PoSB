/* Name: touch_motion_sensor
 * Description: This file is used solely to test the functionality motion and touch sensors.
 * Note: Should probably make a switch case in order to better integrate later on. 
 * When doing the Mocking test, the motion sensor is a bit flimsy.
 * May or may not take Motion sensor out of design due to attach/detach instructions. Needs further testing.
 * Date: 7/16/2021
 * The circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 10
 * LCD D5 pin to digital pin 11
 * LCD D6 pin to digital pin 12
 * LCD D7 pin to digital pin 13
 * Touch sensor to digital pin 7
 * Motion sensor to digital pin 6
*/

// include the library code for LCD Screen:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
const int TouchPin = 7;
const int MotionPin = 6;
int buzzerPin = 3;

void setup() {
  // define inputs and outputs
  pinMode(TouchPin, INPUT);
  pinMode(MotionPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);

}

void loop() {
  
  // variables to detect if touch for touch sensor, movement for motion sensor
  int sensorDetected = digitalRead(TouchPin); 
  int motionDetected = digitalRead(MotionPin);
  
  // sensor is being touched, motion sensor detects movement
  if(sensorDetected == 1 && motionDetected == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("ur touching me ;)");
    lcd.setCursor(0, 1);
    lcd.print("i see you");
    digitalWrite(buzzerPin, HIGH);
    delay(1);
    digitalWrite(buzzerPin, LOW);
  }
  
  // sensor is being touched, motion sensor doesnt detect movement
  else if (sensorDetected == 1 && motionDetected == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("ur touching me ;)");    
    lcd.setCursor(0, 1);
    lcd.print("i dont see you");
    digitalWrite(buzzerPin, HIGH);
    delay(1);
    digitalWrite(buzzerPin, LOW);
  }
  // sensor isnt being touched, motion sensor detects movement
  else if (sensorDetected == 0 && motionDetected == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("ur not touching me :(");    
    lcd.setCursor(0, 1);
    lcd.print("i see you");
  }
  // sensor isnt being touched, motion sensor doesnt detects movement
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("ur not touching me :(");
    lcd.setCursor(0, 1);
    lcd.print("i dont see you");
  }
}
