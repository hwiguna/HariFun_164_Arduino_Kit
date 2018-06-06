const byte col0 = 10;
const byte col1 = 11;
const byte col2 = 12;
const byte col3 = 13;
unsigned long timeToScroll = 0;
byte offset=0;
  
const byte segmentA = 2;
// --A--
// F   B
//  -G-
// E   C
// --D-- .

byte bitmap[] {
  //abcdefg.
  B01101110, // H
  B11111010, // a
  B11001100, // r
  B01100000, // i
  B00000000, //
  B10001110, // F
  B00111000, // u
  B00101010, // n
};

void setup() {
  for (byte i=segmentA; i<=col3; i++)
    pinMode(i, OUTPUT);
  for (byte col=0; col<4; col++) 
    digitalWrite(col0+col, LOW);
}

void loop() {
  if (millis()>=timeToScroll) {
    timeToScroll = millis() + 200;
    offset++;
    if (offset>11) offset=0;
  }

  for (byte col=0; col<8; col++)
    {
      int c = 3 - offset + col;
      if (c>=0 && c<4) {
      for (byte seg=0; seg<8; seg++) {
        digitalWrite(segmentA+seg,!bitRead(bitmap[col],7-seg));
      }
      digitalWrite(col0+c, HIGH);
      delayMicroseconds(100);
      digitalWrite(col0+c, LOW);
      }
    }
}
