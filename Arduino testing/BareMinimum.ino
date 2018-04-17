#define motor_right D2
#define motor_left  D3

int counter;
bool accelerate;

void setup() {
  // put your setup code here, to run once:
  counter = 150;
  accelerate = true;
  if (digitalRead(2) == 0 || digitalRead(3) == 0) {
    delay(5);
  }
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  delay(5);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delay(150);               //stop
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(20);                //stop
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delay(counter);             //accelerating forward
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(150);               //pause
  if (accelerate) {
    counter++;
  } else {
    counter--;
  }
  if (counter == 200) {
    accelerate = false;
  }
  if (counter == 100) {
    accelerate = true;
  }
}
