
// Pin definitions
const int leftMotorForward = 5;
const int leftMotorBackward = 6;
const int rightMotorForward = 9;
const int rightMotorBackward = 10;
const int ENA=3;
const int ENB=11;

// IR sensor pins
const int sensorLeft = A0;
const int sensorLeftCenter = A1;
const int sensorCenter = A2;
const int sensorRightCenter = A3;
const int sensorRight = A4;

void setup() {
  // Set motor pins as outputs
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  
  // Set sensor pins as inputs
  pinMode(sensorLeft, INPUT);
  pinMode(sensorLeftCenter, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRightCenter, INPUT);
  pinMode(sensorRight, INPUT);
}

void loop() {
  // Read sensor values
  int leftValue = digitalRead(sensorLeft);
  int leftCenterValue = digitalRead(sensorLeftCenter);
  int centerValue = digitalRead(sensorCenter);
  int rightCenterValue = digitalRead(sensorRightCenter);
  int rightValue = digitalRead(sensorRight);

  // Control logic
  if (centerValue == LOW) {
    // Move forward
    moveForward();
  } else if (leftCenterValue == LOW) {
    // Turn left
    turnLeft();
  } else if (rightCenterValue == LOW) {
    // Turn right
    turnRight();
  } else if (leftValue == LOW) {
    // Slightly turn left
    slightTurnLeft();
  } else if (rightValue == LOW) {
    // Slightly turn right
    slightTurnRight();
  } else {
    // Stop if no line is detected
    stop();
  }
}

void moveForward() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void turnLeft() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void turnRight() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void slightTurnLeft() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void slightTurnRight() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void stop() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}
