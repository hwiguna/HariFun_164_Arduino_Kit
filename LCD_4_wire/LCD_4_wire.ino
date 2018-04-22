int LCD1602_RS=12;   

int LCD1602_RW=10;   

int LCD1602_EN=11;   

//int DB[] = { 6, 7, 8, 9};
int DB[] = { 9,8,7,6};

char str1[]="Welcome to";

char str2[]="geek-workshop";

char str3[]="this is the";

char str4[]="4-bit interface";



void LCD_Command_Write(int command)

{

int i,temp;

digitalWrite( LCD1602_RS,LOW);

digitalWrite( LCD1602_RW,LOW);

digitalWrite( LCD1602_EN,LOW);



temp=command & 0xf0;

for (i=DB[0]; i <= 9; i++)

{

   digitalWrite(i,temp & 0x80);

   temp <<= 1;

}



digitalWrite( LCD1602_EN,HIGH);

delayMicroseconds(1);

digitalWrite( LCD1602_EN,LOW);



temp=(command & 0x0f)<<4;

for (i=DB[0]; i <= 10; i++)

{

   digitalWrite(i,temp & 0x80);

   temp <<= 1;

}



digitalWrite( LCD1602_EN,HIGH);

delayMicroseconds(1); 

digitalWrite( LCD1602_EN,LOW);

}



void LCD_Data_Write(int dat)

{

int i=0,temp;

digitalWrite( LCD1602_RS,HIGH);

digitalWrite( LCD1602_RW,LOW);

digitalWrite( LCD1602_EN,LOW);



temp=dat & 0xf0;

for (i=DB[0]; i <= 9; i++)

{

   digitalWrite(i,temp & 0x80);

   temp <<= 1;

}



digitalWrite( LCD1602_EN,HIGH);

delayMicroseconds(1);

digitalWrite( LCD1602_EN,LOW);



temp=(dat & 0x0f)<<4;

for (i=DB[0]; i <= 10; i++)

{

   digitalWrite(i,temp & 0x80);

   temp <<= 1;

}



digitalWrite( LCD1602_EN,HIGH);

delayMicroseconds(1); 

digitalWrite( LCD1602_EN,LOW);

}



void LCD_SET_XY( int x, int y )

{

  int address;

  if (y ==0)    address = 0x80 + x;

  else          address = 0xC0 + x;

  LCD_Command_Write(address); 

}



void LCD_Write_Char( int x,int y,int dat)

{

  LCD_SET_XY( x, y ); 

  LCD_Data_Write(dat);

}



void LCD_Write_String(int X,int Y,char *s)

{

LCD_SET_XY( X, Y );    //Set address

    while (*s)             //Write string

    {

      LCD_Data_Write(*s);   

      s ++;

    }

}



void setup (void) 

{

  int i = 0;

  for (i=6; i <= 12; i++) 

   {

     pinMode(i,OUTPUT);

   }

  delay(100);

  LCD_Command_Write(0x28);//4 lines and 2 lines 5x7

  delay(50); 

  LCD_Command_Write(0x06);

  delay(50); 

  LCD_Command_Write(0x0c);

  delay(50); 

  LCD_Command_Write(0x80);

  delay(50); 

  LCD_Command_Write(0x01);

  delay(50); 



}



void loop (void)

{

   LCD_Command_Write(0x01);

   delay(50);

   LCD_Write_String(3,0,str1);//First lines, fourth addresses

   delay(50);

   LCD_Write_String(1,1,str2);//Second lines, second addresses

   delay(5000);

   LCD_Command_Write(0x01);

   delay(50);

   LCD_Write_String(0,0,str3);

   delay(50);

   LCD_Write_String(0,1,str4);

   delay(5000);

   

}


