byte bitmap[8];

void setup() {
  // put your setup code here, to run once:
  for (byte p = 2; p < (2 + 16); p++)
  {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
  }
}

void loop() {
  ClearBitmap();
  DrawX();
  for (int d=0; d<1000; d++) Refresh();
  
  ClearBitmap();
  DrawBox();
  for (int d=0; d<1000; d++) Refresh();
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
    
    int row = 2+r; // 2,3,4,5, 6,7,8,9
    
    for (byte c = 0; c < 8; c++) {
        byte col = 10+c; // 10,11,12,13, 14(A0),15(A1),16(A2),17(A3)
        digitalWrite(col, !bitRead(bitmap[r],c));
        //delayMicroseconds(10);
    }
    digitalWrite(row, HIGH);
    delayMicroseconds(100);
    //for (byte c = 0; c < 8; c++) digitalWrite(10+c, HIGH);
    digitalWrite(row, LOW);
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

