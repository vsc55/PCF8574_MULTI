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
  this->SetTypeDev(PCF8574_MULTI_DEV_TYPE_PCF8574A);
  this->Pins(PCF8574_MULTI_NUM_PIN_INI, PCF8574_MULTI_NUM_PIN_END);
  this->SetAddressWire(PCF8574_DIRECCION_WIRE);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev) {
  this->SetTypeDev(typedev);
  this->Pins(PCF8574_MULTI_NUM_PIN_INI, PCF8574_MULTI_NUM_PIN_END);
  this->SetAddressWire(PCF8574_DIRECCION_WIRE);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev, int pin) {
  this->SetTypeDev(typedev);
  this->Pins(PCF8574_MULTI_NUM_PIN_INI, pin);
  this->SetAddressWire(PCF8574_DIRECCION_WIRE);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev,int pinIni, int PinEnd) {
  this->SetTypeDev(typedev);
  this->Pins(pinIni, PinEnd);
  this->SetAddressWire(PCF8574_DIRECCION_WIRE);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev,int pinIni, int PinEnd, int Address_Wire) {
  this->SetTypeDev(typedev);
  this->Pins(pinIni, PinEnd);
  this->SetAddressWire(Address_Wire);
}

	

	
byte PCF8574_MULTI::GetTypeDev() {
  return this->_DEV_TYPE;
}
void PCF8574_MULTI::SetTypeDev(byte type) {
  this->_DEV_TYPE = type;
}
int PCF8574_MULTI::GetAddressWire() {
  return this->_ADDRES_WIRE;
}
void PCF8574_MULTI::SetAddressWire(int Address_Wire) {
  this->_ADDRES_WIRE = Address_Wire;
}
int PCF8574_MULTI::GetAddresByPin(int pin) {
  if ((pin < 0) || (pin > PCF8574_MULTI_MAX_PIN)) {
    return -1;
  }
  int AddressSelect = 0x0;
  if (pin == 0) {
	return 0;
  }
  else if (pin <= 8 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_1_I2C;
  }
  else if (pin <= 16 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_2_I2C;
    pin -= 8;
  }
  else if (pin <= 24 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_3_I2C;
    pin -= 16;
  }
  else if (pin <= 32 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_4_I2C;
    pin -= 24;
  }
  else if (pin <= 40 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_5_I2C;
    pin -=32 ;
  }
  else if (pin <= 48 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_6_I2C;
    pin -= 40;
  }
  else if (pin <= 56 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_7_I2C;
    pin -= 48;
  }
  else if (pin <= 64 ) {
    AddressSelect = PCF8574_MULTI_PCF8574A_ADDRES_8_I2C;
    pin -= 56;
  }
  else {
    return -2;
  }
  if (this->GetTypeDev() == PCF8574_MULTI_DEV_TYPE_PCF8574) {
    AddressSelect -= PCF8574_MULTI_DIFF_FOR_A;
  }
  return AddressSelect;
}




int PCF8574_MULTI::PinIni() {
  return this->_NUM_PINES_INI;
}
bool PCF8574_MULTI::PinIni(int pin) {
  /*
  if ((pin < 0) || (pin > PCF8574_MAX_PIN)) {
	return false;
  }
  if (pin > this->PinEnd()) {
    return false;
  }
  */
  Serial.print("2SETNEWPIN: "); Serial.println(pin);
  this->_NUM_PINES_INI = pin;
  return true;
}
int PCF8574_MULTI::PinEnd() {
  return this->_NUM_PINES_END;
}
bool PCF8574_MULTI::PinEnd(int pin) {
  /*
  if ((pin < 0) || (pin > PCF8574_MAX_PIN)) {
	return false;
  }
  */
  Serial.print("1SETNEWPIN: "); Serial.println(pin);
  this->_NUM_PINES_END = pin;
  return true;
}
bool PCF8574_MULTI::Pins(int pinini, int pinend) {
	this->PinIni(pinini);
	this->PinEnd(pinend);
	return true;
}
bool PCF8574_MULTI::PinIsValid(int pin) {
  if (pin < this->PinIni()) {
    return false;
  }
  if (pin > this->PinEnd()) {
	return false;
  }
  return true;
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
  if (pin != 0) {
	if (this->PinIsValid(pin) == false) {
	  return false;
	}
  }
  
  if (pin == 0 ) {
	
	//TODO: PENDIENTE CONTROLAR SOLO LOS PINES QUE TENEMOS AJUSTADOS ENTRE LOS PINES INICIO Y FIN.
	//TODO: PENDIENTE REVISAR NO LO HACE BIEN.
    for (int i = 1; i <= 8; i++){
		int npinfor_end = 8 * i;
		int npinfor_ini = npinfor_end - 7;
		
		PCF8574 _PCF8574_Z_1(GetAddresByPin(8 * i), this->GetAddressWire());
		if ((this->PinIni() == npinfor_ini) && (this->PinEnd() == npinfor_end)) {
		  _PCF8574_Z_1.SetPinStatus(0, newstatus);
		}
		else {
		  //RESETEAR SOLO LOS PINES SELECCIONADOS.
		  //Serial.print("INI: "); Serial.print(this->PinIni()); Serial.print(" - "); Serial.println(npinfor_ini);
		  //Serial.print("END: "); Serial.print(npinfor_end); Serial.print(" - "); Serial.println(this->PinEnd());
		  if (npinfor_ini < this->PinIni()) {
		    _PCF8574_Z_1.SetIniPin(this->PinIni() - npinfor_ini);
		  }
		  if (npinfor_end > this->PinEnd()) {
		    _PCF8574_Z_1.SetEndPin(npinfor_end - this->PinEnd());
		  }
		  _PCF8574_Z_1.SetPinStatus(0, newstatus);	
		}
    }
	return true;
  }
  
  int AddressSelect = 0x0;
  AddressSelect = this->GetAddresByPin(pin);
  if (AddressSelect < 0) {
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
 * Arguments    : int  pin : Numero del pin que deseamos leer el estado.
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
  if (this->PinIsValid(pin) == false) {
    return false;
  }
  int AddressSelect = 0x0;
  AddressSelect = this->GetAddresByPin(pin);
  if (AddressSelect < 0) {
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
  for (int ipin = this->PinIni(); ipin <= this->PinEnd(); ipin++)
  {
    sreturn = sreturn + this->ReadPinStatus(ipin);
  }
}