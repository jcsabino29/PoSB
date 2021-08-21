
/* Name: LCD_Screen_Tester
 * Description: Prints "Hello World!" on LCD Display.
 * Date: 7/12/21
 */
 
//LiquidCrystal library used for LCD 
#include <LiquidCrystal.h>
#include <time.h>
#include "Wire.h"

/*  PIN Layout
 * 1 = Enable
 * 2 = RS
 * 4-7 = D7-D4
 * RW = GND
 * VSS = GND
 * VCC = +
 * A = +
 * K = GDN
 * V0 = MID (POTENTIOMETER)
 * 
 */
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z;                            // variables for gyro raw data
int16_t temperature;                                       // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char *convert_int16_to_str(int16_t i)
{ // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
    sprintf(tmp_str, "%6d", i);
    return tmp_str;
}

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned short timeCtr = 0;

void TimerOn() {
  TCCR1B = 0x0B;
  OCR1A = 125;
  TIMSK1 = 0x02;
  TCNT1 = 0;
  
  _avr_timer_cntcurr = _avr_timer_M;
  SREG |= 0x80;
}

void TimerOff() {
  TCCR1B = 0x00;
}

void TimerISR() {
  TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
  _avr_timer_cntcurr--;
  if (_avr_timer_cntcurr == 0) {
    TimerISR();
    _avr_timer_cntcurr = _avr_timer_M;
  }
}

void TimerSet(unsigned long M) {
  _avr_timer_M = M;
  _avr_timer_cntcurr = _avr_timer_M;
}

// Digital Pin layout
const int touchLPin = 11;
const int touchRPin = 13; 
const int motionLPin= 12;
const int motionRPin = 14;
const int alcoholPin = 3;
const int button1 = 9;
const int button2 = 10;

// Varaibles for detection
int touchLDetected = 0;
int touchRDetected = 0;
int motionLDetected = 0;
int motionRDetected = 0;
int button1_press = 0;
int button2_press = 0;
int alcoholDetected = 0;
int actionTaken = 0;

// Other global vars
char currMessage[99] = "fdsaf";
int currScore = 0;
int highScore = 0;
char currScoreStr[99]; 
char highScoreStr[99];
int armCtr = 1;

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

struct Messages {
  char welcome[99] = "Want to play?"; //Opening instructions, can change
  char twist_head[99] = "Twist the head";
  char detachL_arm[99] = "Detach left arm";
  char detachR_arm[99] = "Detach right arm";
  char give_alcohol[99] = "Breath alcohol";
  char pokeL_eye[99] = "Poke left eye";
  char pokeR_eye[99] = "Poke right eye";
  char success[99] = "Success!";
  char fail[99] = "Fail";
  char scores[99] = "scores";
} message; 

int randomize(int n) {
  randomSeed(analogRead(0));
  n = random(1, 5);
  return n;
}

/*
 * Description: State machine that controls the instructions of our instruction states.
 * Step 1: Twist head
 * Step 2: Give alcohol
 * Step 3: Detach arm.
 * Step 4: Poke eyes
 */
