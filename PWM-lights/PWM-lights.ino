#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int greenPin = 3;
int bluePin = 2;
const int DRUM_PAD = 3;
unsigned long time_now = 0;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
//setup all PWM pins to high
  pwm.setPWM(bluePin, 4096, 0);
  pwm.setPWM(greenPin, 4096, 0);
  pwm.setPWM(0, 4096, 0);
  pwm.setPWM(1, 4096, 0);
  pwm.setPWM(3, 4096, 0);
  pwm.setPWM(4, 4096, 0);
  pwm.setPWM(5, 4096, 0);
  pwm.setPWM(6, 4096, 0);
  pwm.setPWM(7, 4096, 0);
  pwm.setPWM(8, 4096, 0);
  pwm.setPWM(0, 4096, 0);
  pwm.setPWM(9, 4096, 0);
  pwm.setPWM(10, 4096, 0);
  pwm.setPWM(11, 4096, 0);
  pwm.setPWM(12, 4096, 0);
  pwm.setPWM(13, 4096, 0);



}

void loop() {
  bluePinLoop();
  greenPinHit();
}

void greenPinHit() {
  time_now
  if (digitalRead(DRUM_PAD)==HIGH) {
    
    }
  }

void bluePinLoop() {
  pwm.setPWM(bluePin, 0, 4096);
  delay(500);
  pwm.setPWM(bluePin, 4096, 0);
  delay(1116);
  
  }
