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
  this->Init(PCF8574_MULTI_TDEV_PCF8574, PCF8574_MULTI_NUM_BOARDS);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev) {
  this->Init(typedev, PCF8574_MULTI_NUM_BOARDS);
}
PCF8574_MULTI::PCF8574_MULTI(byte typedev,byte nBoards) {
  this->Init(typedev, nBoards);
}




void PCF8574_MULTI::Init(byte typedev,byte nBoards) {
  this->TypeDev(typedev);
  this->NumBoards(nBoards);
  this->AddressWire(PCF8574_ADDRESS_I2C);
}
void PCF8574_MULTI::begin()	{
  if (this->_BEGIN_OK == true ){ return; }
  byte iboard = 0;
  for(byte i = 0; i < PCF8574_MULTI_MAX_BOARDS; i++)  {
	if (i == this->NumBoards()) { break; }
	
	iboard = i + 1;
	this->_PCF8574_DEV[i].AddressWire(this->AddressWire());
	this->_PCF8574_DEV[i].AddressI2C(this->GetAddresByPin(iboard * 8));
    this->_PCF8574_DEV[i].begin();
	
	#ifdef DEBUG
	  Serial.print("- Begin ("); Serial.print(i); Serial.print("): "); Serial.println(this->_PCF8574_DEV[i].isBegin());
    #endif
  }
  this->_BEGIN_OK = true;
}





int 	PCF8574_MULTI::AddressI2C(byte nb) {
  if ((nb < 1) || (nb > PCF8574_MULTI_MAX_BOARDS)) { return -1; }
  return this->_ADDRES_I2C[nb];
}
void 	PCF8574_MULTI::AddressI2C(byte nb, int address) {
  if ((nb < 1) || (nb > PCF8574_MULTI_MAX_BOARDS)) { return; }
  this->_ADDRES_I2C[nb] = address;
}




	
byte 	PCF8574_MULTI::TypeDev() {
  return this->_DEV_TYPE;
}
void 	PCF8574_MULTI::TypeDev(byte type) {
  this->_DEV_TYPE = type;
}
int  	PCF8574_MULTI::AddressWire() {
  return this->_ADDRES_WIRE;
}
void 	PCF8574_MULTI::AddressWire(int Address_Wire) {
  this->_ADDRES_WIRE = Address_Wire;
}




int 	PCF8574_MULTI::GetNumBoardByPin(byte pin) {
  if ((pin < 0) || (pin > PCF8574_MULTI_MAX_PIN)) { return -1; }
  if (pin == 0) { return 0; }
  
  int mm = 0;
  for (int i = 0; i < PCF8574_MULTI_MAX_BOARDS; i++){
    mm = pin - (8 * i);
    if (mm <= 0) {
	  return i;
      //break;
    }
  }
  return 0;
}
int 	PCF8574_MULTI::GetAddresByPin(byte pin) {
  if ((pin < 0) || (pin > PCF8574_MULTI_MAX_PIN)) { return -1; }
  if (pin > (this->NumBoards() * 8)) {  return -2; }
  if (pin == 0) { return 0; }
  
  int NumBoardInToPin = this->GetNumBoardByPin(pin);
  int NumBoardInToPinArray = NumBoardInToPin - 1;
  int AddressBoard = 0x00;
  
  if (this->_BEGIN_OK == true ) {
	AddressBoard = this->_PCF8574_DEV[NumBoardInToPinArray].AddressI2C();
  }
  else {
    AddressBoard = this->_ADDRES_I2C[NumBoardInToPinArray];
	if (AddressBoard == 0x00) {
	  AddressBoard = PCF8574_MULTI_PCF8574_ADDRES_I2C + NumBoardInToPinArray;
      if (this->TypeDev() == PCF8574_MULTI_TDEV_PCF8574A) {
		AddressBoard += PCF8574_MULTI_DIFF_FOR_A;
      }
	}
  }
  return AddressBoard;
}




