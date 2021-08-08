
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

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); //Dimension of the LCD
}

//Blinking Hello World!
void loop() {
  // put your main code here, to run repeatedly:
  lcd.print("  Hello World! "); 
  delay(3000);

  lcd.clear();
  delay(3000);
}
