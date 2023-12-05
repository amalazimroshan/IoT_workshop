int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int   motor2pin2 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,   OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(9,   OUTPUT); 
  pinMode(10, OUTPUT);
  pinMode(11,INPUT);
  Serial.begin(9600);
  //(Optional)
}

void loop() {
   // put your main code here, to run repeatedly:
   int x = digitalRead(11);
   Serial.println(x);
  if(digitalRead(11) == 1){
    
    move();
  }else if(digitalRead(11)==0){
    
    
    rev();
    
  }
   
  
}

void move(){
   analogWrite(10, 80); 
    analogWrite(9, 80); 
digitalWrite(motor1pin1,   HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);



}

void rev(){
    analogWrite(10, 60); 
    analogWrite(9, 60); 
  digitalWrite(motor1pin1,   LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);


}

void Right_turn(){
    analogWrite(10, 100); 
    analogWrite(9, 100); 
digitalWrite(motor1pin1,   HIGH);
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, LOW);
digitalWrite(motor2pin2, HIGH);


}
void left_turn(){
    analogWrite(10, 70); 
    analogWrite(9, 70); 
   digitalWrite(motor2pin1, HIGH);
   digitalWrite(motor2pin2, LOW);
   digitalWrite(motor1pin1,   LOW);
  digitalWrite(motor1pin2, HIGH);

}



