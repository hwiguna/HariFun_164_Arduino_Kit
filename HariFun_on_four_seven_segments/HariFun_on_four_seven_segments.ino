const byte col0 = 10;
const byte col1 = 11;
const byte col2 = 12;
const byte col3 = 13;

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
};

void setup() {
  for (byte i=segmentA; i<=col3; i++)
    pinMode(i, OUTPUT);
  for (byte col=0; col<4; col++) 
    digitalWrite(col0+col, LOW);
}

void loop() {
  for (byte col=0; col<4; col++)
  {
    
    for (byte seg=0; seg<8; seg++) {
      digitalWrite(segmentA+seg,!bitRead(bitmap[col],7-seg));
    }
    digitalWrite(col0+col, HIGH);
    delayMicroseconds(100);
    digitalWrite(col0+col, LOW);
  }
}
