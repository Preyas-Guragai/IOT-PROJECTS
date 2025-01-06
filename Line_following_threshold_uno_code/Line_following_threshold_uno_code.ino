#define LEFT_MOTOR_FORWARD 5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define RIGHT_MOTOR_BACKWARD 10

int sensorPins[5] = {A0, A1, A2, A3, A4};  // IR sensors connected to analog pins
int sensorValues[5];                       // Array to store sensor readings
int threshold = 500;                       // Threshold value for detecting the line

void setup() {
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  Serial.begin(9600);  // For debugging
}

void loop() {
  // Read sensor values
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);
  }

  // Debugging: print sensor values to serial monitor
  for (int i = 0; i < 5; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();

  // Determine robot behavior based on sensor readings
  if (sensorValues[2] > threshold) { // Middle sensor detects the line
    moveForward();
  } else if (sensorValues[0] > threshold || sensorValues[1] > threshold) { // Line is to the left
    turnLeft();
  } else if (sensorValues[3] > threshold || sensorValues[4] > threshold) { // Line is to the right
    turnRight();
  } else { // No line detected
    stopMotors();
  }
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}
