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

// Digital Pin layout
const int button2 = 10;
const int touchPin = 11;
const int motionPin = 12;

// Varaibles for detection
int button2_press = 0;
int touchDetected = 0;
int motionDetected = 0;

// For strings
char currMessage[99] = "fdsaf";
char currScoreStr[99];
char highScoreStr[99];

// other variables
int currScore = 0;
int highScore = 0;
int armCtr = 1;


int randomize(int n) {
  randomSeed(analogRead(0));
  n = random(1, 5);
  return n;
}


LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

struct Messages {
  char welcome[99] = "Poke my eye to "; //Opening instructions, can change
  char twist_head[99] = "Neck cramp";
  char detach_arm[99] = "Arm hurtie";
  char give_alcohol[99] = "Baby thiwsty";
  char poke_eyes[99] = "Eye itchy";
  char success[99] = "Success!";
  char fail[99] = "Fail";
  char scores[99] = "scores";
} message;

/*
   Description: State machine that controls the instructions of our instruction states.
   Step 1: Twist head = Gyroscope sensor (TODO)
   Step 2: Give alcohol = Alcohol sensor (TODO)
   Step 3: Detach arm = Motion sensor
   Step 4: Poke eyes = Touch sensor
*/

enum instructionStates { startSM, twistSM, alcoholSM, detachSM, pokeSM, successSM, failSM} InstructionSM;
int instructionTick (int state, int touchDetected, int motionDetected, int button2) {
  Messages Message;
  int randomNum = 0;

  switch (state) {
    case (startSM):
      if (touchDetected == 1) {
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
          state = detachSM;
        }
        else if (randomNum == 4)
        {
          state = pokeSM;
        }
      } else { }
      break;
    case (twistSM):
      if (touchDetected == 1) {
        currScore += 100;
        state = successSM;
      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (alcoholSM):
      if (touchDetected == 1) {
        currScore += 100;
        state = successSM;

      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (detachSM):
      if (motionDetected == 1) {
        currScore += 100;
        armCtr = armCtr + 1;
        state = successSM;
      } else if (button2 == 1 || touchDetected == 1) {
        state = failSM;
      } else { }
      break;
    case (pokeSM):
      if (touchDetected == 1) {
        currScore += 100;
        state = successSM;
      } else if (button2 == 1) {
        state = failSM;
      } else { }
      break;
    case (successSM):
      if (touchDetected == 1) {
        // state = startSM;
        randomNum = randomize(randomNum);
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
          state = detachSM;
        }
        else if (randomNum == 4)
        {
          state = pokeSM;
        }
      } else {}
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
      strcpy(currMessage, "play");
      strcat(currMessage, highScoreStr);
      lcd.setCursor(0, 2);
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
    case (detachSM):
      memcpy(currMessage, Message.detach_arm, sizeof(currMessage));
      lcd.clear();
      lcd.print(currMessage);
      break;
    case (pokeSM):
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
  lcd.begin(16, 2); //Dimension of the LCD
  pinMode(button2, INPUT);
  pinMode(touchPin, INPUT);
  pinMode(motionPin, INPUT);
  //Messages Message;
}

void loop() {
  Messages Message;
  int state = 0;
  int isPressed = 0;
  button2_press = digitalRead(button2);
  touchDetected = digitalRead(touchPin);
  motionDetected = digitalRead(motionPin);

  while (1) {
    button2_press = digitalRead(button2);
    touchDetected = digitalRead(touchPin);
    motionDetected = digitalRead(motionPin);
    if (touchDetected || button2_press || motionDetected) {
      isPressed = 1;
    } else {
      isPressed = 0;
    }

    if (isPressed) {
      while (digitalRead(touchPin) || digitalRead(button2) || digitalRead(motionPin));
             state = instructionTick(state, touchDetected, motionDetected, button2_press);
    } else { }
}
}
