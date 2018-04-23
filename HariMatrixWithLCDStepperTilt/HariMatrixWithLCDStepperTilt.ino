//=== MATRIX ===
// Rows are anodes(positive), Columns are cathodes(negative)
byte row0Pin = 2;  // D2(row0),D3,D4,D5, D6,D7,D8,D9(row7) controls the Rows

// Shift register controls the Columns (QA=col0, QH=col7)
int latchPin = A1;  //Pin connected to RCLK/ST_CP of 74HC595
int clockPin = A0;  //Pin connected to SRCLK/SH_CP of 74HC595
int dataPin = A2;   //Pin connected to SER/DS of 74HC595

byte bitmap[8];
byte smiley[8] = {
  B01111110,
  B10000001,
  B10100101,
  B10000001,
  B10100101,
  B10111101,
  B10000001,
  B01111110,
};

//=== LCD ===
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//=== STEPPER ===
#include <CheapStepper.h>
CheapStepper stepper(6, 7, 8, 9);

//=== Tilt Switch ===
int tiltPin = 10; // D10

void SetupMatrix()
{
  // Setup Matrix Row (Shift Register)
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Setup Matrix Column (GPIO)
  for (byte i = 0; i < 8; i++)
  {
    pinMode(row0Pin + i, OUTPUT);
    digitalWrite(row0Pin + i, LOW);
  }
}

void SetupLCD()
{
  lcd.begin(16, 2);
}

void SetupTiltSwitch()
{
  pinMode(tiltPin, INPUT_PULLUP);
}

void LiftMeUp()
{
  lcd.clear();
  lcd.print("Hi! Pick me up");
  lcd.setCursor(4, 1);  lcd.print("to start...");

  while (digitalRead(tiltPin) != 0)
  {
    lcd.setCursor(0, 0);  lcd.print("Hi!           ");
    delay(500);
    lcd.setCursor(0, 0);  lcd.print("Hi! Pick me up");
    delay(500);
  }
}

void setup() {
  SetupMatrix();
  SetupLCD();
  SetupTiltSwitch();
}

void loop() {
  LiftMeUp();

  lcd.clear();   lcd.setCursor(5, 0); lcd.print("Hello!");
  delay(500);
  lcd.setCursor(0, 1); lcd.print("Nice to meet you!");
  delay(500);

  Wave();
  

  for (byte i = 0; i < 4; i++)
  {
    delay(500);
    ClearBitmap();
    DrawSmiley();
    for (int d = 0; d < 15x0; d++) Refresh();

//    ClearBitmap();
//    DrawX();
//    for (int d = 0; d < 100; d++) Refresh();
  }

  ClearBitmap(); Refresh();
}

void MoveStepper(bool moveClockwise, int howManySteps)
{
  for (int s = 0; s < howManySteps; s++) {
    stepper.step(moveClockwise); // 4096 of these equals 360 degree rotation
  }
}

void Wave()
{
  for (byte i = 0; i < 3; i++) {
    MoveStepper(true, 4096 / 8);
    MoveStepper(false, 4096 / 8);
  }
}
void DrawX()
{
  for (byte i = 0; i < 8; i++)
  {
    bitSet(bitmap[i], i);
    bitSet(bitmap[i], 7 - i);
  }
}

void DrawBox()
{
  bitmap[0] = 255;
  bitmap[7] = 255;
  for (byte i = 0; i < 8; i++)
  {
    bitSet(bitmap[i], 0);
    bitSet(bitmap[i], 7);
  }
}

void DrawSmiley()
{
  for (byte i = 0; i < 8; i++)
    bitmap[i] = smiley[i];
}

void ClearBitmap()
{
  for (byte i = 0; i < 8; i++)
  {
    bitmap[i] = 0;
  }
}
void Refresh()
{
  for (byte r = 0; r < 8; r++)
  {
    int row = row0Pin + r; // 2,3,4,5, 6,7,8,9

    // Prepare the column bits for this row
    digitalWrite(latchPin, LOW); // Don't change output while we shift
    shiftOut(dataPin, clockPin, MSBFIRST, ~bitmap[r]);
    digitalWrite(latchPin, HIGH); // BAM! to all 8 outputs at once!

    digitalWrite(row, HIGH); // Turn on this row
    delayMicroseconds(1000); // Let humans see it
    digitalWrite(row, LOW); // Turn row off in preparation for next row
  }
}

void ScanTest()
{
  for (byte r = 0; r < 8; r++)
  {
    int row = 2 + r; // 2,3,4,5, 6,7,8,9
    digitalWrite(row, HIGH);
    for (byte c = 0; c < 8; c++) {
      byte col = 10 + c; // 10,11,12,13, 14(A0),15(A1),16(A2),17(A3)
      digitalWrite(col, LOW);
      delay(200);
      digitalWrite(col, HIGH);
    }
    digitalWrite(row, LOW);
  }
}

