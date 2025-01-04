// Pin configuration
const int leftMotorForward = 5;
const int leftMotorBackward = 6;
const int rightMotorForward = 9;
const int rightMotorBackward = 10;

const int sensorPin[5] = {A0, A1, A2, A3, A4}; // IR sensors connected to analog pins

// PID Constants
float Kp = 1.0;
float Ki = 0.0;
float Kd = 0.0;

// Variables
int sensorValue[5]; // Array to store IR sensor values
float error, lastError = 0, integral = 0, derivative = 0;
int motorSpeed = 255;  // Maximum motor speed
int threshold = 500;  // Threshold for line detection

void setup() {
  // Initialize motors
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  // Initialize sensor pins
  for (int i = 0; i < 5; i++) {
    pinMode(sensorPin[i], INPUT);
  }
}

void loop() {
  // Read IR sensors
  for (int i = 0; i < 5; i++) {
    sensorValue[i] = analogRead(sensorPin[i]);
  }

  // Calculate error based on the sensor readings
  error = calculateError();

  // PID calculations
  integral += error;
  derivative = error - lastError;
  float output = Kp * error + Ki * integral + Kd * derivative;

  // Apply PID output to motors
  moveRobot(output);

  // Update last error
  lastError = error;
}

float calculateError() {
  long total = 0;
  long weightedSum = 0;

  // Check sensor states and calculate weighted sum
  for (int i = 0; i < 5; i++) {
    if (sensorValue[i] > threshold) {  // Line detected
      total += 1;
      weightedSum += i * 1;
    }
  }

  // If no sensors detect the line
  if (total == 0) {
    return 0;  // No error
  }

  // Return the calculated error
  return (weightedSum / total) - 2; // Center the error around 0
}

void moveRobot(float pidOutput) {
  int leftSpeed = motorSpeed - pidOutput;
  int rightSpeed = motorSpeed + pidOutput;

  // Limit motor speeds to prevent overflow
  leftSpeed = constrain(leftSpeed, -motorSpeed, motorSpeed);
  rightSpeed = constrain(rightSpeed, -motorSpeed, motorSpeed);

  if (leftSpeed > 0) {
    analogWrite(leftMotorForward, leftSpeed);
    analogWrite(leftMotorBackward, 0);
  } else {
    analogWrite(leftMotorForward, 0);
    analogWrite(leftMotorBackward, -leftSpeed);
  }

  if (rightSpeed > 0) {
    analogWrite(rightMotorForward, rightSpeed);
    analogWrite(rightMotorBackward, 0);
  } else {
    analogWrite(rightMotorForward, 0);
    analogWrite(rightMotorBackward, -rightSpeed);
  }
}

