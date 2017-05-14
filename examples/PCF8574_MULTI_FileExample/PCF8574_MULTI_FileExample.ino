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
   Creamos el objeto, por defecto se configura para controlar los canales del 1 al 8 y el bus I2C en modo master.
   Podemos configura el objeto para que use determinados canales y la dirección I2C que queramos.

   Ejemplos:
      Objeto por defecto I2C modo Master y canales de 1 al 8.
      PCF8574_MULTI PCF8574_MULTI_A();

      Objeto que le decimos que use los canales de 5 al 11 y el bus I2C en modo Master.
      PCF8574_MULTI PCF8574_MULTI_A(5, 11);

      Objeto que le decimos que use los canales del 5 al 11 y el bus I2C en modo esclavo en la dirección 0x11.
      PCF8574_MULTI PCF8574_MULTI_A(5, 11, 0x11);
*/
PCF8574_MULTI PCF8574_MULTI_A();


void setup() {
  Serial.begin(9600);


  /*
     Configuramos el objeto para que use los 14 primeros canales.
  */
  PCF8574_MULTI_A.NumeroPins(14);


  /*
     Ahora configuramos el objeto parar que comienza desde el canal número 5.
     El objeto se quedaría configurado para que se usen los canales de 5 al 14.
  */
  PCF8574_MULTI_A.InitNumeroPin(5);


  /*
     Reseteamos todos los canales que están configuradas y los ponemos en false.
  */
  PCF8574_MULTI_A.ResetPinStatus();


  /*
     Ponemos todos los canales en modo true.
  */
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_ON);


  /*
     Ponemos los canales 5 y 11 en modo False.
  */
  PCF8574_MULTI_A.SetPinStatus(5, PIN_STATUS_OFF);
  PCF8574_MULTI_A.SetPinStatus(11, PIN_STATUS_OFF);


  /*
     Leemos el estado de los canales 5 y 7.
  */
  bool PIN5 = PCF8574_MULTI_A.ReadPinStatus(5);
  bool PIN7 = PCF8574_MULTI_A.ReadPinStatus(7);
}

void loop() {
  /*
     Leemos el estado de todos los canales configurados y los enviamos al puerto serie en mod binario.
  */
  String vreturn;
  PCF8574_MULTI_A.DebugStatusPin(vreturn);
  Serial.println(vreturn);
  delay(1000);
}
