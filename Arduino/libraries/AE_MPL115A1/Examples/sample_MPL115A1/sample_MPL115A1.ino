
#include "Arduino.h"
#include "SPI.h"
#include "AE_MPL115A1.h"

void setup() {
  Serial.begin(9600);
  Serial.println("MPL115A1 Test.");
  //MPL115A1　初期化 
  SPI_MPL115A1_Init();
  //MPL115A1　補正データ読出し
  SPI_MPL115A1_ReadCoefficient();  
  
  Serial.println("=====================================");
  Serial.println("MPL115A1 Miniature SPI Digital Barometer");
  // 測定範囲　50 - 115 kPa
  // 精度　+- 1kPa 
  Serial.println("Range: 50 - 115 kPa");
  Serial.println("Accuracy: +- 1kPa (-20*C to 85*C)");
  Serial.println("=====================================");

}

void loop() {
  
  //MPL115A1　気圧のＡＤ値読出し
  SPI_MPL115A1_ReadPressure();

 //MPL115A1　計算後の気圧データ　(kPa)
  Serial.print(SPI_MPL115A1_Pressure());
  Serial.print("kPa");
  Serial.print("\n");
 //MPL115A1　計算後の温度データ (hPa)
  Serial.print(SPI_MPL115A1_Pressure()*10);
  Serial.print("hPa");
  Serial.print("\n");
 //MPL115A1　計算後の温度データ (℃)
  Serial.print(SPI_MPL115A1_Temp());
  Serial.print("*C");
  Serial.print("\n");
  Serial.print("----------------------------------");
  Serial.print("\n");
  delay(1000);
}


