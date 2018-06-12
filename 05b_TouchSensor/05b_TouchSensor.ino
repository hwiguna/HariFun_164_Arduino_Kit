int Led=13;// Define LED interface
int touch=3;//Define the touch module interface
int val;// Digital variables "val"
void setup()
{
pinMode(Led,OUTPUT);// Define the LED for the output interface
pinMode(touch,INPUT);/*Define the touch module for the input interface*/
}
void loop()
{
val=digitalRead(touch);/* Will the value of the digital interface 3 read assigned to val*/
if(val==HIGH)/* When the key switch sensor detection signal, LED light*/
{
digitalWrite(Led,HIGH);
}
else
{
digitalWrite(Led,LOW);
}
}

