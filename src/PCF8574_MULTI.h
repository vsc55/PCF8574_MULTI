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

#define DEFAULT_DIRECCION_PCF8574_1_I2C 0x38
#define DEFAULT_DIRECCION_PCF8574_2_I2C 0x39
#define DEFAULT_DIRECCION_PCF8574_3_I2C 0x40
#define DEFAULT_DIRECCION_PCF8574_4_I2C 0x41

#include "PCF8574.h"


class PCF8574_MULTI
{
  private:
    int _numchannels = 8;
    int _initnumchannel = 1;

  public:
    PCF8574_MULTI();
    PCF8574_MULTI(int NewNumChannel);
    PCF8574_MULTI(int NewNumChannel, int InitNumChannel);

    int  PCF8574_MULTI::NumeroCanales();
    void PCF8574_MULTI::NumeroCanales(int NewNumChannel);

    int  PCF8574_MULTI::InitNumeroCanales();
    void PCF8574_MULTI::InitNumeroCanales(int NumChannel);
    

    bool PCF8574_MULTI::SetPinStatus(short pin, bool newstatus);
    bool PCF8574_MULTI::ReadPinStatus(short pin);

    void PCF8574_MULTI::ResetPinStatus();
    void PCF8574_MULTI::DebugStatusPin(String &sreturn);
};

#endif
