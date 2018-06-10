//=== LCD ===
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
void SetupLCD()
{
  lcd.begin(16, 2);
}

void setup() {
  SetupLCD();
}

void TestLCD()
{
  lcd.clear(); lcd.setCursor(5, 0); lcd.print("hello,");
  delay(500);
  lcd.clear(); lcd.setCursor(5, 1); lcd.print("World!");
  delay(500);  
}

void loop() {
  TestLCD();
}

