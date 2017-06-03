//  Copyright (C) 2017 Javier Pastor
//  http://www.cerebelum.net
//
// Este archivo forma parte de PCF8574_MULTI.
//
// PCF8574_MULTI es software libre: se puede redistribuir y / o modificar
// bajo los términos de la GNU Lesser General Public License como
// publicado por la Free Software Foundation, ya sea la versión 3 de
// la Licencia, o (a su elección) cualquier versión posterior.
//
// PCF8574_MULTI se distribuye con la esperanza de que sea útil,
// pero SIN NINGUNA GARANTÍA; Sin la garantía implícita de
// MERCANTIBILIDAD o ADECUACIÓN PARA UN PROPÓSITO PARTICULAR. Vea el
// GNU Lesser General Public License para más detalles.
//
// Debería haber recibido una copia del Público General Menor de GNU
// Licencia junto con PCF8574_MULTI. Si no, vea
// <http://www.gnu.org/licenses/>.
//

#ifndef PCF8574_MULTI_H
#define PCF8574_MULTI_H

#define PCF8574_MULTI_PCF8574_ADDRES_1_I2C  0x20
#define PCF8574_MULTI_PCF8574_ADDRES_2_I2C  0x21
#define PCF8574_MULTI_PCF8574_ADDRES_3_I2C  0x22
#define PCF8574_MULTI_PCF8574_ADDRES_4_I2C  0x23
#define PCF8574_MULTI_PCF8574_ADDRES_5_I2C  0x24
#define PCF8574_MULTI_PCF8574_ADDRES_6_I2C  0x25
#define PCF8574_MULTI_PCF8574_ADDRES_7_I2C  0x26
#define PCF8574_MULTI_PCF8574_ADDRES_8_I2C  0x27

#define PCF8574_MULTI_PCF8574A_ADDRES_1_I2C 0x38
#define PCF8574_MULTI_PCF8574A_ADDRES_2_I2C 0x39
#define PCF8574_MULTI_PCF8574A_ADDRES_3_I2C 0x3A
#define PCF8574_MULTI_PCF8574A_ADDRES_4_I2C 0x3B
#define PCF8574_MULTI_PCF8574A_ADDRES_5_I2C 0x3C
#define PCF8574_MULTI_PCF8574A_ADDRES_6_I2C 0x3D
#define PCF8574_MULTI_PCF8574A_ADDRES_7_I2C 0x3E
#define PCF8574_MULTI_PCF8574A_ADDRES_8_I2C 0x3F

#define PCF8574_MULTI_MAX_BOARDS 		8		//NUMERO MAXIMO DE BOARDS QUE SE PUEDEN CONTROLAR TANTO PCF8574 y PCF8574A.
#define PCF8574_MULTI_MAX_PIN			64		//NUMERO MAXIMO DE PIN's SOPORTADOS
#define PCF8574_MULTI_NUM_BOARDS		1		//NUMERO DE BOARDS CONTROLADAS

#define PCF8574_MULTI_TDEV_PCF8574		0		//REF DEV PCF8574		ADDRESS 0100xxx
#define PCF8574_MULTI_TDEV_PCF8574A		1		//REF DEV PCF8574A		ADDRESS 0111xxx
#define PCF8574_MULTI_DIFF_FOR_A		0x18	//NUMERO DE DIRECCIONES DE DIFERENCIA ENTRA PCF8574 Y PCF8574A

#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"

struct InfoDatosPin {
  uint8_t 	board;
  uint8_t 	pinA;
  uint8_t 	pinB;
  int 		addressI2C;
  bool 		err;
};

class PCF8574_MULTI
{
  private:
	uint8_t _DEV_TYPE;
    uint8_t _NUM_BOARDS;
	int 	_ADDRES_WIRE;
	
	PCF8574 _PCF8574_DEV[7];
	
	bool _BEGIN_OK = false;
	
	int  PCF8574_MULTI::GetAddresByPin(byte pin);
	InfoDatosPin PCF8574_MULTI::GetInfoPin(byte pin);
	
  public:
    PCF8574_MULTI();
	PCF8574_MULTI(byte typedev);
    PCF8574_MULTI(byte typedev, byte nBoards);

	void 	PCF8574_MULTI::begin();
	
	uint8_t PCF8574_MULTI::TypeDev();
	void 	PCF8574_MULTI::TypeDev(byte type);
	
	int  	PCF8574_MULTI::AddressWire();
	void 	PCF8574_MULTI::AddressWire(int Address_Wire);
	
	void 	PCF8574_MULTI::pinMode(byte pin, byte mode);
	uint8_t PCF8574_MULTI::pinMode(byte pin);
	
	bool 	PCF8574_MULTI::PinIsValid(byte pin);
	uint8_t PCF8574_MULTI::NumPinsAll();
	
	uint8_t PCF8574_MULTI::NumBoars();
    void 	PCF8574_MULTI::NumBoars(byte nBoards);
	
    bool 	PCF8574_MULTI::digitalWrite(byte pin, byte newstatus);
    uint8_t PCF8574_MULTI::digitalRead(byte pin);

    void 	PCF8574_MULTI::ResetPinStatus();
    void 	PCF8574_MULTI::DebugStatusPin(String &sreturn);
};

#endif
