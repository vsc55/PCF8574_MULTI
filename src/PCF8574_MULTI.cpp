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
  this->InitNumeroCanales(PCF8574_NUM_CANALES_INI);
  this->NumeroCanales(PCF8574_NUM_CANALES);
}

PCF8574_MULTI::PCF8574_MULTI(int NewNumChannel) {
  this->InitNumeroCanales(PCF8574_NUM_CANALES_INI);
  this->NumeroCanales(NewNumChannel);
}
PCF8574_MULTI::PCF8574_MULTI(int NewNumChannel, int InitNumChannel) {
  this->InitNumeroCanales(InitNumChannel);
  this->NumeroCanales(NewNumChannel);
}
PCF8574_MULTI::PCF8574_MULTI(int NewNumChannel, int InitNumChannel, int Address_Wire) {
  this->InitNumeroCanales(InitNumChannel);
  this->NumeroCanales(NewNumChannel);
  this->SetAddressWire(Address_Wire);
}




int PCF8574_MULTI::NumeroCanales() {
  return this->_NUM_CHANNELS;
}
void PCF8574_MULTI::NumeroCanales(int NewNumChannel) {
  this->_NUM_CHANNELS = NewNumChannel;
}
int PCF8574_MULTI::InitNumeroCanales() {
  return this->_NUM_CHANNELS_INIT;
}
void PCF8574_MULTI::InitNumeroCanales(int NumChannel) {
  this->_NUM_CHANNELS_INIT = NumChannel;
}
int PCF8574_MULTI::GetAddressWire() {
  return this->_DIRECCION_WIRE;
}
void PCF8574_MULTI::SetAddressWire(int Channel) {
  this->_DIRECCION_WIRE = Channel;
}




/*
 * Method Name  : SetPinStatus
 *
 * Synopsis     : bool PCF8574_MULTI::SetPinStatus(int pin, bool newstatus)  *
 * Arguments    : int   pin : Pin del canal que deseamos definir.
 *                bool  newstatus : Nuevo estado del canal
 *
 * Description  : Seteamos el canal que le pasamos con el valor que le especificamos.
 *                Si usamos el canal 0 el nuevo valor se definira en todos los canales.
 * 
 * Returns      : bool 
 */

bool PCF8574_MULTI::SetPinStatus(int pin, byte newstatus) {
  if (pin < this->InitNumeroCanales()) {
    return false;
  }
  if (pin > this->NumeroCanales()) {
    return false;
  }
  
  //TODO: PENDIENTE CONTROLAR SOLO LOS CANALES QUE TENEMOS AJUSTADOS ENTRE LOS CANALES INICIO Y FIN.
  //TODO: PENDIENTE CONTROLAR LA VERSION DEL CHIP PCF8574 O PCF8574A.
  int AddressSelect = 0x0;
  if (pin == 0 ) {
    PCF8574 _PCF8574_Z_1(PCF8574A_DIRECCION_1_I2C, this->GetAddressWire());
    PCF8574 _PCF8574_Z_2(PCF8574A_DIRECCION_2_I2C, this->GetAddressWire());
    PCF8574 _PCF8574_Z_3(PCF8574A_DIRECCION_3_I2C, this->GetAddressWire());
    PCF8574 _PCF8574_Z_4(PCF8574A_DIRECCION_4_I2C, this->GetAddressWire());
	PCF8574 _PCF8574_Z_5(PCF8574A_DIRECCION_5_I2C, this->GetAddressWire());
	PCF8574 _PCF8574_Z_6(PCF8574A_DIRECCION_6_I2C, this->GetAddressWire());
	PCF8574 _PCF8574_Z_7(PCF8574A_DIRECCION_7_I2C, this->GetAddressWire());
	PCF8574 _PCF8574_Z_8(PCF8574A_DIRECCION_8_I2C, this->GetAddressWire());
    
    _PCF8574_Z_1.SetPinStatus(0, newstatus);
    _PCF8574_Z_2.SetPinStatus(0, newstatus);
    _PCF8574_Z_3.SetPinStatus(0, newstatus);
    _PCF8574_Z_4.SetPinStatus(0, newstatus);
	_PCF8574_Z_5.SetPinStatus(0, newstatus);
	_PCF8574_Z_6.SetPinStatus(0, newstatus);
	_PCF8574_Z_7.SetPinStatus(0, newstatus);
	_PCF8574_Z_8.SetPinStatus(0, newstatus);
    return true;
  }
  else if (pin <= 8 ) {
    AddressSelect = PCF8574A_DIRECCION_1_I2C;
  }
  else if (pin <= 16 ) {
    AddressSelect = PCF8574A_DIRECCION_2_I2C;
    pin -= 8;
  }
  else if (pin <= 24 ) {
    AddressSelect = PCF8574A_DIRECCION_3_I2C;
    pin -= 16;
  }
  else if (pin <= 32 ) {
    AddressSelect = PCF8574A_DIRECCION_4_I2C;
    pin -= 24;
  }
  else if (pin <= 64 ) {
    AddressSelect = PCF8574A_DIRECCION_5_I2C;
    pin -=32 ;
  }
  else if (pin <= 128 ) {
    AddressSelect = PCF8574A_DIRECCION_6_I2C;
    pin -= 64;
  }
  else if (pin <= 256 ) {
    AddressSelect = PCF8574A_DIRECCION_7_I2C;
    pin -= 128;
  }
  else if (pin <= 512 ) {
    AddressSelect = PCF8574A_DIRECCION_8_I2C;
    pin -= 256;
  }
  else {
    return false;
  }
  
  PCF8574 _PCF8574_Z(AddressSelect, this->GetAddressWire());
  _PCF8574_Z.SetPinStatus(pin, newstatus);
  return true;
}


