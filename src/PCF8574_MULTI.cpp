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
  this->SetTypeDev(PCF8574A_DEV_TYPE);
  this->NumeroPins(PCF8574_NUM_PIN);
  this->InitNumeroPin(PCF8574_NUM_PIN_INI);
  this->SetAddressWire(PCF8574_DIRECCION_WIRE);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev) {
  this->SetTypeDev(typedev);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev, int pin) {
  this->SetTypeDev(typedev);
  this->NumeroPins(pin);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev,int pin, int InitPin) {
  this->SetTypeDev(typedev);
  this->NumeroPins(pin);
  this->InitNumeroPin(InitPin);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev,int pin, int InitPin, int Address_Wire) {
  this->SetTypeDev(typedev);
  this->NumeroPins(pin);
  this->InitNumeroPin(InitPin);
  this->SetAddressWire(Address_Wire);
}

	

	
byte PCF8574_MULTI::GetTypeDev() {
  return this->_PCF8574_DEV_TYPE;
}
void PCF8574_MULTI::SetTypeDev(byte type) {
  this->_PCF8574_DEV_TYPE = type;
}
int PCF8574_MULTI::GetAddressWire() {
  return this->_DIRECCION_WIRE;
}
void PCF8574_MULTI::SetAddressWire(int Address_Wire) {
  this->_DIRECCION_WIRE = Address_Wire;
}
int PCF8574_MULTI::GetAddresByPin(int pin) {
  if ((pin < 0) || (pin > PCF8574_MAX_PIN)) {
    return -1;
  }
  int AddressSelect = 0x0;
  if (pin == 0) {
	return 0;
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
  else if (pin <= 40 ) {
    AddressSelect = PCF8574A_DIRECCION_5_I2C;
    pin -=32 ;
  }
  else if (pin <= 48 ) {
    AddressSelect = PCF8574A_DIRECCION_6_I2C;
    pin -= 40;
  }
  else if (pin <= 56 ) {
    AddressSelect = PCF8574A_DIRECCION_7_I2C;
    pin -= 48;
  }
  else if (pin <= 64 ) {
    AddressSelect = PCF8574A_DIRECCION_8_I2C;
    pin -= 56;
  }
  else {
    return -2;
  }
  if (this->GetTypeDev() == PCF8574_DEV_TYPE) {
    AddressSelect -= PCF8574_DIFF_FOR_A;
  }
  return AddressSelect;
}



int PCF8574_MULTI::NumeroPins() {
  return this->_NUM_PINES;
}
bool PCF8574_MULTI::NumeroPins(int pin) {
  /*
  if ((pin < 0) || (pin > PCF8574_MAX_PIN)) {
	return false;
  }
  */
  Serial.print("1SETNEWPIN: "); Serial.println(pin);
  this->_NUM_PINES = pin;
  return true;
}
int PCF8574_MULTI::InitNumeroPin() {
  return this->_NUM_PINES_INIT;
}
bool PCF8574_MULTI::InitNumeroPin(int pin) {
  /*
  if ((pin < 0) || (pin > PCF8574_MAX_PIN)) {
	return false;
  }
  if (pin > this->NumeroPins()) {
    return false;
  }
  */
  Serial.print("2SETNEWPIN: "); Serial.println(pin);
  this->_NUM_PINES_INIT = pin;
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
    if ((pin < this->InitNumeroPin()) && (pin > this->NumeroPins())) {
      return false;
    }
  }
  
  if (pin == 0 ) {
	//TODO: PENDIENTE CONTROLAR SOLO LOS CANALES QUE TENEMOS AJUSTADOS ENTRE LOS CANALES INICIO Y FIN.
	//TODO: PENDIENTE REVISAR NO LO HACE BIEN.
    for (int i = 1; i <= 8; i++){
		int npinfor_end = 8 * i;
		int npinfor_ini = npinfor_end - 7;
		
		/*
		if ((npinfor_ini < this->InitNumeroPin()) || (npinfor_end > this->NumeroPins())) {
			Serial.println("1.0.1.2 -----");
		  continue;
		}
*/
			
			Serial.print("INI: ");
			Serial.print(this->InitNumeroPin());
			Serial.print(" - ");
			Serial.println(npinfor_ini);
			
			Serial.print("END: ");
			Serial.print(npinfor_end);
			Serial.print(" - ");
			Serial.println(this->NumeroPins());
			
			
		
		PCF8574 _PCF8574_Z_1(GetAddresByPin(8 * i), this->GetAddressWire());
		if ((this->InitNumeroPin() == npinfor_ini) && (this->NumeroPins() == npinfor_end)) {
		  Serial.println("1.1 -----");
		  _PCF8574_Z_1.SetPinStatus(0, newstatus);
		}
		else {
		  //RESETEAR SOLO LOS PINES SELECCIONADOS.
		  Serial.println("1.2 -----");
		  if (npinfor_ini < this->InitNumeroPin()) {
		    _PCF8574_Z_1.SetIniPin(this->InitNumeroPin() - npinfor_ini);
		  }
		  if (npinfor_end > this->NumeroPins()) {
		    _PCF8574_Z_1.SetEndPin(npinfor_end - this->NumeroPins());
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
  if (pin < this->InitNumeroPin()) {
    return false;
  }
  if (pin > this->NumeroPins()) {
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
  for (int channel = this->InitNumeroPin(); channel <= this->NumeroPins(); channel++)
  {
    sreturn = sreturn + this->ReadPinStatus(channel);
  }
}