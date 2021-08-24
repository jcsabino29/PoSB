
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
const int button2 = 10;
int button1_press = 0;
int button2_press = 0;
char currMessage[20] = "fdsaf";
int currScore = 0;
int highScore = 0;
char currScoreStr[30]; 
char highScoreStr[30];

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

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
  unsigned long prevNum = 0;
/*
 * Description: State machine that controls the instructions of our instruction states.
 * Step 1: Twist head
 * Step 2: Give alcohol
 * Step 3: Detach arm.
 */
enum instructionStates { startSM, twistSM, alcoholSM, pokeLSM, pokeRSM, detachLSM, detachRSM, successSM, failSM} InstructionSM;
int instructionTick (int state, int button1, int button2) {
  Messages Message;
  unsigned long randomNum = random(1, 5);
  switch(state) {
     case(startSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 5); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else { }
        break;
     case(twistSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 5); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(alcoholSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 5); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(pokeLSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 5); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
      case(pokeRSM):
        while (prevNum == randomNum) { randomNum = random(1, 5); };
        if (button1 == 1) {
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(detachLSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 5); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(detachRSM):
        if (button1 == 1) {
          while (prevNum == randomNum) { randomNum = random(1, 5); };
          state = randomNum;
          prevNum = randomNum;
          currScore += 100;
        } else if (button2) {
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
        lcd.print(currMessage);
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
  //Messages Message; 
}

void loop() {
  Messages Message;
  int isPressed = 0;
  button1_press = digitalRead(button1);
  button2_press = digitalRead(button2); 
  int state = 0; 
  unsigned short timeCtr = 0;
  unsigned short timeLimit = 300;

  //Timer Initialization
  TimerSet(100);
  TimerOn();
  while (timeCtr < timeLimit) {
    button1_press = digitalRead(button1);
    button2_press = digitalRead(button2);
    if (button1_press || button2_press) {
      isPressed = 1;
    } else { isPressed = 0; }

    if (isPressed) {
      while(digitalRead(button1) || digitalRead(button2)); 
      state = instructionTick(state, button1_press, button2_press); 
    } else { }

    //Time code
    while(!TimerFlag);
    timeCtr++;
    TimerFlag = 0;
  }

  //Resets time limit
  if (timeCtr == timeLimit) {
    timeCtr = timeLimit++;
    lcd.clear();
    lcd.print("Game Over");
  } else { }
}