enum instructionStates { startSM, twistSM, alcoholSM, detachLeftArm, detachRightArm, pokeLeftEye, pokeRightEye, successSM, failSM } InstructionSM;
int instructionTick (int state, int touchLDetected, int motionLDetected, int button2) {
  Messages Message;
  int randomNum = 0;

  switch (state) {
    case (startSM):
      if (touchLDetected == 1) {
        randomNum = randomize(randomNum);
        currScore += 100;
        if (randomNum == 1)
        {
          state = twistSM;
        }
        else if (randomNum == 2)
        {
          state = alcoholSM;
        }
        else if (randomNum == 3 && armCtr < 3)
        {
          state = pokeLeftEye;
        }
        else if (randomNum == 4)
        {
          state = pokeLeftRightEye;
        }
        else if (randomNum == 5) {
          state = detachLeftArm;
        }
        else if (randomNum == 6) {
          state = detachRightArm;
        }
      } else { }
      break;
    case (twistSM):
      if (touchLDetected == 1) {
        currScore += 100;
        state = successSM;
      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (alcoholSM):
      if (alcoholDetected) {
        currScore += 100;
        state = successSM;

      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (detachLeftArm):
      if (motionLDetected == 1) {
        currScore += 100;
        armCtr = armCtr + 1;
        state = successSM;
      } else if (button2 == 1 || touchLDetected == 1) {
        state = failSM;
      } else { }
      break;
    case (detachRightArm):
      if (motionLDetected == 1) {
        currScore += 100;
        armCtr = armCtr + 1;
        state = successSM;
      } else if (button2 == 1 || touchLDetected == 1) {
        state = failSM;
      } else { }
      break;
    case (pokeLeftEye):
      if (touchLDetected == 1) {
        currScore += 100;
        state = successSM;
      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (pokeRightEye):
      if (touchRDetected == 1) {
        currScore += 100;
        state = successSM;
      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (successSM):
      if (touchLDetected == 1) {
        randomNum = randomize(randomNum);
        currScore += 100;
        if (randomNum == 1)
        {
          state = twistSM;
        }
        else if (randomNum == 2)
        {
          state = alcoholSM;
        }
        else if (randomNum == 3 && armCtr < 3)
        {
          state = pokeLeftEye;
        }
        else if (randomNum == 4)
        {
          state = pokeRightEye;
        }
        else if (randomNum == 5) {
          state = detachLeftArm;
        }
        else if (randomNum == 6) {
          state = detachRightArm;
        }
      } else { }
      break;
    case (failSM):
      if (button2 == 1) {
        currScore = 0;
        state = startSM;
      } else { }
      break;
    default:
      state = startSM;
      break;
  }

  switch (state) {
    case (startSM):
      memcpy(currMessage, Message.welcome, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (twistSM):
      memcpy(currMessage, Message.twist_head, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (alcoholSM):
      memcpy(currMessage, Message.give_alcohol, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (detachLeftArm):
      memcpy(currMessage, Message.detachL_arm, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (detachRightArm):
      memcpy(currMessage, Message.detachR_arm, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (pokeLeftEye):
      memcpy(currMessage, Message.pokeL_eye, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (pokeRightEye):
      memcpy(currMessage, Message.pokeR_eye, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (successSM):
      //New high score
      if (currScore > highScore) {
        highScore = currScore;
      } else { }

      //Converts int to char
      sprintf(currScoreStr, "%d", currScore);
      sprintf(highScoreStr, "%d", highScore);

      //Places "Score: " --> currMessage
      strcpy(currMessage, "Score: ");

      //Concatenates a series of chars
      strcat(currMessage, currScoreStr);

      //memcpy(currMessage, currScoreStr, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);

      //Repeats same process for high score
      strcpy(currMessage, "High Score: ");
      strcat(currMessage, highScoreStr);
      lcd.setCursor(0, 2);
      lcd.print(currMessage);
      break;
    case (failSM):
      //New high score
      if (currScore > highScore) {
        highScore = currScore;
      } else { }

      //Converts int to char
      sprintf(currScoreStr, "%d", currScore);
      sprintf(highScoreStr, "%d", highScore);

      //Places "Score: " --> currMessage
      strcpy(currMessage, "Score: ");

      //Concatenates a series of chars
      strcat(currMessage, currScoreStr);

      //memcpy(currMessage, currScoreStr, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);

      //Repeats same process for hihg score
      strcpy(currMessage, "High Score: ");
      strcat(currMessage, highScoreStr);
      lcd.setCursor(0, 2);
      lcd.print(currMessage);
      break;
    default:
      break;
  }

  return state;
}


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); //Dimension of the LCD
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(alcoholPin, INPUT);
  pinMode(touchLPin, INPUT);
  pinMode(touchRPin, INPUT);
  pinMode(motionLPin, INPUT);
  pinMode(motionRPin, INPUT); 

  //SETUP FOR GYROSCOPE START
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                 // PWR_MGMT_1 register
  Wire.write(0);                    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  Messages Message;
  int isPressed = 0;
  int state = 0; 
  int timeLimit = 60;
  int touchDetected = 0;
  int motionDetected = 0;
  
  //Timer Initialization
  TimerSet(500);
  TimerOn();
 
  while (timeCtr < timeLimit) {
    button1_press = digitalRead(button1);
    button2_press = digitalRead(button2);
    alcoholDetected = digitalRead(alcoholPin);
    touchLDetected = digitalRead(touchLPin);
    touchRDetected = digitalRead(touchRPin);
    motionLDetected = digitalRead(motionLPin);
    motionRDetected = digitalRead(motionRPin);
    touchDetected = 0;
    motionDetected = 0;
    
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);                        // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false);             // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers
    // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
    accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    temperature = Wire.read() << 8 | Wire.read();     // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
    gyro_x = Wire.read() << 8 | Wire.read();          // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
    gyro_y = Wire.read() << 8 | Wire.read();          // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
    gyro_z = Wire.read() << 8 | Wire.read();          // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
    //Touch detection
    if (touchLDetected || touchRDetected) {
      touchDetected = 1;
    } else { } 

    //Motion Detection
    if (motionLDetected || motionRDetected) {
      motionDetected = 1;
    }

    /*if (touchLDetected || button2_press || motionLDetected || alcoholDetected) {
      isPressed = 1;
    } else {
      isPressed = 0;
    }*/

    //if (isPressed || touchDetected || motionDetected) {
      //while (digitalRead(touchLPin) || digitalRead(touchRPin) || digitalRead(button2) || digitalRead(motionLPin) || digitalRead(motionRPin));
             state = instructionTick(state, touchLDetected, motionLDetected, button2_press);
    //} else { }



    //Time code
    while(!TimerFlag);
    timeCtr++;
    TimerFlag = 0;
    actionTaken = 0;
  } 

  //Resets time limit
  if (timeCtr == timeLimit) {
    timeCtr = timeLimit++;
    lcd.clear();
    lcd.print("Game Over");
  } else { }
}
