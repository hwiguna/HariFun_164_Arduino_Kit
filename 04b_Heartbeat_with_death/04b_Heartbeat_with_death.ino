//=== MATRIX ===
// Rows are anodes(positive), Columns are cathodes(negative)
byte row0Pin = 2;  // D2(row0),D3,D4,D5, D6,D7,D8,D9(row7) controls the Rows

// Shift register controls the Columns (QA=col0, QH=col7)
int latchPin = A1;  //Pin connected to RCLK/ST_CP of 74HC595
int clockPin = A0;  //Pin connected to SRCLK/SH_CP of 74HC595
int dataPin = A2;   //Pin connected to SER/DS of 74HC595
 
byte bitmap[8];

byte heartbeatBitmap[] = {
  B00000000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B11101111,
  B00000000,
  B00000000,
};


byte flatlineBitmap[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B00000000,
  B00000000,
};


// Heartbeat
byte head = 0;
unsigned long timeToMove;
int heartSpeed = 120;
byte buzzerPin = 13;

int timeToDie = 3;
byte resuscitatePin = A3;
  
void SetupMatrix()
{
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

  // Setup Buzzer
  pinMode(buzzerPin, OUTPUT);
}

void setup() {
  SetupMatrix();
}

bool TimeToMove()
{
  return millis() > timeToMove;
}

bool IsDead()
{
  return timeToDie<=0;
}

void AnimateHeartbeat()
{
  ClearBitmap();
  
  // Copy "head" column
  for (byte r = 0; r < 8; r++)
  {
    if (bitRead(heartbeatBitmap[r], 7-head))
      bitSet(bitmap[r], head);
    else
      bitClear(bitmap[r], head);
  }

  if (head==3) digitalWrite(buzzerPin,LOW);
  if (head==4) digitalWrite(buzzerPin,HIGH);
  
  head++;
  if (head>7) {
    head = 0;
    timeToDie--;
  }
}


void AnimateFlatline()
{
  digitalWrite(buzzerPin,LOW); // Turn buzzer on continuously
  ClearBitmap();
  
  // Copy "head" column
  for (byte r = 0; r < 8; r++)
  {
    if (bitRead(flatlineBitmap[r], 7-head))
      bitSet(bitmap[r], head);
    else
      bitClear(bitmap[r], head);
  }
    
  head++;
  if (head>7) {
    head = 0;
  }

  if (analogRead(resuscitatePin)>1000) {
      digitalWrite(buzzerPin,HIGH); // Turn buzzer off
      timeToDie=5; // Bring back to live at age 5
    }
}

void Animate()
{
  if (TimeToMove()) {
    if (IsDead())
      AnimateFlatline();
    else
      AnimateHeartbeat();
    timeToMove = millis() + heartSpeed;
  }
  Refresh();
}
void loop() {
  Animate();
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
    delayMicroseconds(500); // Let humans see it
    digitalWrite(row, LOW); // Turn row off in preparation for next row
  }
}

