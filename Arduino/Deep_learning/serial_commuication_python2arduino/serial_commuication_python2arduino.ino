#include "MeOrion.h"

MeDCMotor motor1(PORT_1);

MeDCMotor motor2(PORT_2);

MeDCMotor motor3(M1);

MeDCMotor motor4(M2);

MeUltrasonicSensor ultraSensor(PORT_3);


uint8_t motorSpeed = 100;


void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hello world from Ardunio!"); // write a string
  delay(1000);
}
