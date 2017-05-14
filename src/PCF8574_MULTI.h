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

#define PCF8574_DIRECCION_1_I2C  0x20
#define PCF8574_DIRECCION_2_I2C  0x21
#define PCF8574_DIRECCION_3_I2C  0x22
#define PCF8574_DIRECCION_4_I2C  0x23
#define PCF8574_DIRECCION_5_I2C  0x24
#define PCF8574_DIRECCION_6_I2C  0x25
#define PCF8574_DIRECCION_7_I2C  0x26
#define PCF8574_DIRECCION_8_I2C  0x27

#define PCF8574A_DIRECCION_1_I2C 0x38
#define PCF8574A_DIRECCION_2_I2C 0x39
#define PCF8574A_DIRECCION_3_I2C 0x3A
#define PCF8574A_DIRECCION_4_I2C 0x3B
#define PCF8574A_DIRECCION_5_I2C 0x3C
#define PCF8574A_DIRECCION_6_I2C 0x3D
#define PCF8574A_DIRECCION_7_I2C 0x3E
#define PCF8574A_DIRECCION_8_I2C 0x3F

#define PCF8574_DIFF_FOR_A		0x18	//NUMERO DE DIRECCIONES DE DIFERENCIA ENTRA PCF8574 Y PCF8574A

#define PCF8574_MAX_BOARDS 		8		//NUMERO MAXIMO DE BOARDS QUE SE PUEDEN CONTROLAR TANTO PCF8574 y PCF8574A.
#define PCF8574_MAX_PIN			64		//NUMERO MAXIMO DE CANALES SOPORTADOS
#define PCF8574_NUM_BOARDS		1		//NUMERO DE BOARDS CONTROLADAS
#define PCF8574_NUM_PIN			8		//NUMERO DE PINES POR DEFECTO
#define PCF8574_NUM_PIN_INI		1		//NUMERO DEL PIN INICIAL POR DEFECTO

#define PCF8574_DEV_TYPE		0		//REF DEV PCF8574		ADDRESS 0100xxx
#define PCF8574A_DEV_TYPE		1		//REF DEV PCF8574A		ADDRESS 0111xxx

#include "PCF8574.h"

class PCF8574_MULTI
{
  private:
    int _NUM_PINES = PCF8574_NUM_PIN;
    int _NUM_PINES_INIT = PCF8574_NUM_PIN_INI;
	int _DIRECCION_WIRE = PCF8574_DIRECCION_WIRE;
	byte _PCF8574_DEV_TYPE = PCF8574A_DEV_TYPE;
	
	
	byte PCF8574_MULTI::GetTypeDev();
	void PCF8574_MULTI::SetTypeDev(byte type);
	
	int  PCF8574_MULTI::GetAddressWire();
	void PCF8574_MULTI::SetAddressWire(int Address_Wire);
	
	int  PCF8574_MULTI::GetAddresByPin(int pin);

  public:
    PCF8574_MULTI();
	PCF8574_MULTI(byte typedev);
    PCF8574_MULTI(byte typedev, int pin);
    PCF8574_MULTI(byte typedev, int pin, int InitPin);
	PCF8574_MULTI(byte typedev, int pin, int InitPin, int Address_Wire);

    int  PCF8574_MULTI::NumeroPins();
    bool PCF8574_MULTI::NumeroPins(int pin);

    int  PCF8574_MULTI::InitNumeroPin();
    bool PCF8574_MULTI::InitNumeroPin(int pin);
    

    bool PCF8574_MULTI::SetPinStatus(int pin, byte newstatus);
    bool PCF8574_MULTI::ReadPinStatus(int pin);

    void PCF8574_MULTI::ResetPinStatus();
    void PCF8574_MULTI::DebugStatusPin(String &sreturn);
};

#endif
