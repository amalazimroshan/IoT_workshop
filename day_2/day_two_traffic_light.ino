// C++ code
//
int green_one = 13;
int yellow_one = 12;
int red_one = 11;

int green_two = 7;
int yellow_two = 6;
int red_two = 5;

void setup()
{
  pinMode(green_one, OUTPUT);
  pinMode(yellow_one, OUTPUT);
  pinMode(red_one, OUTPUT);
  
  pinMode(green_two, OUTPUT);
  pinMode(yellow_two, OUTPUT);
  pinMode(red_two, OUTPUT);
}

void loop(){
  digitalWrite(red_one,HIGH);
  digitalWrite(green_two,HIGH);
  delay(4000);
  
  ///////////////////////////////

  digitalWrite(green_two,LOW);
  digitalWrite(yellow_two,HIGH);
  delay(1000);
  digitalWrite(yellow_two,LOW);
  digitalWrite(red_two,HIGH);
  
  digitalWrite(red_one,LOW);
  digitalWrite(green_one,HIGH);
  delay(4000);
  
  digitalWrite(green_one,LOW);
  digitalWrite(yellow_one,HIGH);
  
  delay(1000);
  digitalWrite(yellow_one,LOW);
  digitalWrite(red_two,LOW);
  
  
}