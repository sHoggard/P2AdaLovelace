#include <Servo.h>

#define pin_motorRight 8

const int quad_A = 2;
const int quad_B = 13;
const unsigned int mask_quad_A = digitalPinToBitMask(quad_A);
const unsigned int mask_quad_B = digitalPinToBitMask(quad_B);  

Servo motorRight;

void setup() {
    Serial.begin(9600);  
    delay(100);
    
    // activate peripheral functions for quad pins
    REG_PIOB_PDR = mask_quad_A;     // activate peripheral function (disables all PIO functionality)
    REG_PIOB_ABSR |= mask_quad_A;   // choose peripheral option B    
    REG_PIOB_PDR = mask_quad_B;     // activate peripheral function (disables all PIO functionality)
    REG_PIOB_ABSR |= mask_quad_B;   // choose peripheral option B 
    
    // activate clock for TC0
    REG_PMC_PCER0 = (1<<27);
    // select XC0 as clock source and set capture mode
    REG_TC0_CMR0 = 5; 
    // activate quadrature encoder and position measure mode, no filters
    REG_TC0_BMR = (1<<9)|(1<<8)|(1<<12);
    // enable the clock (CLKEN=1) and reset the counter (SWTRG=1) 
    // SWTRG = 1 necessary to start the clock!!
    REG_TC0_CCR0 = 5;
    pinMode(pin_motorRight, INPUT);
    while (digitalRead(pin_motorRight) == 0) {
      delayMicroseconds(100);
    }
    digitalWrite(pin_motorRight, LOW);
    pinMode(pin_motorRight, OUTPUT);
    motorRight.attach(pin_motorRight, 1000, 2000);
    motorRight.writeMicroseconds(1500);
    delay(20);
    motorRight.writeMicroseconds(1700);
}
    
void loop() {
  Serial.println((signed long)REG_TC0_CV0,DEC);
  delay(500);
}
