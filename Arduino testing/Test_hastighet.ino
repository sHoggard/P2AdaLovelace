int counterL1 = 0;
int counterL2 = 0;
int counterR1 = 0;
int counterR2 = 0;
int command = 1700;

long startTime, endTime;

void incrementLeft1(void);
void incrementLeft2(void);
void incrementRight1(void);
void incrementRight2(void);

void setup() {
  Serial.begin(9600);
  Serial.println("setup");

  //put motors in rest mode
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  while (digitalRead(2) == 0 || digitalRead(3) == 0) {
    delayMicroseconds(50);
  }
  digitalWrite(2, LOW);                 //go low before switching to output mode
  digitalWrite(3, LOW);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  delay(5);                             //wait for initialization
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delayMicroseconds(1500);              //stop motor
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(20);                            //wait
  Serial.println("setup done");

  //attach interrupts
  attachInterrupt(digitalPinToInterrupt(34), incrementLeft1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(35), incrementLeft2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(38), incrementRight1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(39), incrementRight2, CHANGE);
  
  delay(1000);
  startTime = millis();
  endTime = startTime + 30000;
  
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delayMicroseconds(command);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Left: ");
  Serial.println(counterL1);
  Serial.println(counterL2);
  Serial.println("Right: ");
  Serial.println(counterR1);
  Serial.println(counterR2);
  Serial.println();

  if (millis() > endTime) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    delayMicroseconds(1500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  } else {                      //necessary if Communications Timeout mode is enabled
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    delayMicroseconds(command);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }

  delay(20);                    //pause
}

void incrementLeft1() {
  counterL1++;
}

void incrementLeft2() {
  counterL2++;
}

void incrementRight1() {
  counterR1++;
}

void incrementRight2() {
  counterR2++;
}

