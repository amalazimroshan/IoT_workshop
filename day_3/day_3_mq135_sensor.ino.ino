int analogInput = 0; //analog input pin
int digitalInput = 6; //digital input pin
int output = 13; // pin to light an led
float sensorValueAnalog;
int sensorValueDigital;
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
}


void loop() {
  sensorValueAnalog = analogRead(analogInput);
  sensorValueDigital = digitalRead(digitalInput);
  if(sensorValueDigital == 0){
    digitalWrite(output,HIGH);
  }
  else{
    digitalWrite(output,LOW);
  }
}


