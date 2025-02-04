#include <ESP32Servo.h>

static const int servoPin = 18;

Servo servo1;

void setup() {

  Serial.begin(115200);
  servo1.attach(servoPin);
}

void loop() 
{
  for(int posDegrees = 0; posDegrees <= 90; posDegrees++) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }

  for(int posDegrees = 90; posDegrees >= 0; posDegrees--) 
  {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}