int DI = 12;
int RW = 11;
int DB[] = {3, 4, 5, 6, 7, 8, 9, 10};//Use an array to define the pins needed by the bus
int Enable = 2;

void LcdCommandWrite(int value) {
// Define all pins
int i = 0;
for (i=DB[0]; i <= DI; i++) //Bus assignment
{
   digitalWrite(i,value & 01);//Because the 1602 liquid crystal signal recognition is D7-D0 (not D0-D7), here is used to reverse the signal.
   value >>= 1;
}
digitalWrite(Enable,LOW);
delayMicroseconds(1);
digitalWrite(Enable,HIGH);
delayMicroseconds(1);  //delay 1ms
digitalWrite(Enable,LOW);
delayMicroseconds(1);  // delay 1ms
}

void LcdDataWrite(int value) {
// Define all pins
int i = 0;
digitalWrite(DI, HIGH);
digitalWrite(RW, LOW);
for (i=DB[0]; i <= DB[7]; i++) {
   digitalWrite(i,value & 01);
   value >>= 1;
}
digitalWrite(Enable,LOW);
delayMicroseconds(1);
digitalWrite(Enable,HIGH);
delayMicroseconds(1);
digitalWrite(Enable,LOW);
delayMicroseconds(1);  //Delay 1ms
}

void setup (void) {
int i = 0;
for (i=Enable; i <= DI; i++) {
   pinMode(i,OUTPUT);
}
delay(100);
// After a short pause, LCD
// For LCD control needs
LcdCommandWrite(0x38);  // Set to 8-bit interface, 2 line display, 5x7 text size                
delay(64);                      
LcdCommandWrite(0x38);  // Set to 8-bit interface, 2 line display, 5x7 text size                      
delay(50);                      
LcdCommandWrite(0x38);  //Set to 8-bit interface, 2 line display, 5x7 text size                       
delay(20);                      
LcdCommandWrite(0x06);  // Input mode setting
                         // Auto increment, no display shift
delay(20);                      
LcdCommandWrite(0x0E);  // Display settings
                         // Turn on the display, the cursor shows, no flicker
delay(20);                      
LcdCommandWrite(0x01);  // The screen is empty, the cursor position is zero  
delay(100);                      
LcdCommandWrite(0x80);  // Display settings
                         // Turn on the display, the cursor shows, no flicker
delay(20);                      
}

void loop (void) {
  LcdCommandWrite(0x01);  // The screen is empty, the cursor position is zero
  delay(10); 
  LcdCommandWrite(0x80+3); 
  delay(10);                     

  LcdDataWrite('W');
  LcdDataWrite('e');
  LcdDataWrite('l');
  LcdDataWrite('c');
  LcdDataWrite('o');
  LcdDataWrite('m');
  LcdDataWrite('e');
  LcdDataWrite(' ');
  LcdDataWrite('t');
  LcdDataWrite('o');
  delay(10);
  LcdCommandWrite(0xc0+1);  // Defines the cursor position as second rows and second positions
  delay(10); 
  LcdDataWrite('g');
  LcdDataWrite('e');
  LcdDataWrite('e');
  LcdDataWrite('k');
  LcdDataWrite('-');
  LcdDataWrite('w');
  LcdDataWrite('o');
  LcdDataWrite('r');
  LcdDataWrite('k');
  LcdDataWrite('s');
  LcdDataWrite('h');
  LcdDataWrite('o');
  LcdDataWrite('p');
  delay(5000);
  LcdCommandWrite(0x01);  // The screen is empty, the cursor position is zero  
  delay(10);
  LcdDataWrite('I');
  LcdDataWrite(' ');
  LcdDataWrite('a');
  LcdDataWrite('m');
  LcdDataWrite(' ');
  LcdDataWrite('h');
  LcdDataWrite('o');
  LcdDataWrite('n');
  LcdDataWrite('g');
  LcdDataWrite('y');
  LcdDataWrite('i');
  delay(3000);
  LcdCommandWrite(0x02); //Set the pattern for the new text to replace the old text, no new text display the same place
  delay(10);
  LcdCommandWrite(0x80+5); //Defines the cursor position as the first line of the sixth position
  delay(10);  
  LcdDataWrite('t');
  LcdDataWrite('h');
  LcdDataWrite('e');
  LcdDataWrite(' ');
  LcdDataWrite('a');
  LcdDataWrite('d');
  LcdDataWrite('m');
  LcdDataWrite('i');
  LcdDataWrite('n');
  delay(5000);
}

