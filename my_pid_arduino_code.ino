const int IN1=5;
const int IN2=6;
const int IN3=9;
const int IN4=10;
const int ENA=3;
const int ENB=11;


#define LEFT_SENSOR A0
#define MID_LEFT_SENSOR A1
#define MID_SENSOR A2
#define MID_RIGHT_SENSOR A3
#define RIGHT_SENSOR A4

int SENSOR_THRESHOLD=500;

float Kp = 1.0;
float Ki = 0.0;
float Kd = 0.0;

int sensorValue[5]; 
float error; 
float lastError = 0.0; 
float integral = 0;
float derivative = 0;

int motorSpeed = 255;  
int threshold = 500;

void setup() {
  // Initialize motors
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

//for (int i = 0; i < 5; i++) {
  //  pinMode(sensorPin[i], INPUT);
  //}


}


void loop()
{

int leftSensor = analogRead(LEFT_SENSOR);
  int midLeftSensor = analogRead(MID_LEFT_SENSOR);
  int midSensor = analogRead(MID_SENSOR);
  int midRightSensor = analogRead(MID_RIGHT_SENSOR);
  int rightSensor = analogRead(RIGHT_SENSOR);

  Serial.print("Left: "); Serial.print(leftSensor);
  Serial.print(" MidLeft: "); Serial.print(midLeftSensor);
  Serial.print(" Mid: "); Serial.print(midSensor);
  Serial.print(" MidRight: "); Serial.print(midRightSensor);
  Serial.print(" Right: "); Serial.println(rightSensor);

  if(leftSensor < SENSOR_THRESHOLD && midLeftSensor < SENSOR_THRESHOLD )
  {
    error=-3;
  }

/*
if(leftSensor < SENSOR_THRESHOLD || midLeftSensor < SENSOR_THRESHOLD )
  {
    error=(leftSensor+midLeftSensor)/2
    error=-3;
  }
    if(rightSensor > SENSOR_THRESHOLD || midRightSensor > SENSOR_THRESHOLD )
  {
    error=3;
  }
*/

 if(rightSensor > SENSOR_THRESHOLD && midRightSensor > SENSOR_THRESHOLD )
  {
    error=3;
  }


if (midSensor==0)
{
  error=0;
}


 integral += error;
  int derivative = error - lastError;
  int output = Kp * error + Ki * integral + Kd * derivative;

  if (output > 0) {
   //right
    analogWrite(IN1, 210);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
  } 
  else if (output < 0) 
  {
    //left
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 210);
    analogWrite(IN4, 0);
  } 
  else 
  {
   //straight
    analogWrite(IN1,210);
    analogWrite(IN2, 0);
    analogWrite(IN3, 210);
    analogWrite(IN4, 0);
  }

 
  lastError = error;

  delay(100); 
}


