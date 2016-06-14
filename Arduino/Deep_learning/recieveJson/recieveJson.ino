#include <ArduinoJson.h>
#include "MeOrion.h"

MeUltrasonicSensor ultraSensor(PORT_3);

StaticJsonBuffer<200> jsonBuffer;
char json[100];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  /*
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  */
  
  delay(400);
  Serial.print("seiral available:");
  Serial.println(Serial.available());

  if(Serial.available() > 0){
    String jString = Serial.readString();
    Serial.print("jString:");
    Serial.println(jString);
    jString.toCharArray(json, 100);
    JsonObject& root = jsonBuffer.parseObject(json);
    const char* sensor = root["sensor"];
    long time = root["time"];
    Serial.print("time:");
    Serial.println(time);
  }
}
