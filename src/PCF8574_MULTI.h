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

#define PCF8574_MULTI_PCF8574_ADDRES_I2C  0x20
#define PCF8574_MULTI_DIFF_FOR_A		  0x18	//NUMERO DE DIRECCIONES DE DIFERENCIA ENTRA PCF8574 Y PCF8574A

#define PCF8574_MULTI_MAX_BOARDS 		8		//NUMERO MAXIMO DE BOARDS QUE SE PUEDEN CONTROLAR TANTO PCF8574 y PCF8574A.
#define PCF8574_MULTI_MAX_PIN			64		//NUMERO MAXIMO DE PIN's SOPORTADOS
#define PCF8574_MULTI_NUM_BOARDS		1		//NUMERO DE BOARDS CONTROLADAS

#define PCF8574_MULTI_TDEV_PCF8574		0		//REF DEV PCF8574		ADDRESS 0100xxx
#define PCF8574_MULTI_TDEV_PCF8574A		1		//REF DEV PCF8574A		ADDRESS 0111xxx

//#define DEBUG

#include <Arduino.h>
#include <Wire.h>
#include "PCF8574.h"

struct InfoDatosPin {
  uint8_t 	board;
  uint8_t	boardarray;
  uint8_t 	pinA;
  uint8_t 	pinB;
  bool 		err;
};

class PCF8574_MULTI
{
  private:
	uint8_t _DEV_TYPE;
    uint8_t _NUM_BOARDS;
	int 	_ADDRES_WIRE;
	
	int		_ADDRES_I2C[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	PCF8574 _PCF8574_DEV[8];
	
	bool 	_BEGIN_OK = false;
	
	void 	PCF8574_MULTI::Init(byte typedev,byte nBoards);
	
	int 	PCF8574_MULTI::GetNumBoardByPin(byte pin);
	int  	PCF8574_MULTI::GetAddresByPin(byte pin);
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
	
	int 	PCF8574_MULTI::AddressI2C(byte nb);
	void 	PCF8574_MULTI::AddressI2C(byte nb, int address);

	
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
