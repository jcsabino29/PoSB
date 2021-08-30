


/* Name: LCD_Screen_Tester
 * Description: Prints "Hello World!" on LCD Display.
 * Date: 7/12/21
 */
 
//LiquidCrystal library used for LCD 

#include <LiquidCrystal.h>
#include "Wire.h"


/*  PIN Layout
 * 3 = Enable
 * 2 = RS
 * 4-7 = D4-D7
 * RW = GND
 * VSS = GND
 * VDD = +
 * A = +
 * K = GDN
 * V0 = MID (POTENTIOMETER)
 */
//gyro setup start
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
//gyro setup end
//digital pins
const unsigned short button1 = 10;
const unsigned short reset_button = 10;
const unsigned short touchLPin = 9; //head
const unsigned short touchRPin = 13; //eye
const unsigned short motionLPin = 11;
const unsigned short motionRPin = 8;
const unsigned short alcoholPin = 12;
const unsigned short speakerPin = 0;
const unsigned short gyroscopePin = 0;


//digital pin helper vars
unsigned short touchLDetected = 0;
unsigned short touchRDetected = 0;
unsigned short motionLDetected = 0;
unsigned short motionRDetected = 0;
unsigned short alcoholDetected = 0;
//unsigned short twistDetected = 0;

//other global vars
unsigned short button1_press = 0;
unsigned short reset_button_press = 0;
char currMessage[20] = "fdsaf";
unsigned long currScore = 0;
unsigned long highScore = 0;
char currScoreStr[30]; 
char highScoreStr[30];

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


//Time variables
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned short timeLimit = 200;
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

struct Messages {
  char welcome[20] = "Want to play?"; //Opening instructions, can change
  char twist_head[20] = "Turn baby upside down";
  char detachL_arm[20] = "Detach left arm";
  char detachR_arm[20] = "Poke Baby Head";
  char give_alcohol[20] = "Breath alcohol";
  char pokeR_eye[20] = "Jab Head";
  char pokeL_eye[20] = "Poke right eye";
  char success[20] = "Success!";
  char fail[10] = "Fail";
  char scores[10] = "scores";
} message; 

//Other global helper variables 
char detachR_arm[20] = "Detach right arm";
unsigned short prevNum = 0;
unsigned short state = 0;
unsigned short isRDetached = 0;
unsigned short isLDetached = 0;
unsigned int alcVal=0;
/*
 * Description: State machine that controls the instructions of our instruction states.
 * Step 1: Twist head
 * Step 2: Give alcohol
 * Step 3: Detach arm.
 */
