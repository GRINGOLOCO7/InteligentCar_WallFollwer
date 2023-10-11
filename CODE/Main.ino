//Distance sensors
const int trigg_front = 11; 
const int echo_front = 13; 
const int trigg_dx = 10; 
const int echo_dx = 12;

// Motors
const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 8;
const int rightBackward = 9;
const int enableLeft = 6;
const int enableRight = 5;

// Variables
int speedMotorsLeft= 0;
int speedMotorsRight= 0;
int MAX_SPEED = 255;      //---> WTF?! btw 0-255
float distance_front;
float distance_dx;
int toCloseFront = 25; //--> set to 10  OR intervall?
int toCloseWall = 25; //--> set to 10  OR intervall?
int toFarWall = 33; //--> set to 10  OR intervall?


void setup() 
{
  Serial.begin(9600);
  pinMode(trigg_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trigg_dx, OUTPUT);
  pinMode(echo_dx, INPUT);
  
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);

}

void loop()
{
Main:
  float distance_front = DISTANCE_f(echo_front, trigg_front);
  float distance_dx = DISTANCE_r(echo_dx, trigg_dx);
  //Serial.print(distance_front);
  //Serial.println(distance_dx);
  //delay(2000);
  if (distance_front == 1 && distance_dx == 1){
    Serial.println("1-1");
    LEFT_STRONG();
  }
  else if (distance_front == 1 && distance_dx == 3){
    Serial.println("1-3");
    LEFT_STRONG();
  }
  else if (distance_front == 1 && distance_dx == 2){
      Serial.println("1-2");
    LEFT_STRONG();
  }
  else if (distance_front == 0 && distance_dx == 1){
    Serial.println("0-1");
    LEFT_LIGHT();
  }
  else if (distance_front == 0 && distance_dx == 3){
    Serial.println("0-3");
    FOWARD();
  }
  else if (distance_front == 0 && distance_dx == 2){
    Serial.println("0-2");
    RIGHT_LIGHT();
  }
  else{
    FOWARD();
  }
}



//FUNCTIONS:
float DISTANCE_f(int echo, int trigg)
{
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
  float distance = 0.034 * pulseIn(echo, HIGH) / 2;
  int output;
  if (distance <= toCloseFront){
    output = 1; // "On" 
  } 
  else{
    output = 0; // "Off" 
  } 
  return output;
}


float DISTANCE_r(int echo, int trigg)
{
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
  float distance = 0.034 * pulseIn(echo, HIGH) / 2;
  int output;
  if (distance < toCloseWall){
    output = 1; // toClose
  } 
  else if (distance > toFarWall){
    output = 2;
  }
  else{
    output = 3; // "Good" 
  } 
  return output;
}


void BACKWARD()
{
  speedMotorsLeft = MAX_SPEED;
  speedMotorsRight = MAX_SPEED;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , HIGH);
  digitalWrite(rightForward , LOW);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
}


void BACKWARD_RIGHT()
{
  speedMotorsLeft = MAX_SPEED;
  speedMotorsRight = MAX_SPEED * 0.7;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , HIGH);
  digitalWrite(rightForward , LOW);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
}


void FOWARD()
{
  speedMotorsLeft = MAX_SPEED * 0.87;
  speedMotorsRight = MAX_SPEED;
  
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , LOW);
  digitalWrite(rightForward , HIGH);
}


void LEFT_STRONG()
{
  speedMotorsLeft = 0;
  speedMotorsRight = MAX_SPEED * 0.8;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , LOW);
  digitalWrite(rightForward , HIGH);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
}


void RIGHT_STRONG()
{
  speedMotorsLeft = MAX_SPEED * 0.8;
  speedMotorsRight = 0;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , LOW);
  digitalWrite(rightForward , LOW);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
}


void LEFT_LIGHT()
{
  speedMotorsLeft = MAX_SPEED * 0.6;
  speedMotorsRight = MAX_SPEED * 0.9;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , LOW);
  digitalWrite(rightForward , HIGH);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
}


void RIGHT_LIGHT()
{
  speedMotorsLeft = MAX_SPEED;
  speedMotorsRight = MAX_SPEED * 0.7;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , LOW);
  digitalWrite(rightForward , HIGH);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
}

// not used
void STOP()
{
  speedMotorsLeft = 0;
  speedMotorsRight = 0;
  
  analogWrite(enableRight , speedMotorsRight);
  digitalWrite(rightBackward , HIGH);
  digitalWrite(rightForward , LOW);
  analogWrite(enableLeft , speedMotorsLeft);
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
}