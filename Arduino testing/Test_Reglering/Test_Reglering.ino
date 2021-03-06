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
#define FULL_ROTATION 144
#define HISTORY_SIZE 10
#define LOOP_DELAY 100

Servo motorLeft;
Servo motorRight;

byte sensorLeft1;
byte sensorLeft2;
byte sensorRight1;
byte sensorRight2;

signed long counterLeft = 0;
signed long counterRight = 0;

signed long lastLeft = 0;
signed long lastRight = 0;

signed long currentLeft = 0;
signed long currentRight = 0;

signed long historyLeft[HISTORY_SIZE] = {0};
signed long historyRight[HISTORY_SIZE] = {0};

String printString;

int uL = 1700;
int uR = 1690;
double error=0;              // felvärde
 int prevError=0;            // förgående felvärde
 int bv = 0;             // börvärde
 double P=0;                // P-regulator
 double I=0;                // I-regulator
 double D=0;                // D-regulator
 double kp=1;
 double Td=0;
 double Ti=0;
 double dT=0;
 int sum=0;               // summan av flera felvärden
 double u;                // nya styrvärdet

 int N =144;             // pulser per rotation
 int t =1;               // samplingstid
 double uV =0;              // hastighet för vänsterhjul
 double uH =0;              // hastighet för högerhjul
 double pi =3.14159265359;
 double omkrets=49;


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
  motorLeft.writeMicroseconds(uL);
  motorRight.writeMicroseconds(uR);
  sensorSetup();
  Serial.println("setup done");
}

void loop() {
  //move history upwards
  for (int index = HISTORY_SIZE; index > 0; index--) {
    historyLeft[index - 1] = historyLeft[index - 2];
    historyRight[index - 1] = historyRight[index - 2];
  }

  //wait for exact time interval
  while (millis()%LOOP_DELAY != 0);

  //new history
  historyRight[0] = currentRight;
  historyLeft[0] = currentLeft;
  
  currentRight = counterRight;
  currentLeft = counterLeft;
  uV = (((2*pi*(currentLeft - historyLeft[9]))/(N/t))/(2*pi))*omkrets;
  uH = (((2*pi*(currentRight - historyRight[9]))/(N/t))/(2*pi))*omkrets;

 // uV = (((2*pi*counterLeft)/(N/t))/(2*pi))*omkrets;
 // uH = (((2*pi*counterRight)/(N/t))/(2*pi))*omkrets;

 // uV = counterLeft;
 //uH = counterRight;
  
  

  printString = "Left speed: ";
  printString.concat(uV);
  printString.concat("\nRight speed: ");
  printString.concat(uH);
  printString.concat("\nDifference: ");
  printString.concat(abs(uV - uH));
  printString.concat("\n");
  Serial.println(printString);

  //PID reglering

    error = uV - uH;         
    sum = sum + error;
    P = kp*error;
   // I = (sum*(dT/Ti));
   // D = ((error-prevError)*(Td/dT));
    //prevError = error;

    u = P + I + D;
    
    if ( error > bv){
      uL = (uL - 1);
      uR = (uR + 1);
    }
    else if( error < bv){
      uL = (uL + 1);
      uR = (uR - 1);
    }
    
  Serial.println(u);

  motorLeft.writeMicroseconds(uL);
  motorRight.writeMicroseconds(uR);
  delay(1);
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
