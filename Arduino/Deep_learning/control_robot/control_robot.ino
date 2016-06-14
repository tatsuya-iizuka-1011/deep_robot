#include "MeOrion.h"
#include <ArduinoJson.h>
MeDCMotor wheel_r(PORT_1);

MeDCMotor wheel_l(PORT_2);

MeDCMotor arm_r(M1);

MeDCMotor arm_l(M2);

MeUltrasonicSensor ultraSensor(PORT_3);

char jsonChar[100];

int wheel_r_speed = 50;
int wheel_l_speed = 50;
int arm_r_speed = 50;
int arm_l_speed = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  wheel_r.run(wheel_r_speed); /* value: between -255 and 255. */
  wheel_l.run(wheel_l_speed); /* value: between -255 and 255. */
  arm_r.run(arm_r_speed);
  arm_l.run(arm_l_speed);
  delay(100);
  wheel_r.stop();
  wheel_l.stop();
  arm_r.stop();
  arm_l.stop();
  
  if(Serial.available() > 0){
    
    unsigned long start_time = millis();
    int count = 0; 
    while(Serial.available() > 0){
      jsonChar[count] = Serial.read();
      if ( jsonChar[count] == '#') {
        jsonChar[count] = '\0';
        count = 0;
      } else {
        count++;
      }
    }
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(jsonChar);
    wheel_r_speed = json["wheel_r"];
    wheel_l_speed = json["wheel_r"];
    arm_r_speed = json["arm_r"];
    arm_l_speed = json["arm_l"];
  }
  StaticJsonBuffer<200> jsonSendBuffer;
  JsonObject& sendData = jsonSendBuffer.createObject();
  sendData["distance"] = ultraSensor.distanceCm();
  sendData["wheel_r_speed"] = wheel_r_speed;
  sendData["wheel_l_speed"] = wheel_r_speed;
  sendData["arm_r_speed"] = arm_r_speed;
  sendData["arm_l_speed"] = arm_l_speed;
  char buf[256];
  sendData.printTo(buf, sizeof(buf));
  Serial.println(buf);

}
