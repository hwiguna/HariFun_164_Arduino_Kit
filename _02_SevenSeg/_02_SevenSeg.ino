//=== 7-Segment ===
//  -A- 
// F   B
//  -G- 
// E   C
//  -D-  . 
int one7SegCathode = 13; // D13
byte one7SegAnodes[] = {4,5,8,6,7,3,2,9};
//                      G F A B D E C .
volatile byte digitBits[] = {
  B00000000, // 0 -> (space)
  B00001100, // 1 ----EF--
  B11011010, // 2 ABxDE-G-
  B11110010, // 3 ABCD--G-
  B01100110, // 4 -BC--FG-
  B10110110, // 5 A-CD-FG-
  B10111110, // 6 A-CDEFG-
  B11100000, // 7 ABC-----
  B11111110, // 8 ABCDEFG-
  B11110110, // 9 ABCD_FG-
};

void SetupOne7Seg()
{
  pinMode(one7SegCathode,OUTPUT);
  digitalWrite(one7SegCathode,HIGH); // HIGH = Off
  
  for (byte i=0; i<8; i++) {
    pinMode(one7SegAnodes[i],OUTPUT);
    digitalWrite(one7SegAnodes[i],LOW);
  }
}

void TestOne7Seg()
{
  // turn off all segments before turning on the digit
  for (byte i=0; i<8; i++) digitalWrite(one7SegAnodes[i],LOW);
    
  digitalWrite(one7SegCathode,LOW); // Turn on the digit

  // Cycle through the segments
  for (byte i=0; i<8; i++) {
    digitalWrite(one7SegAnodes[i],HIGH);
    delay(250);
    digitalWrite(one7SegAnodes[i],LOW);
  }
  
  digitalWrite(one7SegCathode,HIGH); // Turn off the digit
}

void DisplayNumber(byte digit) {
  for (byte seg=0; seg<8; seg++)
  {
    digitalWrite(one7SegAnodes[seg], bitRead(digitBits[digit], 7-seg) );
  }
}

void CountDown(byte highDigit)
{
  for (int digit=highDigit; digit>=0; digit--) {
    DisplayNumber(digit);
    digitalWrite(one7SegCathode,LOW); // Turn on the digit
    delay(500);
    digitalWrite(one7SegCathode,HIGH); // Turn off the digit
  }
}

void setup() {
  SetupOne7Seg();
  TestOne7Seg();
}

void loop() {
  CountDown(9);
}
