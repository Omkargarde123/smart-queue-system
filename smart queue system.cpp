
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BTN_NEXT 4
#define BTN_CALL 5
#define BUZZER 18

int tokenNumber = 0;
int currentToken = 0;

void beep() {
  tone(BUZZER, 2000);
  delay(300);
  noTone(BUZZER);
}

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_CALL, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Smart Queue");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  if (digitalRead(BTN_NEXT) == LOW) {
    tokenNumber++;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Token Generated");
    lcd.setCursor(0, 1);
    lcd.print("Token: ");
    lcd.print(tokenNumber);

    delay(300);
  }

  if (digitalRead(BTN_CALL) == LOW) {

    if (currentToken < tokenNumber) {
      currentToken++;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Now Serving:");
      lcd.setCursor(0, 1);
      lcd.print("Token: ");
      lcd.print(currentToken);

      beep(); // 🔔 working beep

    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Tokens Left");
    }

    delay(300);
  }
} 
```
