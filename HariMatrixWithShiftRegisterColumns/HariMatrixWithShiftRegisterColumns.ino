//=== MATRIX ===
// Rows are anodes(positive), Columns are cathodes(negative)
byte row0Pin = 2;  // D2(row0),D3,D4,D5, D6,D7,D8,D9(row7) controls the Rows

// Shift register controls the Columns (QA=col0, QH=col7)
int latchPin = A1;  //Pin connected to RCLK/ST_CP of 74HC595
int clockPin = A0;  //Pin connected to SRCLK/SH_CP of 74HC595
int dataPin = A2;   //Pin connected to SER/DS of 74HC595
 
byte bitmap[8];

void setup() {
  // Setup Matrix Row (Shift Register)
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Setup Matrix Column (GPIO)
  for (byte i = 0; i < 8; i++)
  {
    pinMode(row0Pin+i, OUTPUT);
    digitalWrite(row0Pin+i, LOW);
  }
}

void loop() {
  //LCDPrint("Hello");
  ClearBitmap();
  ScanTestWithShiftRegister();
  
  ClearBitmap();
  DrawX();
  for (int d=0; d<100; d++) Refresh();
  
  ClearBitmap();
  DrawBox();
  for (int d=0; d<100; d++) Refresh();
}

void DrawX()
{
  for (byte i = 0; i < 8; i++)
  {
    bitSet(bitmap[i],i);
    bitSet(bitmap[i],7-i);
  }
}

void DrawBox()
{
  bitmap[0]=255;
  bitmap[7]=255;
  for (byte i = 0; i < 8; i++)
  {
    bitSet(bitmap[i],0);
    bitSet(bitmap[i],7);
  }
}

void ClearBitmap()
{
  for (byte i = 0; i < 8; i++)
  {
    bitmap[i]=0;
  }
}

void Refresh()
{
  for (byte r = 0; r < 8; r++)
  {
    int row = row0Pin+r; // 2,3,4,5, 6,7,8,9
    
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
    int row = 2+r; // 2,3,4,5, 6,7,8,9
    digitalWrite(row, HIGH);
    for (byte c = 0; c < 8; c++) {
      byte col = 10+c; // 10,11,12,13, 14(A0),15(A1),16(A2),17(A3)
      digitalWrite(col, LOW);
      delay(200);
      digitalWrite(col, HIGH);
    }
    digitalWrite(row, LOW);
  }
}

void ScanTestWithShiftRegister()
{
  for (byte r = 0; r < 8; r++)
  {
    for (byte c = 0; c < 8; c++) {
      bitSet(bitmap[r],c);
      for (int i=0;i<5;i++) Refresh();
      bitClear(bitmap[r],c);
    }
  }
}