/*
 * Method Name  : ReadPinStatus
 *
 * Synopsis     : bool PCF8574_MULTI::ReadPinStatus(int pin)  *
 * Arguments    : int  pin : Canal que deseamos leer.
 *
 * Description  : Lee el estado del pin que le solicitamos.
 * 
 * Returns      : bool 
 *
 * NOTA:
 *   Tener en cuenta que si el valor de pin es superior o inferior a los
 *   canales configurados retornara siempre false.
 */
bool PCF8574_MULTI::ReadPinStatus(int pin) {
  if (pin < this->InitNumeroCanales()) {
    return false;
  }
  if (pin > this->NumeroCanales()) {
    return false;
  }
  
  //TODO: PENDIENTE CONTROLAR LA VERSION DEL CHIP PCF8574 O PCF8574A.
  int AddressSelect = 0x0;
  if (pin <= 8 ) {
    AddressSelect = PCF8574A_DIRECCION_1_I2C;
  }
  else if (pin <= 16 ) {
    AddressSelect = PCF8574A_DIRECCION_2_I2C;
    pin -= 8;
  }
  else if (pin <= 24 ) {
    AddressSelect = PCF8574A_DIRECCION_3_I2C;
    pin -= 16;
  }
  else if (pin <= 32 ) {
    AddressSelect = PCF8574A_DIRECCION_4_I2C;
    pin -= 24;
  }
  else if (pin <= 64 ) {
    AddressSelect = PCF8574A_DIRECCION_5_I2C;
    pin -= 32;
  }
  else if (pin <= 128 ) {
    AddressSelect = PCF8574A_DIRECCION_6_I2C;
    pin -= 64;
  }
  else if (pin <= 256 ) {
    AddressSelect = PCF8574A_DIRECCION_7_I2C;
    pin -= 128;
  }
  else if (pin <= 512 ) {
    AddressSelect = PCF8574A_DIRECCION_8_I2C;
    pin -= 256;
  }
  else {
    return false;
  }

  PCF8574 _PCF8574_Z(AddressSelect, this->GetAddressWire());
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
  this->SetPinStatus(0, false);
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
  for (int channel = this->InitNumeroCanales(); channel <= this->NumeroCanales(); channel++)
  {
    sreturn = sreturn + this->ReadPinStatus(channel);
  }
}