enum instructionStates { startSM, twistSM, alcoholSM, pokeLSM, pokeRSM, detachLSM, detachRSM, successSM, failSM} InstructionSM;
int instructionTick (unsigned short state, unsigned short reset_button) {
  Messages Message;
  unsigned short randomNum = random(1, 7);
  switch(state) {
     case(startSM):
        if (reset_button == 1) {
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
        } else { }
        break;
     case(twistSM):
        if (button1_press == 1) {
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(alcoholSM):
        if (alcoholDetected == 1) {
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(pokeLSM):
        if (touchLDetected == 1) {
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
      case(pokeRSM):
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
        if (touchRDetected == 1) {
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(detachLSM):
        if (motionLDetected == 1) {
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
          isLDetached = 1;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(detachRSM):
        if (motionRDetected == 1) {
          while (prevNum == randomNum || (isLDetached && (randomNum == 5)) || (isRDetached && (randomNum == 6))) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          isRDetached = 1;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     default:
        break;
  }

  switch(state) {
     case(startSM):
        memcpy(currMessage, Message.welcome, sizeof(currMessage));
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Press START to");
        lcd.setCursor(0, 1);
        lcd.print("play!...");
        break;
     case(twistSM):
        memcpy(currMessage, Message.twist_head, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(alcoholSM):
        memcpy(currMessage, Message.give_alcohol, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(pokeLSM):
        memcpy(currMessage, Message.pokeR_eye, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(pokeRSM):
        memcpy(Message.pokeL_eye, "Poke right eye", sizeof(currMessage));
        memcpy(currMessage, Message.pokeL_eye, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(detachLSM):
        memcpy(currMessage, Message.detachL_arm, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(detachRSM):
        memcpy(Message.detachL_arm, "Detach right arm", sizeof(currMessage));
        memcpy(currMessage, detachR_arm, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(successSM):
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
     case(failSM):
        //New high score
        if (currScore > highScore) {
          highScore = currScore; 
        } else { }

        timeCtr = timeLimit + 1;
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

        delay(2000);
        state = 0;
        instructionTick(0, 0);
        break;
     default:
        break;
  }
  
  return state;
}


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); //Dimension of the LCD
  pinMode(touchLPin, INPUT);
  pinMode(touchRPin, INPUT);
  pinMode(motionLPin, INPUT);
  pinMode(motionRPin, INPUT);
  pinMode(alcoholPin, INPUT);
  pinMode(speakerPin, INPUT);
  pinMode(gyroscopePin, INPUT);
  pinMode(button1, INPUT);
  pinMode(reset_button, INPUT);
  timeCtr = timeLimit + 1;
  instructionTick(0, 0);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                 // PWR_MGMT_1 register
  Wire.write(0);                    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  Messages Message;
  unsigned short isPressed = 0;
  unsigned short isTouched = 0;
  unsigned short isMoved = 0;
  unsigned short isAlcohol = 0;
  char timeStr[3] = "ad";
  char timeMsg[20] = "Time: ";
  button1_press = 0;
  reset_button_press = digitalRead(reset_button); 

  //Timer Initialization
  TimerSet(500);
  TimerOn();
  
  while (timeCtr < timeLimit) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);                        // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false);             // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers
    // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
    accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    alcVal = analogRead(alcoholPin);
    //Button detection
    reset_button_press = digitalRead(reset_button);
    if (reset_button_press) {
      isPressed = 1;
    } else { isPressed = 0; }
    if(accelerometer_x < -10000){
      button1_press=1; 
    }
    else{
      button1_press=0;  
    }
    //Touch detection
    if (digitalRead(touchLPin)) {
      touchLDetected = 1;
      isTouched = 1;
    } else if (digitalRead(touchRPin)) {
      touchRDetected = 1; 
      isTouched = 1;
    } else { isTouched = 0; touchLDetected = 0; touchRDetected = 0; }

    //Motion detection
    if (digitalRead(motionLPin)) {
      motionLDetected = 1;
      isMoved = 1;
    } else if (digitalRead(motionRPin)) {
      motionRDetected = 1;
      isMoved = 1;
    } else { isMoved = 0; motionLDetected = 0; motionRDetected = 0; }

    //Alcohol detection
    if (alcVal>830) {
      alcoholDetected = 1;
      isAlcohol = 1;
    } else { alcoholDetected = 0; isAlcohol = 0; }

    // State call
    if (isPressed || isTouched || isMoved || isAlcohol) {
      while(digitalRead(reset_button)); 
      state = instructionTick(state, reset_button_press); 
    } else { }

    lcd.setCursor(0,1);
    if ((timeCtr % 2) == 0) { 
      sprintf(timeStr, "%d", ((timeLimit/2) - timeCtr/2));
      //strcat(timeMsg, timeStr);
      lcd.print(timeMsg);
      lcd.print(timeStr);
    } else { }
    //Time code
    while(!TimerFlag);
    timeCtr++;
    TimerFlag = 0;
  }

  //Resets time limit
  if (timeCtr == timeLimit) {
    timeCtr = timeLimit + 1;
    lcd.clear();
    lcd.print("Game Over!");
    
    delay(2000);
    lcd.clear();
    instructionTick(7, reset_button_press); 
    
    delay(2000); 
    instructionTick(0, reset_button_press); 

    state = 0;
  } else { }

  if (digitalRead(reset_button)) {
    while(digitalRead(reset_button)); 
    timeCtr = 0;
    currScore = 0;

    state = instructionTick(random(1, 7), 0); 
    isLDetached = 0;
    isRDetached = 0;
  } else { }
}
