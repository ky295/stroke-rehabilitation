#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int greenPin = 3;
int bluePin = 2;
int x;
int y;
int noOfHits = 0;
int drumPadList[] = {2,3,4,5,6,7,8,9};
const int DRUM_PAD = 3;
unsigned long time_now = 0;
int bluePinList[] = {0,2,4,6,8,10,12};
int greenPinList[] = {1,3,5,7,9,11,13};
void setup() {
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
//setup all PWM pins to high
  pwm.setPWM(bluePin, 4096, 0);
  pwm.setPWM(greenPin, 4096, 0);
  pwm.setPWM(0, 4096, 0);
  pwm.setPWM(1, 4096, 0);
  pwm.setPWM(4, 4096, 0);
  pwm.setPWM(5, 4096, 0);
  pwm.setPWM(6, 4096, 0);
  pwm.setPWM(7, 4096, 0);
  pwm.setPWM(8, 4096, 0);
  pwm.setPWM(9, 4096, 0);
  pwm.setPWM(10, 4096, 0);
  pwm.setPWM(11, 4096, 0);
  pwm.setPWM(12, 4096, 0);
  pwm.setPWM(13, 4096, 0);
  x=0;
  y=0;


}

void loop() {
  time_now = millis();
  while (millis() < time_now + 900) {
    pwm.setPWM(bluePinList[x], 0, 4096);
    y=x;
    if (digitalRead(drumPadList[x])==HIGH) {
      noOfHits+=1;
      pwm.setPWM(greenPinList[x], 0, 4096);
      pwm.setPWM(bluePinList[x], 4096, 0);
//      x=(x+1)%7;
      x = random(0,7);
      delay(400); //how long green light lasts
      break;
      }
   Serial.println(["hits ", noOfHits]);
    }
  while (millis() < time_now + 1000) {
    pwm.setPWM(bluePinList[y], 4096, 0);
    pwm.setPWM(greenPinList[y], 4096, 0);
    }
}