uint8_t PCF8574_MULTI::NumBoards() {
	return this->_NUM_BOARDS;
}
void 	PCF8574_MULTI::NumBoards(byte nBoards) {
	if (this->_BEGIN_OK == true ) { return; }
	if ((nBoards < 1) || (nBoards > PCF8574_MULTI_MAX_BOARDS)) { return; }
	this->_NUM_BOARDS = nBoards;
}
uint8_t PCF8574_MULTI::NumPinsAll(){
	return this->NumBoards() * 8;
}



InfoDatosPin PCF8574_MULTI::GetInfoPin(byte pin) {
  InfoDatosPin pininfo;
  
  pininfo.board = 0;
  pininfo.boardarray = 0;
  pininfo.pinA = 0;
  pininfo.pinB = 0;
  pininfo.err = true;
  
  for (byte i = 1; i <= PCF8574_MULTI_MAX_BOARDS; i++){
	byte npinfor_end = 8 * i;
	byte npinfor_ini = npinfor_end - 7;
	if ((pin >= npinfor_ini) && (pin <= npinfor_end)) {
	  pininfo.board = i;
	  pininfo.boardarray = i - 1;
	  pininfo.pinA = pin;
	  pininfo.pinB = (((8 * (pininfo.boardarray)) - pin) * -1);
	  pininfo.err = false;
	  return pininfo;
	}
  }
  return pininfo;
}
bool 	PCF8574_MULTI::PinIsValid(byte pin) {
  if ((pin < 0) || (pin >PCF8574_MULTI_MAX_PIN)) {
    return false;
  }
  if (pin > this->NumPinsAll()) {
    return false;
  }
  return true;
}



void 	PCF8574_MULTI::pinMode(byte pin, byte mode) {
  if (this->_BEGIN_OK == false ){ return; }
  if (this->PinIsValid(pin) == false) { return; }
  
  if (pin == 0)
  {
    for (byte i = 1; i <= this->NumBoards(); i++){
      this->_PCF8574_DEV[i - 1].pinMode(0, mode);
    }
  }
  else {
	InfoDatosPin pininfo = this->GetInfoPin(pin);
    if (pininfo.err == true) { return PIN_STATUS_ERR; }
    this->_PCF8574_DEV[pininfo.boardarray].pinMode(pininfo.pinB, mode);
  }
}
uint8_t PCF8574_MULTI::pinMode(byte pin) {
  if (this->_BEGIN_OK == false ){ return -1; }
  if (this->PinIsValid(pin) == false) { return -2; }
  
  InfoDatosPin pininfo = this->GetInfoPin(pin);
  if (pininfo.err == true) { return -2; }
  return this->_PCF8574_DEV[pininfo.boardarray].pinMode(pininfo.pinB);
}






/*
 * Method Name  : digitalWrite
 *
 * Synopsis     : bool PCF8574_MULTI::digitalWrite(byte pin, bool newstatus)
 * Arguments    : byte pin : Numero de pin que deseamos cambiar su estado.
 *                bool  newstatus : Nuevo estado del pin.
 *
 * Description  : Reconfiguramos el pin que le pasamos con el valor que le especificamos.
 *                Si usamos el PIN 0, el nuevo valor se configurará en todos los PINES.
 * 
 * Returns      : bool 
 */
