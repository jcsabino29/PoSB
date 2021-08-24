
/* Name: LCD_Screen_Tester
 * Description: Prints "Hello World!" on LCD Display.
 * Date: 7/12/21
 */
 
//LiquidCrystal library used for LCD 
#include <LiquidCrystal.h>

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

const int button1 = 9;
const int reset_button = 10;
int button1_press = 0;
int reset_button_press = 0;
char currMessage[20] = "fdsaf";
int currScore = 0;
int highScore = 0;
char currScoreStr[30]; 
char highScoreStr[30];

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned short timeLimit = 150;
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
  char twist_head[20] = "Twist the head";
  char detachL_arm[20] = "Detach left arm";
  char give_alcohol[20] = "Breath alcohol";
  char pokeL_eye[20] = "Poke left eye";
  char success[20] = "Success!";
  char fail[10] = "Fail";
  char scores[10] = "scores";
} message; 

  char detachR_arm[20] = "Detach right arm";
  unsigned short prevNum = 0;
  unsigned short state = 0;
/*
 * Description: State machine that controls the instructions of our instruction states.
 * Step 1: Twist head
 * Step 2: Give alcohol
 * Step 3: Detach arm.
 */
enum instructionStates { startSM, twistSM, alcoholSM, pokeLSM, pokeRSM, detachLSM, detachRSM, successSM, failSM} InstructionSM;
int instructionTick (int state, int button1, int reset_button) {
  Messages Message;
  unsigned short randomNum = random(1, 7);
  switch(state) {
     case(startSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
<<<<<<< HEAD
=======
          highScore = highScore; //NOTE: lmk if this accidentally messes things up
          currScore += 100;
>>>>>>> 6ffe5eb9aadec633a7b2809aef223dcfbfb5b4ad
        } else { }
        break;
     case(twistSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(alcoholSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(pokeLSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
      case(pokeRSM):
        while (prevNum == randomNum) { randomNum = random(1, 7); };
        if (button1 == 1) {
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(detachLSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (reset_button) {
          state = failSM;
        } else { }
        break;
     case(detachRSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 7); };
          state = randomNum;
          prevNum = randomNum;
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
        memcpy(currMessage, Message.pokeL_eye, sizeof(currMessage));
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
        instructionTick(0, 0, 0);
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
  pinMode(reset_button, INPUT);
  timeCtr = timeLimit + 1;
  instructionTick(0, 0, 0);
}

void loop() {
  Messages Message;
  unsigned short isPressed = 0;
  button1_press = digitalRead(button1);
  reset_button_press = digitalRead(reset_button); 

  //Timer Initialization
  TimerSet(100);
  TimerOn();
  
  while (timeCtr < timeLimit) {
    button1_press = digitalRead(button1);
    reset_button_press = digitalRead(reset_button);
    if (button1_press || reset_button_press) {
      isPressed = 1;
    } else { isPressed = 0; }

    if (isPressed) {
      while(digitalRead(button1) || digitalRead(reset_button)); 
      state = instructionTick(state, button1_press, reset_button_press); 
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
    instructionTick(7, button1_press, reset_button_press); 
    
    delay(2000); 
    instructionTick(0, button1_press, reset_button_press); 

    state = 0;
  } else { }

  if (digitalRead(reset_button)) {
    while(digitalRead(reset_button)); 
    timeCtr = 0;
    currScore = 0;

    state = instructionTick(random(1, 7), 0, 0); 
    //isLDetached = 0;
    //isRDetached = 0;
  } else { }
}
