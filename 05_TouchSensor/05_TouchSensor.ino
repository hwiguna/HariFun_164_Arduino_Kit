void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A5,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(A5));
delay(1000);
}
