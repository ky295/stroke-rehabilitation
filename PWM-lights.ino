#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

pwm.begin();
pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

bluePin = 2;
greenPin = 3;

void setup() {

//setup all PWM pins to high
  pwm.setPWM(bluePin, 0, 4096);
  pwm.setPWM(greenPin, 0, 4096);

}

void loop() {
  // set state 1
  pwm.setPWM(bluePin, 0, 4096);
  pwm.setPWM(greenPin, 0, 4096);

  // wait
  delay(500);

  // set state 2
  digitalWrite(LED_BUILTIN, LOW);
  pwm.setPWM(bluePin, 4096, 0);
  pwm.setPWM(greenPin, 4096, 0);

  // wait
  delay(500);
}
