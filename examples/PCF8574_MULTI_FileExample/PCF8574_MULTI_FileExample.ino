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

#include <PCF8574_MULTI.h>

/*
   CREAMOE EL OBJETO Y NO LE PASAMOS NINGUN CANAL.
   POR DEFECTO SE CONFIGURA CON LOS PRIMEROS 8 CANALES.
   ESTO SE PUEDE MODIFICAR EN CUALQUIER MOMENTO.
*/
PCF8574_MULTI PCF8574_MULTI_A();


void setup() {
  Serial.begin(9600);

  /*
     LE DECIMOS QUE USE LOS 14 PRIMEROS CANALES.
  */
  PCF8574_MULTI_A.NumeroCanales(14);


  /*
     AHORA LE DECIMOS QUE EMPIEZE DESDE EL CANAL 5 CON LO QUE
     SE QUDARA CONFIGURADO DEL CANAL 5 AL 14.
  */
  PCF8574_MULTI_A.InitNumeroCanales(5);


  /*
     RESETEAMOS TODOS LOS CANALES QUE ESTAN CONFIGURADOS Y LOS PONEMOS EN FALSE
  */
  PCF8574_MULTI_A.ResetPinStatus();


  /*
     PONEMOS TODOS LOS CANLES CONFIGURADOS EN TRUE.
  */
  PCF8574_MULTI_A.SetPinStatus(0, TRUE);


  /*
     PONEMOS EL PIN 5 Y LUEGO EL 11 EN FALSE
  */
  PCF8574_MULTI_A.SetPinStatus(5, FALSE);
  PCF8574_MULTI_A.SetPinStatus(11, FALSE);


  /*
     LEEMOS EL ESTADO DE LOS PINES 5 Y 7
  */
  bool PIN5 = PCF8574_MULTI_A.ReadPinStatus(5);
  bool PIN7 = PCF8574_MULTI_A.ReadPinStatus(7);
}

void loop() {

  /*
     LEEMOS EL ESTADO DE TODOS LOS PINES
  */
  //lememos el estado de todos los pines.
  String vreturn;
  PCF8574_MULTI_A.DebugStatusPin(vreturn);
  PrintlnSerial(vreturn);
  delay(1000);
}
