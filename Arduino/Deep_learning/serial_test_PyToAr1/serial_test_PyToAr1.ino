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
  if(Serial.available() > 0) {
    char data = Serial.read();
    char str[2];
    str[0] = data;
    if(data=='s'){
      Serial.println("received e");
      Serial.print("Distance : ");
      Serial.print(ultraSensor.distanceCm() );
      Serial.println(" cm");      
    }
     if(data = 'm'){/*
      if(Serial.available() > 0){
        char char_num = Serial.read();
        int num = (int)char_num - 48;
      }*/
       Serial.print("motor");
      motor3.run(motorSpeed);
      delay(1000);
      motor3.stop();
    }
  }
}

/*
    if(data = 'm'){
       Serial.print("motor");
      //motor3.run(motorSpeed);
    }
    if(data = 'p'){
       Serial.print("pause");
      //motor3.stop();
    }
    
    if(data = 's'){
       Serial.print("sensor");
      //motor3.run(motorSpeed);
    }
    
    
    Serial.print("abc");*/
