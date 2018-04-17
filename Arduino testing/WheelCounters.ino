#include <Servo.h>

#define pin_motorLeft 2
#define pin_motorRight 3
#define pin_sensorLeft1 34
#define pin_sensorLeft2 35
#define pin_sensorRight1 38
#define pin_sensorRight2 39
#define FULL_REVERSE 1000
#define MOTOR_BRAKE 1500
#define FULL_FORWARD 2000
#define FULL_ROTATION 144

Servo motorLeft;
Servo motorRight;

byte sensorLeft1;
byte sensorLeft2;
byte sensorRight1;
byte sensorRight2;

signed long counterLeft = 0;
signed long counterRight = 0;

signed long tempLeft;
signed long tempRight;
String printString;

void sensorLeft1Event(void);
void sensorLeft2Event(void);
void sensorRight1Event(void);
void sensorRight2Event(void);

void motorSetup() {
  Serial.println("motorSetup");
  //put motors in rest mode
  pinMode(pin_motorLeft, INPUT);
  pinMode(pin_motorRight, INPUT);
  while (digitalRead(pin_motorLeft) == 0 || digitalRead(pin_motorRight) == 0) {
    delayMicroseconds(100);
  }
  digitalWrite(pin_motorLeft, LOW);     //go low before switching to output mode
  digitalWrite(pin_motorRight, LOW);
  pinMode(pin_motorLeft, OUTPUT);
  pinMode(pin_motorRight, OUTPUT);
  delay(5);                             //wait for initialization
  //motors are ready to be attached
  motorLeft.attach(pin_motorLeft, FULL_REVERSE, FULL_FORWARD);
  motorRight.attach(pin_motorRight, FULL_REVERSE, FULL_FORWARD);
}

void sensorSetup() {
  Serial.println("sensorSetup");
  attachInterrupt(digitalPinToInterrupt(pin_sensorLeft1), sensorLeft1Event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_sensorLeft2), sensorLeft2Event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_sensorRight1), sensorRight1Event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_sensorRight2), sensorRight2Event, CHANGE);
  //set flags to correspond to wheels
  sensorLeft1 = digitalRead(pin_sensorLeft1);
  sensorLeft2 = digitalRead(pin_sensorLeft2);
  sensorRight1 = digitalRead(pin_sensorRight1);
  sensorRight2 = digitalRead(pin_sensorRight2);
}

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  motorSetup();
  sensorSetup();
  Serial.println("setup done");
}

void loop() {
  tempLeft = counterLeft;
  tempRight = counterRight;
  printString = "Left counter: ";
  printString.concat(tempLeft);
  printString.concat("\nRight counter: ");
  printString.concat(tempRight);
  printString.concat("\nDifference: ");
  printString.concat(abs(tempLeft - tempRight));
  printString.concat("\n");
  Serial.println(printString);
  delay(500);
}

// Interrupt functions, used for input from Quadrature Encoders

void sensorLeft1Event() {
  sensorLeft1 = digitalRead(pin_sensorLeft1);
  if (sensorLeft1 == HIGH) {
    if (sensorLeft2 == LOW) counterLeft++;
    if (sensorLeft2 == HIGH) counterLeft--;
  }
  if (sensorLeft1 == LOW) {
    if (sensorLeft2 == HIGH) counterLeft++;
    if (sensorLeft2 == LOW) counterLeft--;
  }
}

void sensorLeft2Event() {
  sensorLeft2 = digitalRead(pin_sensorLeft2);
  if (sensorLeft2 == HIGH) {
    if (sensorLeft1 == HIGH) counterLeft++;
    if (sensorLeft1 == LOW) counterLeft--;
  }
  if (sensorLeft2 == LOW) {
    if (sensorLeft1 == LOW) counterLeft++;
    if (sensorLeft1 == HIGH) counterLeft--;
  }
}

void sensorRight1Event() {
  sensorRight1 = digitalRead(pin_sensorRight1);
  if (sensorRight1 == HIGH) {
    if (sensorRight2 == LOW) counterRight++;
    if (sensorRight2 == HIGH) counterRight--;
  }
  if (sensorRight1 == LOW) {
    if (sensorRight2 == HIGH) counterRight++;
    if (sensorRight2 == LOW) counterRight--;
  }
}

void sensorRight2Event() {
  sensorRight2 = digitalRead(pin_sensorRight2);
  if (sensorRight2 == HIGH) {
    if (sensorRight1 == HIGH) counterRight++;
    if (sensorRight1 == LOW) counterRight--;
  }
  if (sensorRight2 == LOW) {
    if (sensorRight1 == LOW) counterRight++;
    if (sensorRight1 == HIGH) counterRight--;
  }
}

