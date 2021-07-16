
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
int button_press = 0;
char currMessage[99] = "fdsaf";

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

struct Messages {
  char welcome[99] = "Want to play?"; //Opening instructions, can change
  char twist_head[99] = "Twist the head";
  char detach_arm[99] = "Detach the arm";
  char give_alcohol[99] = "Breath alcohol";
  char success[99] = "Success!";
  char fail[99] = "Fail";
} message; 

/*
 * Description: State machine that controls the instructions of our instruction states.
 * Step 1: Twist head
 * Step 2: Give alcohol
 * Step 3: Detach arm.
 */
enum instructionStates { startSM, step_1SM, step_2SM, step_3SM, successSM, failSM} InstructionSM;
int instructionTick (int state, int button1) {
  Messages Message;
  switch(state) {
     case(startSM):
        if (button1 == 1) {
          state = step_1SM;
        } else { }
        break;
     case(step_1SM):
        if (button1 == 1) {
          state = step_2SM;
        } else {
         
        }
        break;
     case(step_2SM):
        if (button1 == 1) {
          state = step_3SM;
        } else { }
        break;
     case(step_3SM):
        if (button1 == 1) {
          if (1) { // if user wins 
            state = successSM;
          } else { state = failSM; } 
          state = step_1SM;
        } else { }
        break;
     default:
        break;
  }

  switch(state) {
     case(startSM):
        memcpy(currMessage, Message.welcome, sizeof(currMessage));
        break;
     case(step_1SM):
        memcpy(currMessage, Message.twist_head, sizeof(currMessage));
        break;
     case(step_2SM):
        memcpy(currMessage, Message.give_alcohol, sizeof(currMessage));
        break;
     case(step_3SM):
        memcpy(currMessage, Message.detach_arm, sizeof(currMessage));
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
  //Messages Message; 
}

void loop() {
  Messages Message;
  button_press = digitalRead(button1);
  int state = 0; 

  while (1) {
    button_press = digitalRead(button1);
    if (button_press) {
      while(digitalRead(button1)); 
      state = instructionTick(state, button_press); 
      lcd.clear();
      lcd.print(currMessage);
    } else { }
  }
}
