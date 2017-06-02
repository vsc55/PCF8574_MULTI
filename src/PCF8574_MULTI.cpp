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
  this->SetAddressWire(PCF8574_ADDRESS_I2C);
  this->SetTypeDev(PCF8574_MULTI_TDEV_PCF8574); 
  this->SetNumBoars(PCF8574_MULTI_NUM_BOARDS);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev) {
  this->SetTypeDev(typedev);
  this->SetAddressWire(PCF8574_ADDRESS_I2C);
  this->SetNumBoars(PCF8574_MULTI_NUM_BOARDS);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev,int nBoards) {
  this->SetTypeDev(typedev);
  this->SetAddressWire(PCF8574_ADDRESS_I2C);
  this->SetNumBoars(nBoards);
}




void PCF8574_MULTI::begin()	{
  if (this->_BEGIN_OK == true ){ return; }
  
  for(int i=0; i < PCF8574_MULTI_MAX_BOARDS; i++)  {
	//Serial.print("Init PCF8574 > "); Serial.print(i);
	this->_PCF8574_DEV[i].SetAddressWire(this->GetAddressWire());
    this->_PCF8574_DEV[i].begin(this->GetAddresByPin(8*i));
	//TODO: Añadir control de pin ini and pin end
	//Serial.println(" > End!");
  }
  this->_BEGIN_OK = true;
  //Serial.println("Begin OK!");
}



	
byte PCF8574_MULTI::GetTypeDev() {
  return this->_DEV_TYPE;
}
void PCF8574_MULTI::SetTypeDev(byte type) {
  this->_DEV_TYPE = type;
}
int  PCF8574_MULTI::GetAddressWire() {
  return this->_ADDRES_WIRE;
}
void PCF8574_MULTI::SetAddressWire(int Address_Wire) {
  this->_ADDRES_WIRE = Address_Wire;
}
int  PCF8574_MULTI::GetAddresByPin(int pin) {
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
  if (this->GetTypeDev() == PCF8574_MULTI_TDEV_PCF8574) {
    AddressSelect -= PCF8574_MULTI_DIFF_FOR_A;
  }
  return AddressSelect;
}




int  PCF8574_MULTI::GetNumBoars() {
	return this->_NUM_BOARDS;
}
void PCF8574_MULTI::SetNumBoars(int nBoards) {
	if (this->_BEGIN_OK == true ) { return; }
	if (nBoards > PCF8574_MULTI_MAX_BOARDS) { return; }
	this->_NUM_BOARDS = nBoards;
}
int  PCF8574_MULTI::NumPinsAll(){
	return this->GetNumBoars() * 8;
}



InfoDatosPin PCF8574_MULTI::GetInfoPin(int pin) {
  InfoDatosPin pininfo;
  
  pininfo.board = 0;
  pininfo.pinA = 0;
  pininfo.pinB = 0;
  pininfo.err = true;
  
  for (int i = 1; i <= PCF8574_MULTI_MAX_BOARDS; i++){
	int npinfor_end = 8 * i;
	int npinfor_ini = npinfor_end - 7;
	if ((pin >= npinfor_ini) && (pin <= npinfor_end)) {
	  pininfo.board = i;
	  pininfo.pinA = pin;
	  pininfo.pinB = (((8 * (i-1)) - pin) * -1);
	  pininfo.addressI2C = this->GetAddresByPin(pin);
	  pininfo.err = false;
	  return pininfo;
	}
  }
  return pininfo;
}
bool PCF8574_MULTI::PinIsValid(int pin) {
  if ((pin < 0) || (pin >PCF8574_MULTI_MAX_PIN)) {
    return false;
  }
  if (pin > this->NumPinsAll()) {
    return false;
  }
  return true;
}



void PCF8574_MULTI::pinMode(int pin, int mode) {
  if (this->_BEGIN_OK == false ){ return; }
  if (this->PinIsValid(pin) == false) { return; }
  
  if (pin == 0)
  {
    for (int i = 1; i <= this->GetNumBoars(); i++){
      this->_PCF8574_DEV[i].pinMode(0, mode);
    }
  }
  else {
	InfoDatosPin pininfo = this->GetInfoPin(pin);
    if (pininfo.err == true) { return PIN_STATUS_ERR; }
    this->_PCF8574_DEV[pininfo.board].pinMode(pininfo.pinB, mode);
  }
}
int PCF8574_MULTI::pinMode(int pin) {
  if (this->_BEGIN_OK == false ){ return -1; }
  if (this->PinIsValid(pin) == false) { return -2; }
  
  InfoDatosPin pininfo = this->GetInfoPin(pin);
  if (pininfo.err == true) { return -2; }
  return this->_PCF8574_DEV[pininfo.board].pinMode(pininfo.pinB);
}






/*
 * Method Name  : digitalWrite
 *
 * Synopsis     : bool PCF8574_MULTI::digitalWrite(int pin, bool newstatus)
 * Arguments    : int   pin : Numero de pin que deseamos cambiar su estado.
 *                bool  newstatus : Nuevo estado del pin.
 *
 * Description  : Reconfiguramos el pin que le pasamos con el valor que le especificamos.
 *                Si usamos el PIN 0, el nuevo valor se configurará en todos los PINES.
 * 
 * Returns      : bool 
 */
bool PCF8574_MULTI::digitalWrite(int pin, byte newstatus) {
  if (this->_BEGIN_OK == false ) { return false; }
  if (this->PinIsValid(pin) == false) { return false; }
  
  if (pin == 0 ) {
    for (int i = 1; i <= this->GetNumBoars(); i++){
      this->_PCF8574_DEV[i].digitalWrite(0, newstatus);
    }
	return true;
  }
  
  InfoDatosPin pininfo = this->GetInfoPin(pin);
  if (pininfo.err == true) { return PIN_STATUS_ERR; } 
  return this->_PCF8574_DEV[pininfo.board].digitalWrite(pininfo.pinB, newstatus);
}


/*
 * Method Name  : digitalRead
 *
 * Synopsis     : bool PCF8574_MULTI::digitalRead(int pin)
 * Arguments    : int  pin : Número del pin que deseamos leer el estado.
 *
 * Description  : Lee el estado del pin que le solicitamos da igual el modo en el que este configurado, siempre se puede leer el estado de cualquier pin.
 * 
 * Returns      : bool 
 *
 * NOTA:
 *   Tener en cuenta que si el valor de pin es superior o inferior a los pones configurados retornara siempre false.
 */
int PCF8574_MULTI::digitalRead(int pin) {
  if (this->_BEGIN_OK == false ) { return PIN_STATUS_ERR; }
  if (pin == 0) { return PIN_STATUS_ERR; }
  if (this->PinIsValid(pin) == false) { return PIN_STATUS_ERR; }
  
  InfoDatosPin pininfo = this->GetInfoPin(pin);
  if (pininfo.err == true) { return PIN_STATUS_ERR; } 
  return this->_PCF8574_DEV[pininfo.board].digitalRead(pininfo.pinB);
}


/*
 * Method Name  : ResetPinStatus
 *
 * Synopsis     : void PCF8574_MULTI::ResetPinStatus()
 * Description  : Pone todos los pines que están en modo OUTPUT en false.
 * 
 */
void PCF8574_MULTI::ResetPinStatus() {
  this->digitalWrite(0, false);
}




//TODO: PENDIENTE REVISAR
void PCF8574_MULTI::DebugStatusPin(String &sreturnpin) {
  if (this->_BEGIN_OK == true ) {
    for (int ipin = 1; this->NumPinsAll(); ipin++)
    {
      sreturnpin = sreturnpin + this->digitalRead(ipin);
    }
  }
}