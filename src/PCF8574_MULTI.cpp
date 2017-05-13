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


#include "PCF8574_MULTI.h"

/*
 * Method Name  : PCF8574_MULTI
 *
 * Synopsis     : PCF8574_MULTI::PCF8574_MULTI()  *
 * Description  : Inicia el objeto con los valores por defecto que son 
 *                controlar los canales del 1 al 8.
 * 
 * Returns      : 
 */

PCF8574_MULTI::PCF8574_MULTI() {
  InitNumeroCanales(1);
  NumeroCanales(8);
}

PCF8574_MULTI::PCF8574_MULTI(int NewNumChannel) {
  InitNumeroCanales(1);
  NumeroCanales(NewNumChannel);
}

PCF8574_MULTI::PCF8574_MULTI(int NewNumChannel, int InitNumChannel) {
  InitNumeroCanales(InitNumChannel);
  NumeroCanales(NewNumChannel);
}



int PCF8574_MULTI::NumeroCanales() {
  return _numchannels;
}
void PCF8574_MULTI::NumeroCanales(int NewNumChannel) {
  _numchannels = NewNumChannel;
}

int PCF8574_MULTI::InitNumeroCanales() {
  return _initnumchannel;
}
void PCF8574_MULTI::InitNumeroCanales(int NumChannel) {
  _initnumchannel = NumChannel;
}


/*
 * Method Name  : SetPinStatus
 *
 * Synopsis     : bool PCF8574_MULTI::SetPinStatus(short pin, bool newstatus)  *
 * Arguments    : short  pin : Pin del canal que deseamos definir.
 *                bool  newstatus : Nuevo estado del canal
 *
 * Description  : Seteamos el canal que le pasamos con el valor que le especificamos.
 *                Si usamos el canal 0 el nuevo valor se definira en todos los canales.
 * 
 * Returns      : bool 
 */

bool PCF8574_MULTI::SetPinStatus(short pin, bool newstatus) {
  if (pin < InitNumeroCanales()) {
    return false;
  }
  if (pin > NumeroCanales()) {
    return false;
  }
  
  //TODO: PENDIENTE CONTROLAR SOLO LOS CANALES QUE TENEMOS AJUSTADOS ENTRE LOS CANALES INICIO Y FIN.
  int AddressSelect = 0x0;
  if (pin == 0 ) {
    PCF8574 _PCF8574_Z_1(DEFAULT_DIRECCION_PCF8574_1_I2C);
    PCF8574 _PCF8574_Z_2(DEFAULT_DIRECCION_PCF8574_2_I2C);
    PCF8574 _PCF8574_Z_3(DEFAULT_DIRECCION_PCF8574_3_I2C);
    PCF8574 _PCF8574_Z_4(DEFAULT_DIRECCION_PCF8574_4_I2C);
    
    _PCF8574_Z_1.SetPinStatus(0, newstatus);
    _PCF8574_Z_2.SetPinStatus(0, newstatus);
    _PCF8574_Z_3.SetPinStatus(0, newstatus);
    _PCF8574_Z_4.SetPinStatus(0, newstatus);
    return true;
  }
  else if (pin <= 8 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_1_I2C;
  }
  else if (pin <= 16 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_2_I2C;
    pin -= 8;
  }
  else if (pin <= 24 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_3_I2C;
    pin -= 16;
  }
  else if (pin <= 32 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_4_I2C;
    pin -= 24;
  }
  else {
    return false;
  }
  
  PCF8574 _PCF8574_Z(AddressSelect);
  _PCF8574_Z.SetPinStatus(pin, newstatus);
  return true;
}


/*
 * Method Name  : ReadPinStatus
 *
 * Synopsis     : bool PCF8574_MULTI::ReadPinStatus(short pin)  *
 * Arguments    : short  pin : Canal que deseamos leer.
 *
 * Description  : Lee el estado del pin que le solicitamos.
 * 
 * Returns      : bool 
 *
 * NOTA:
 *   Tener en cuenta que si el valor de pin es superior o inferior a los
 *   canales configurados retornara siempre false.
 */
bool PCF8574_MULTI::ReadPinStatus(short pin) {
  if (pin < InitNumeroCanales()) {
    return false;
  }
  if (pin > NumeroCanales()) {
    return false;
  }
  
  int AddressSelect = 0x0;
  if (pin <= 8 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_1_I2C;
  }
  else if (pin <= 16 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_2_I2C;
    pin -= 8;
  }
  else if (pin <= 24 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_3_I2C;
    pin -= 16;
  }
  else if (pin <= 32 ) {
    AddressSelect = DEFAULT_DIRECCION_PCF8574_4_I2C;
    pin -= 24;
  }
  else {
    return false;
  }

  PCF8574 _PCF8574_Z(AddressSelect);
  return _PCF8574_Z.ReadPinStatus(pin);
}


/*
 * Method Name  : ResetPinStatus
 *
 * Synopsis     : void PCF8574_MULTI::ResetPinStatus()  *
 * Description  : Resetea todos los canales y los pone en false.
 * 
 */
void PCF8574_MULTI::ResetPinStatus() {
  SetPinStatus(0, false);
}


/*
 * Method Name  : DebugStatusPin
 *
 * Synopsis     : void PCF8574_MULTI::DebugStatusPin(String &sreturn)  *
 * Description  : Obtenemos el estado de los canales todos en un string en
 *                en formato binario.
 * 
 */
void PCF8574_MULTI::DebugStatusPin(String &sreturn) {
  for (int channel = InitNumeroCanales(); channel <= NumeroCanales(); channel++)
  {
    sreturn = sreturn + ReadPinStatus(channel);
  }
}