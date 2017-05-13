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

#define PCF8574_MAX_BOARDS 		16		//NUMERO MAXIMO DE BOARDS QUE SE PUEDEN CONTROLAR TANTO PCF8574 y PCF8574A.
#define PCF8574_NUM_BOARDS		1		//NUMERO DE BOARDS CONTROLADAS
#define PCF8574_NUM_CANALES		8		//NUMERO DE CANALES POR DEFECTO
#define PCF8574_NUM_CANALES_INI	1		//NUMERO DEL CANAL INICIAL POR DEFECTO

#define PCF8574_DEV				1		//REF DEV PCF8574		ADDRESS 0100xxx
#define PCF8574A_DEV			2		//REF DEV PCF8574A		ADDRESS 0111xxx

#include "PCF8574.h"

class PCF8574_MULTI
{
  private:
    int _NUM_CHANNELS = PCF8574_NUM_CANALES;
    int _NUM_CHANNELS_INIT = PCF8574_NUM_CANALES_INI;
	int _DIRECCION_WIRE = PCF8574_DIRECCION_WIRE;
	int _PCF8574_DEV_INIT = PCF8574A_DEV;
	
	int  PCF8574_MULTI::GetAddressWire();
	void PCF8574_MULTI::SetAddressWire(int Channel);

  public:
    PCF8574_MULTI();
    PCF8574_MULTI(int NewNumChannel);
    PCF8574_MULTI(int NewNumChannel, int InitNumChannel);
	PCF8574_MULTI(int NewNumChannel, int InitNumChannel, int Address_Wire);

    int  PCF8574_MULTI::NumeroCanales();
    void PCF8574_MULTI::NumeroCanales(int NewNumChannel);

    int  PCF8574_MULTI::InitNumeroCanales();
    void PCF8574_MULTI::InitNumeroCanales(int NumChannel);
    

    bool PCF8574_MULTI::SetPinStatus(int pin, byte newstatus);
    bool PCF8574_MULTI::ReadPinStatus(int pin);

    void PCF8574_MULTI::ResetPinStatus();
    void PCF8574_MULTI::DebugStatusPin(String &sreturn);
};

#endif
