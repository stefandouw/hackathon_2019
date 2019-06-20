#include <LiquidCrystal.h>
#include <LCDKeypad.h>
//contrast step
#define DELTA 10
LCDKeypad lcd;
//initial backlight
unsigned char bckl=150;
int day = 15;
int hour = 15;
int buttonPrevious = KEYPAD_NONE;

void setup() {
    pinMode(10, OUTPUT);
  analogWrite(10, bckl);
  buttonPrevious = lcd.button();
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("    Place a");
  lcd.setCursor(0,1);
  lcd.print("  reservation");
  delay(500);
  lcd.print("    Place a");
  lcd.setCursor(0,1);
  lcd.print("  reservation.");
  delay(500);
  lcd.print("    Place a");
  lcd.setCursor(0,1);
  lcd.print("  reservation..");
  delay(500);
  lcd.print("    Place a");
  lcd.setCursor(0,1);
  lcd.print("  reservation...");
  delay(500);
}

void loop()
{
 //Check button state change
 int buttonNow = lcd.button();
 if ( buttonNow != buttonPrevious) {
   handleAction(buttonNow);
   buttonPrevious = buttonNow;
//   lastDown = millis();
 }
}
 
 void handleAction(int button) {
 switch(button) {
   case KEYPAD_LEFT  :
     day--;
     handleButton();
     break;
   case KEYPAD_RIGHT :
     day++;
     handleButton();
     break;
   case KEYPAD_UP :
     hour++;
     handleButton();
     break;
   case KEYPAD_DOWN :
     hour--;
     handleButton();
     break;
   case KEYPAD_SELECT :
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Reservation set");
     lcd.setCursor(0,1);
     lcd.print(day);
     lcd.print(" June");
     lcd.print(" - ");
     lcd.print(hour);
     lcd.print(":00");
//     // Here you can implement another function to 'reset', in orde to get the second timestamp (which would be the end of the reservation)
//   case KEYPAD_RESET :
//     lcd.clear();
//     lcd.setCursor(0,0);
//     lcd.print("Reservation set");
 }
}

void handleButton() {
     lcd.clear();
     lcd.setCursor(2,0);
     lcd.print("Day: ");
     lcd.print(day);
     lcd.print(" June");
     lcd.setCursor(2,1);
     lcd.print("Hour: ");
     lcd.print(hour);
     lcd.print(":00");
}
