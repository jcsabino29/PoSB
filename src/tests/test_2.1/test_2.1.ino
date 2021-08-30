
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


const int alc = 12;
const int button1 = 9;
const int button2 = 10;
int button1_press = 0;
int button2_press = 0;
char currMessage[99] = "fdsaf";
int currScore = 0;
int highScore = 0;
char currScoreStr[99]; 
char highScoreStr[99];

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

struct Messages {
  char welcome[99] = "Want to play?"; //Opening instructions, can change
  char twist_head[99] = "Twist the head";
  char detach_arm[99] = "Detach the arm";
  char give_alcohol[99] = "Breath alcohol";
  char poke_eyes[99] = "Poke the eye";
  char success[99] = "Success!";
  char fail[99] = "Fail";
  char scores[99] = "scores";
} message; 

/*
 * Description: State machine that controls the instructions of our instruction states.
 * Step 1: Twist head
 * Step 2: Give alcohol
 * Step 3: Detach arm.
 * Step 4: Poke eyes
 */
enum instructionStates { startSM, step_1SM, step_2SM, step_3SM, step_4SM, successSM, failSM} InstructionSM;
int instructionTick (int state, int button1, int button2) {
  Messages Message;
  switch(state) {
     case(startSM):
        if (button1 == 1) {
          state = step_1SM;
          currScore += 100;
        } else { }
        break;
     case(step_1SM):
        if (button1 == 1) {
          state = step_2SM;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(step_2SM):
        if (button1 == 1) {
          state = step_3SM;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(step_3SM):
        if (button1 == 1) {
          state = step_4SM;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(step_4SM):
        if (button1 == 1) {
          state = successSM;
          currScore += 100;
        } else if (button2) {
          state = failSM;
        } else { }
        break;
     case(successSM):
        if (button1 == 1) {
          state = startSM;
          currScore = 0;
        } else { }
     case(failSM):
        if (button1 == 1) {
          currScore = 0;
          state = startSM;
        } else { }
     default:
        break;
  }

  switch(state) {
     case(startSM):
        memcpy(currMessage, Message.welcome, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(step_1SM):
        memcpy(currMessage, Message.twist_head, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(step_2SM):
        memcpy(currMessage, Message.give_alcohol, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(step_3SM):
        memcpy(currMessage, Message.detach_arm, sizeof(currMessage));
        lcd.clear();
        lcd.print(currMessage);
        break;
     case(step_4SM):
        memcpy(currMessage, Message.poke_eyes, sizeof(currMessage));
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
  pinMode(alc, INPUT);
  //Messages Message; 
}

void loop() {
  Messages Message;
  int isPressed = 0;
  button1_press = digitalRead(button1);
  button2_press = digitalRead(button2); 
  int state = 0; 

  while (1) {
    button1_press = digitalRead(button1);
    button2_press = digitalRead(button2);
    int alcVal = analogRead(alc);
    /*
    if (button1_press || button2_press) {
      isPressed = 1;
    } else { isPressed = 0; }

    if (isPressed) {
      while(digitalRead(button1) || digitalRead(button2)); 
      state = instructionTick(state, button1_press, button2_press); 
    } else { } */

    if (alcVal > 200) {
      //lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(alcVal);
      delay(1000);
    } else {
      //lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("There is no alc");
    }
  }
}