bool 	PCF8574_MULTI::digitalWrite(byte pin, byte newstatus) {
  if (this->_BEGIN_OK == false ) { return false; }
  if (this->PinIsValid(pin) == false) { return false; }
  
  if (pin == 0 ) {
    for (byte i = 0; i < this->NumBoards(); i++){
	  if (i == this->NumBoards()) { break; }
	  #ifdef DEBUG
	    Serial.print("Write - Pin 0 - Begin ("); Serial.print(i); Serial.print("): "); Serial.println(this->_PCF8574_DEV[i].isBegin()); 
		Serial.print("Write - Pin 0 - Address ("); Serial.print(i); Serial.print("): "); Serial.print(this->_PCF8574_DEV[i].AddressI2C()); Serial.print(" / "); Serial.println(this->_PCF8574_DEV[i].AddressI2C(), HEX); 
	  #endif
      this->_PCF8574_DEV[i].digitalWrite(0, newstatus);
    }
	return true;
  }
  
  InfoDatosPin pininfo = this->GetInfoPin(pin);
  if (pininfo.err == true) { return PIN_STATUS_ERR; } 
  
  #ifdef DEBUG
    Serial.print("Write - Pin ("); Serial.print(pin); Serial.print(" / "); Serial.print(pininfo.pinB); Serial.print(" - NewStatus: "); Serial.println(newstatus);
    Serial.print("Write - Begin ("); Serial.print(pininfo.boardarray); Serial.print("): "); Serial.println(this->_PCF8574_DEV[pininfo.boardarray].isBegin()); 
	Serial.print("Write - Address ("); Serial.print(pininfo.boardarray); Serial.print("): "); Serial.print(this->_PCF8574_DEV[pininfo.boardarray].AddressI2C()); Serial.print(" / "); Serial.println(this->_PCF8574_DEV[pininfo.boardarray].AddressI2C(), HEX); 
  #endif
  
  return this->_PCF8574_DEV[pininfo.boardarray].digitalWrite(pininfo.pinB, newstatus);
}


/*
 * Method Name  : digitalRead
 *
 * Synopsis     : bool PCF8574_MULTI::digitalRead(byte pin)
 * Arguments    : byte pin : Número del pin que deseamos leer el estado.
 *
 * Description  : Lee el estado del pin que le solicitamos da igual el modo en el que este configurado, siempre se puede leer el estado de cualquier pin.
 * 
 * Returns      : bool 
 *
 * NOTA:
 *   Tener en cuenta que si el valor de pin es superior o inferior a los pones configurados retornara siempre false.
 */
uint8_t PCF8574_MULTI::digitalRead(byte pin) {
  if (this->_BEGIN_OK == false ) { return PIN_STATUS_ERR; }
  if (pin == 0) { return PIN_STATUS_ERR; }
  if (this->PinIsValid(pin) == false) { return PIN_STATUS_ERR; }
  
  InfoDatosPin pininfo = this->GetInfoPin(pin);
  if (pininfo.err == true) { return PIN_STATUS_ERR; } 
  
  #ifdef DEBUG
    Serial.print("Read - Pin ("); Serial.print(pin); Serial.print(" / "); Serial.println(pininfo.pinB);
    Serial.print("Read - Begin ("); Serial.print(pininfo.boardarray); Serial.print("): "); Serial.println(this->_PCF8574_DEV[pininfo.boardarray].isBegin()); 
	Serial.print("Read - Address ("); Serial.print(pininfo.boardarray); Serial.print("): "); Serial.print(this->_PCF8574_DEV[pininfo.boardarray].AddressI2C()); Serial.print(" / "); Serial.println(this->_PCF8574_DEV[pininfo.boardarray].AddressI2C(), HEX); 
  #endif
  
  return this->_PCF8574_DEV[pininfo.boardarray].digitalRead(pininfo.pinB);
}


/*
 * Method Name  : ResetPinStatus
 *
 * Synopsis     : void PCF8574_MULTI::ResetPinStatus()
 * Description  : Pone todos los pines que están en modo OUTPUT en false.
 * 
 */
void 	PCF8574_MULTI::ResetPinStatus() {
  this->digitalWrite(0, false);
}




//TODO: PENDIENTE REVISAR
void 	PCF8574_MULTI::DebugStatusPin(String &sreturnpin) {
  if (this->_BEGIN_OK == true ) {
    for (byte ipin = 1; this->NumPinsAll(); ipin++)
    {
      sreturnpin = sreturnpin + this->digitalRead(ipin);
    }
  }
}