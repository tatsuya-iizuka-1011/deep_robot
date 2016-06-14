/**************************************************************************/
/*!
    @file     MPL115A1.h
    @author   Y.Kitagami (Akizuki Denshi Tsusho Co., Ltd.)
    @section  HISTORY

    v1.0  - First release

    @license  MIT license
    Copyright (c) 2015 Akizuki Denshi Tsusho Co., Ltd.
    Released under the MIT license
*/
/**************************************************************************/

#ifndef AE_MPL115A1_h
#define AE_MPL115A1_h

#include "Arduino.h"
#include "SPI.h"
	


	// SPI回りの初期設定
	void SPI_MPL115A1_Init(void);
	// SPI書き込み関数
	void SPI_MPL115A1_Write(byte reg,byte val);
	// SPI読出し関数
	byte SPI_MPL115A1_Read(byte reg);
	// MPL115A1の補正データ読出し
	void SPI_MPL115A1_ReadCoefficient(void);
	// MPL115A1のAD変換データ読出し
	void SPI_MPL115A1_ReadPressure(void);
	// MPL115A1の変換後の気圧データ読出し
	float SPI_MPL115A1_Pressure(void);
	// MPL115A1の変換後の温度データ読出し
	float SPI_MPL115A1_Temp(void);

#endif
/* MPL115A1_h*/ 