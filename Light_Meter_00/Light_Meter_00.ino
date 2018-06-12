const byte col0 = 10;
const byte col1 = 11;
const byte col2 = 12;
const byte col3 = 13;
unsigned long timeToUpdate = 0;
int lastValue;
byte offset=0;
char message[] = "1234";
  
const byte segmentA = 2;
// --A--
// F   B
//  -G-
// E   C
// --D-- .

byte bitmap[] = {
  //abcdefg.
  B00000000, // (space)
  B01100001, // !
  B01000100, // "
  B10010010, // # (three horizontal lines)
  B10110110, // $ (capital S)
  B01001011, // % (slash with bottom right dot)
  B00001110, // & (right half of a plus)
  B00000100, // '
  B10011100, // ( (same as [)
  B11110000, // ) (same as ])
  B11000110, // * (small circle on top)
  B00001110, // + (right half of a plus sign)
  B00000001, // , (Comma is same as period)
  B00000010, // -
  B00000001, // .
  B01001010, // /
  B11111100, // 0
  B00001100, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B10010000, // :
  B10010000, // ; (same as :)
  0, // <
  0, // =
  0, // >
  0, // ?
  0, // @
  B11101110, // A
  B11111110, // B
  B10011100, // C
  B11111100, // D
  B10011110, // E
  B10001110, // F
  B10111110, // G
  B01101110, // H
  B01100000, // I
  B01111000, // J
  B01101110, // K
  B00011100, // L
  B11101110, // M
  B11101100, // N
  B11111100, // O
  B11001110, // P
  B11100110, // Q
  B11101110, // R
  B10110110, // S
  B11100000, // T
  B01111100, // U
  B01111100, // V
  B01111110, // W
  B01101110, // X
  B01110110, // Y
  B11011010, // Z
  B0, // [
  B0, // (backslash)
  B0, // ]
  B0, // ^
  B0, // _
  B0, // `
  B11111010, // a
  B00111110, // b
  B00011010, // c
  B01111010, // d
  B11011110, // e
  B10001110, // f
  B11110110, // g
  B01101110, // h
  B00001100, // i
  B01111000, // j
  B00101110, // k
  B00011100, // l
  B11101100, // m
  B00101010, // n
  B00111010, // o
  B11001110, // p
  B11100110, // q
  B11001100, // r
  B10110110, // s
  B00011110, // t
  B00111000, // u
  B01111100, // v
  B01111110, // w
  B01101110, // x
  B01110110, // y
  B11011010, // z
//  B11111010, // a
//  B11001100, // r
//  B01100000, // i
//  B00000000, //
//  B10001110, // F
//  B00111000, // u
//  B00101010, // n
};
byte messageLen = sizeof(message)/sizeof(char) - 1; // -1 to remove the terminating null character at the end of string.

void setup() {
  for (byte i=segmentA; i<=col3; i++)
    pinMode(i, OUTPUT);
  for (byte col=0; col<4; col++) 
    digitalWrite(col0+col, LOW);
}

void loop() {
  GetData();
  
  int messageStart = 0;
  for (byte c=0; c<4; c++)
  {
    int messageIndex = messageStart + c;
    if (messageIndex<messageLen) {
      byte theChar = bitmap[ message[messageIndex] - ' ' ];
      for (byte seg=0; seg<8; seg++) {
        digitalWrite(segmentA+seg,!bitRead(theChar,7-seg));
      }
      digitalWrite(col0+c, HIGH);
      delayMicroseconds(100);
      digitalWrite(col0+c, LOW);
    }
  }
}

void GetData()
{
  if (millis() > timeToUpdate) {
  int analogValue = analogRead(A7);
  if (abs(analogValue-lastValue)>5) {
  message[3] = '0' + (analogValue % 10);
  message[2] = '0' + (analogValue % 100) / 10;
  message[1] = '0' + (analogValue % 1000) / 100;
  message[0] = '0' + (analogValue / 1000);
  lastValue = analogValue;
  }
  timeToUpdate = millis() + 100;
  }
}

