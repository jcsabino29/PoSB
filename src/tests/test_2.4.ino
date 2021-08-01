/* Name: main.c
   Description: Initial version is the skeleton code for our system. We just need to integrate the components for our system.
   Date: 7/17/21
*/

//LiquidCrystal library used for LCD
#include <LiquidCrystal.h>

/*  PIN Layout
   1 = Enable
   2 = RS
   4-7 = D7-D4  NOTE: Changed to 3-6 in order to make space for pin
   RW = GND
   VSS = GND
   VCC = +
   A = +
   K = GDN
   V0 = MID (POTENTIOMETER)

*/

const int touchS = 11;
const int motionS = 12;
const int button1 = 9;
const int button2 = 10;
int button1_press = 0;
int button2_press = 0;
int touch_sense = 0;
int motion_sense = 0;
char currMessage[99] = "fdsaf";
int currScore = 0;
int highScore = 0;
int randomNum = 0;
int armCtr = 0;
char currScoreStr[99];
char highScoreStr[99];

int randomize(int n) {
  randomSeed(analogRead(0));
  n = random(4);
  return n;
}


LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

struct Messages {
  char welcome[99] = "Want to play?"; //Opening instructions, can change
  char twist_head[99] = "Twist the head";
  char detach_arm[99] = "Detach the arm";
  char give_alcohol[99] = "Breathe alcohol into mouth";
  char poke_eyes[99] = "Poke the eye";
  char success[99] = "Success!";
  char fail[99] = "Fail";
  char scores[99] = "scores";
} message;

/*
   Description: State machine that controls the instructions of our instruction states.
   Step 1: Twist head = Gyroscope sensor (TODO)
   Step 2: Give alcohol = Alcohol sensor (TODO)
   Step 3: Detach arm = Motion sensor (TODO)
   Step 4: Poke eyes = Touch sensor (RODO)

  TODO: Randomize the instructions below:
  step_1SM = twist head
  step_2SM = alcohol sensor
  step_3SM = motion sensor
  step_4SM = touch sensor
*/

enum instructionStates { startSM, step_1SM, step_2SM, step_3SM, step_4SM, successSM, failSM} InstructionSM;
int instructionTick (int state, int button1, int button2) {
  Messages Message;
  switch (state) {
    case (startSM):
      if (button1 == 1) {
        randomize(randomNum);
        currScore += 100;
        if (randomNum == 1)
        {
          state = step_1SM;
        }
        else if (randomNum == 2)
        {
          state = step_2SM;
        }
        else if (randomNum == 3)
        {
          state = step_3SM;
        }
        else if (randomNum == 4)
        {
          state = step_4SM;
        }
      } else { }
      break;
    case (step_1SM):
      if (button1 == 1) {
        currScore += 100;
        randomize(randomNum);
        if (randomNum == 2)
        {
          state = step_2SM;
        }
        else if (randomNum == 3 && armCtr < 3)
        {
          state = step_3SM;
        }
        else if (randomNum == 4)
        {
          state = step_4SM;
        }
      } else if (button2) {
        state = failSM;
      } else { }
      break;
    case (step_2SM):
      if (button1 == 1) {
        currScore += 100;
        randomize(randomNum);
        if (randomNum == 1)
        {
          state = step_1SM;
        }
        else if (randomNum == 3 && armCtr < 3)
        {
          state = step_3SM;
        }
        else if (randomNum == 4)
        {
          state = step_4SM;
        }
      } else if (button2) {
        state = failSM;
      } else { }
      break;
    case (step_3SM):
      if (button1 == 1) {
        currScore += 100;
        armCtr = armCtr + 1;
        randomize(randomNum);
        if (randomNum == 1)
        {
          state = step_1SM;
        }
        else if (randomNum == 2)
        {
          state = step_2SM;
        }
        else if (randomNum == 4)
        {
          state = step_4SM;
        }
      } else if (button2) {
        state = failSM;
      } else { }
      break;
    case (step_4SM):
      if (button1 == 1) {
        currScore += 100;
        randomize(randomNum);
        if (randomNum == 1)
        {
          state = step_1SM;
        }
        else if (randomNum == 2)
        {
          state = step_2SM;
        }
        else if (randomNum == 3 && armCtr < 3)
        {
          state = step_3SM;
        }
      } else if (button2) {
        state = failSM;
      } else { }
      break;
    case (successSM):
      if (button1 == 1) {
        state = startSM;
        currScore = 0;
      } else { }
    case (failSM):
      if (button1 == 1) {
        currScore = 0;
        state = startSM;
      } else { }
    default:
      break;
  }

  switch (state) {
    case (startSM):
      memcpy(currMessage, Message.welcome, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (step_1SM):
      memcpy(currMessage, Message.twist_head, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (step_2SM):
      memcpy(currMessage, Message.give_alcohol, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (step_3SM):
      memcpy(currMessage, Message.detach_arm, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (step_4SM):
      memcpy(currMessage, Message.poke_eyes, sizeof(currMessage));
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

      //Repeats same process for hihg score
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
  lcd.begin(16, 2); //Dimension of the LCD
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

  while (1) {
    button1_press = digitalRead(button1);
    button2_press = digitalRead(button2);
    if (button1_press || button2_press) {
      isPressed = 1;
    } else {
      isPressed = 0;
    }

    if (isPressed) {
      while (digitalRead(button1) || digitalRead(button2));
      state = instructionTick(state, button1_press, button2_press);
    } else { }
  }
}
