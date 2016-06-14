/**************************************************************************/
/*!
    @file     MPL115A1.c
    @author   Y.Kitagami (Akizuki Denshi Tsusho Co., Ltd.)
    @section  HISTORY

    v1.0  - First release

    @license  MIT license
    Copyright (c) 2015 Akizuki Denshi Tsusho Co., Ltd.
    Released under the MIT license
*/
/**************************************************************************/
#include "Arduino.h"
#include "SPI.h"
#include "AE_MPL115A1.h"

    
int SPI_MPL115A1_CS = 10;     // チップセレクタのポート番号
float SPI_MPL115A1_a0 ;       // 補正データの保存用変数
float SPI_MPL115A1_b1 ;       // 補正データの保存用変数
float SPI_MPL115A1_b2 ;       // 補正データの保存用変数
float SPI_MPL115A1_c12 ;      // 補正データの保存用変数
unsigned long SPI_MPL115A1_Pressure_AD ;   // 補正前の気圧データ
unsigned long SPI_MPL115A1_Temp_AD ;       // 補正前の温度データ

//---------------------------------------------------------------------------------//
// ＳＰＩ回りの初期設定
//---------------------------------------------------------------------------------//
void SPI_MPL115A1_Init(void)
{
  // チップセレクタのポート設定
  pinMode(SPI_MPL115A1_CS,OUTPUT);  
  digitalWrite(SPI_MPL115A1_CS, HIGH);  
  // SPIの初期化
  SPI.begin() ;                    
  SPI.setBitOrder(MSBFIRST) ;
  SPI.setClockDivider(SPI_CLOCK_DIV4) ;
  SPI.setDataMode(SPI_MODE0) ;
}

//---------------------------------------------------------------------------------//
// ＳＰＩ書き込み関数
//---------------------------------------------------------------------------------//
void SPI_MPL115A1_Write(byte reg,byte val)
{
  //MPL115A1データ書き込み
  digitalWrite(SPI_MPL115A1_CS, LOW);
  SPI.transfer(reg);
  SPI.transfer(val);
  digitalWrite(SPI_MPL115A1_CS, HIGH);  
}

//---------------------------------------------------------------------------------//
// ＳＰＩ読出し関数
//---------------------------------------------------------------------------------//
byte SPI_MPL115A1_Read(byte reg)
{
  //MPL115A1データ読出し
  byte ret=0;
  digitalWrite(SPI_MPL115A1_CS, LOW);
  SPI.transfer(reg);
  ret = SPI.transfer(0);
  digitalWrite(SPI_MPL115A1_CS, HIGH);
  return ret;
}

//---------------------------------------------------------------------------------//
// MPL115A1の補正データ読出し
//---------------------------------------------------------------------------------//
void SPI_MPL115A1_ReadCoefficient(void)
{
  //MPL1151補正データ処理
   unsigned int h , l ;
   h = SPI_MPL115A1_Read(0x88);
   l = SPI_MPL115A1_Read(0x8a);
   SPI_MPL115A1_a0 = (h << 5) + (l >> 3) + (l & 0x07) / 8.0;
   h = SPI_MPL115A1_Read(0x8c);
   l = SPI_MPL115A1_Read(0x8e);
   SPI_MPL115A1_b1 = ( ( ( (h & 0x1F) * 0x100 ) + l ) / 8192.0 ) - 3;
   h = SPI_MPL115A1_Read(0x90);
   l = SPI_MPL115A1_Read(0x92);
   SPI_MPL115A1_b2 = ( ( ( ( h - 0x80) << 8 ) + l ) / 16384.0 ) - 2;
   h = SPI_MPL115A1_Read(0x94);
   l = SPI_MPL115A1_Read(0x96);
   SPI_MPL115A1_c12 = (( (uint16_t) (h << 8) | l)) >> 2;
   SPI_MPL115A1_c12 /= 4194304.0;
}

//---------------------------------------------------------------------------------//
// MPL115A1のＡＤ変換データ読出し
//---------------------------------------------------------------------------------//
void SPI_MPL115A1_ReadPressure(void)
{
  //MPL115A1気圧＆温度のＡＤ値取得
  unsigned int h , l ;
  SPI_MPL115A1_Write(0x24,0x00);
  delay(3);
   h = SPI_MPL115A1_Read(0x80);
   l = SPI_MPL115A1_Read(0x82);
   SPI_MPL115A1_Pressure_AD =(( h << 8) | l) >> 6;
   h = SPI_MPL115A1_Read(0x84);
   l = SPI_MPL115A1_Read(0x86);
   SPI_MPL115A1_Temp_AD = (( h << 8) | l) >> 6;
}

//---------------------------------------------------------------------------------//
// MPL115A1の変換後の気圧データ読出し
//---------------------------------------------------------------------------------//
float SPI_MPL115A1_Pressure(void)
{
  //MPL115　気圧値出力（kPa)
  float ret , f ;
  f = SPI_MPL115A1_a0 + ( SPI_MPL115A1_b1 + SPI_MPL115A1_c12 * SPI_MPL115A1_Temp_AD ) * SPI_MPL115A1_Pressure_AD + SPI_MPL115A1_b2 * SPI_MPL115A1_Temp_AD ;
  ret = f * ( 65.0 / 1023.0 ) + 50.0 ;
  return ret ;
}

//---------------------------------------------------------------------------------//
// MPL115A1の変換後の温度データ読出し
//---------------------------------------------------------------------------------//
float SPI_MPL115A1_Temp(void)
{
  //MPL115A1 温度情報出力(℃)
  return ((float) SPI_MPL115A1_Temp_AD - 498.0F) / -5.35F +25.0F ;
}

//---------------------------------------------------------------------------------//
// End.