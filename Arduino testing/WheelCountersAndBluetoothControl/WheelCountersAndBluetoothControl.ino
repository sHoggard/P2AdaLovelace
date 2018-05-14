#include <Servo.h>

#define pin_motorLeft 9
#define pin_motorRight 8
#define pin_sensorLeft1 34
#define pin_sensorLeft2 35
#define pin_sensorRight1 38
#define pin_sensorRight2 39
#define FULL_REVERSE 1000
#define MOTOR_BRAKE 1500
#define FULL_FORWARD 2000
#define MOTOR_INCREMENTS 50   //must not be more than 100
#define FULL_ROTATION 731
#define ROTATION_PRECISION 2
#define LOOP_DELAY 100
#define PRINT_DELAY 5

Servo motorLeft;
Servo motorRight;

byte sensorLeft1;
byte sensorLeft2;
byte sensorRight1;
byte sensorRight2;

signed long counterLeft = 0;
signed long counterRight = 0;

signed long aimLeft = 0;
signed long aimRight = 0;

int bumps = 0;
char command = 's';
char mode = 's';
signed long aim = 0;
int orientation;            //strictly calculated
int orientationToAim = 0;

signed long tempLeft;
signed long tempRight;
String printString;

char clrCom[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

void sensorLeft1Event(void);
void sensorLeft2Event(void);
void sensorRight1Event(void);
void sensorRight2Event(void);

void motorSetup() {
  Serial.println("motorSetup");
  //wait for motors to be powered up
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
  //put motors in rest mode and wait
  motorLeft.writeMicroseconds(MOTOR_BRAKE);
  motorRight.writeMicroseconds(MOTOR_BRAKE);
  delay(20);
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
  //clear the counters
  counterLeft = 0;
  counterRight = 0;
}

void printStatus() {
  tempLeft = counterLeft;
  tempRight = counterRight;
  printString = "Command: ";
  printString.concat(command);
  printString.concat("\nMode: ");
  printString.concat(mode);
  printString.concat("\nLeft counter: ");
  printString.concat(tempLeft);
  printString.concat("\nRight counter: ");
  printString.concat(tempRight);
  printString.concat("\nDifference: ");
  printString.concat(abs(tempLeft - tempRight));
  printString.concat("\nOrientation: ");
  printString.concat(orientation);
  printString.concat("\nOrientationToAim: ");
  printString.concat(orientationToAim);
  printString.concat("\nAim: ");
  printString.concat(aim);
  Serial.write(clrCom);
  Serial.println(printString);
}

void readInput() {
  //if no "aim" is provided, 0 is default, meaning e.g. no speed
  while (Serial.available()) {
    command = Serial.read();
    switch (command) {
      case 'f':
      case 'b':
      case 'l':
      case 'r':
        mode = command;
        aim = Serial.parseInt();
        if (aim > 5) {
          aim = 5;
        }
        break;
      case 'd':
        mode = command;
        aim = Serial.parseInt();
        if (aim > 1000) {
          aim = 1000;
        }
        //multiply aim with ticks/mm
        aimLeft = counterLeft + aim;
        aimRight = counterRight + aim;
        break;
      case 'o':
        mode = command;
        aim = Serial.parseInt()%FULL_ROTATION;
        if (aim < 0) {
          aim += FULL_ROTATION;
        }
        break;
      case 's':
        mode = command;
        aim = 0;
        break;
      case 'c':
        counterLeft = 0;
        counterRight = 0;
        break;
    }
  }
}

void calculateOrientation() {
  //may need to be changed to only use positive orientations
  orientation = (int)((counterLeft - counterRight)%FULL_ROTATION);
  if (orientation < 0) {
    orientation += FULL_ROTATION;
  }

  orientationToAim = aim - orientation;
  if (orientationToAim < (-FULL_ROTATION/2)) {
    orientationToAim += FULL_ROTATION;
  }
  if (orientationToAim > FULL_ROTATION/2) {
    orientationToAim -= FULL_ROTATION;
  }
}

void regulate() {
  switch (mode) {
    case 'f':
      motorLeft.writeMicroseconds(MOTOR_BRAKE + aim*MOTOR_INCREMENTS);
      motorRight.writeMicroseconds(MOTOR_BRAKE + aim*MOTOR_INCREMENTS);
      break;
    case 'b':
      motorLeft.writeMicroseconds(MOTOR_BRAKE - aim*MOTOR_INCREMENTS);
      motorRight.writeMicroseconds(MOTOR_BRAKE - aim*MOTOR_INCREMENTS);
      break;
    case 'l':
      motorLeft.writeMicroseconds(MOTOR_BRAKE - aim*MOTOR_INCREMENTS);
      motorRight.writeMicroseconds(MOTOR_BRAKE + aim*MOTOR_INCREMENTS);
      break;
    case 'r':
      motorLeft.writeMicroseconds(MOTOR_BRAKE + aim*MOTOR_INCREMENTS);
      motorRight.writeMicroseconds(MOTOR_BRAKE - aim*MOTOR_INCREMENTS);
      break;
    case 'd':
      tempLeft = ((aimLeft - counterLeft)/100) + 1;
      if (tempLeft > 5) {
        tempLeft = 5;
      }
      if (abs(aimLeft - counterLeft) < ROTATION_PRECISION) {
        tempLeft = 0;
      }
      tempRight = ((aimRight - counterRight)/100) + 1;
      if (tempRight > 5) {
        tempRight = 5;
      }
      if (abs(aimRight - counterRight) < ROTATION_PRECISION) {
        tempRight = 0;
      }
      motorLeft.writeMicroseconds(MOTOR_BRAKE + tempLeft*MOTOR_INCREMENTS);
      motorRight.writeMicroseconds(MOTOR_BRAKE + tempRight*MOTOR_INCREMENTS);
      break;
    case 'o':
      if (aim == orientation) {         //(abs(aim - orientation) < ROTATION_PRECISION)
        mode = 's';
        break;
      }
      aimLeft = orientationToAim/100;
      if (orientationToAim > 0) {
        aimLeft++;
      }
      if (orientationToAim < 0) {
        aimLeft--;
      }
      motorLeft.writeMicroseconds(MOTOR_BRAKE + aimLeft*MOTOR_INCREMENTS);
      motorRight.writeMicroseconds(MOTOR_BRAKE - aimLeft*MOTOR_INCREMENTS);
      break;
    case 's':
      motorLeft.writeMicroseconds(MOTOR_BRAKE);
      motorRight.writeMicroseconds(MOTOR_BRAKE);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  //Serial1.println("U,9600,N");
  //Serial1.begin(9600);
  //Serial = Serial1;
  Serial.println("setup");
  motorSetup();
  sensorSetup();
  Serial.println("setup done");
}

void loop() {
  //instead of delay(LOOP_DELAY), wait until exact time step
  while (millis()%LOOP_DELAY != 0);
  readInput();
  calculateOrientation();
  regulate();
  if (bumps%PRINT_DELAY == 0) {
    printStatus();
  }
  bumps++;
  delay(1);
  //bumps %= 10;
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

