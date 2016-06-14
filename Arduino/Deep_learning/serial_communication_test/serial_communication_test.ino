void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  if(Serial.available() > 0){
    char data = Serial.read();
    Serial.print(data);
  }
}
