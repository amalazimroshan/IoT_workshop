int analogInput = 0; //analog input pin
int digitalInput = 6; // digital input pin
int output = 13; // pin to light an led
int sensorValueDigital;
float sensorValueAnalog;
void setup() {
  pinMode(analogInput,INPUT);
  pinMode(digitalInput,INPUT);
  pinMode(output,OUTPUT);
  Serial.begin(9600);
  // mq3 sensor require to heat up a little
  Serial.println("sensor warming up");
  delay(1000);
}


void loop() {
  sensorValueAnalog = analogRead(analogInput);
  sensorValueDigital = digitalRead(digitalInput);
  Serial.print("Sensor value: ");
  Serial.println(sensorValueAnalog);


  if(sensorValueDigital == 0){
    digitalWrite(output,HIGH);
  }
  else{
    digitalWrite(output,LOW);
  }
  delay(500);
}
