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
   Creamos el objeto.
   Por defecto se configura para controlar el modelo PCF8574A, de los pines 1 al 8 y el bus I2C en modo master.
   Podemos configura el objeto para que use los pines que nosotros queramos y la dirección I2C que nos necesitemos.

   Ejemplos:
      Objeto por defecto I2C modo Master, pines del 1 al 8 y el modelo PCF8574A.
      PCF8574_MULTI PCF8574_MULTI_A();

      Objeto que le especificamos el modelo PCF8574A, que use los pines del 5 al 11 y el bus I2C en modo Master.
      PCF8574_MULTI PCF8574_MULTI_A(5, 11);

      NOTA I2C: Si se ha ejecutado “Wire.Begin” antes no hará caso al valor que le hemos configurado.
*/
PCF8574_MULTI PCF8574_MULTI_A;


void setup() {
  Serial.begin(9600);


  /*
     Configuramos el tipo de chip que vamos a usar para obtener las direcciones I2C correctas.
  */
  PCF8574_MULTI_A.SetTypeDev(PCF8574_MULTI_TDEV_PCF8574A);


  /*
     Configuramos para usar los pines del 1 al 8.
  */
  PCF8574_MULTI_A.Pins(1, 8);
  Serial.println("Pins... End!");

  /*
     Iniciamos el objeto.
     NOTA: Si vamos a usar el bus I2C en modo esclavo tendremos que configura la dirección Wire antes de ejecutar Begin().
     NOTA: Si se ha ejecutado antes en algún sitio Wire.Begin(), se usarán los datos que se hayan ejecutando antes, y la dirección Wire que tengamos configurado en el objeto no tendrá efecto.
  */
  PCF8574_MULTI_A.begin();
  Serial.println("Begin... End!");


  /*
     Configuramos el tipo de pin si es IN o OUT.
     NOTE: Todos los pines por defecto están configurados en modo IN.
  */
  PCF8574_MULTI_A.pinMode(1, OUTPUT);
  PCF8574_MULTI_A.pinMode(2, OUTPUT);
  PCF8574_MULTI_A.pinMode(3, OUTPUT);
  PCF8574_MULTI_A.pinMode(4, OUTPUT);
  PCF8574_MULTI_A.pinMode(5, OUTPUT);
  PCF8574_MULTI_A.pinMode(6, OUTPUT);
  Serial.println("PinMode... End!");


  /*
     Configuramos el objeto para que use hasta el pin 14.
  */
  PCF8574_MULTI_A.PinEnd(14);
  Serial.println("Pin14... End!");
  


  /*
    Ahora configuramos el objeto parar que comienza desde el pin número 5.
    El objeto se quedaría configurado para que se usen los pines del 5 al 14.
  */
  PCF8574_MULTI_A.PinIni(5);
  Serial.println("Pin5... End!");


  /*
     Reseteamos todos los canales que están configuradas y los ponemos en false.
  */
  PCF8574_MULTI_A.ResetPinStatus();
  Serial.println("ResetPinStatus... End!");
  delay(1000);

  /*
     Ponemos todos los pines en modo true. Solo afectara al rango que tengamos
     configurado en este caso del 5 al 14.
  */
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_ON);
  Serial.println("Todo ON!");
  delay(1000);


  /*
     Ponemos los pines 5 y 11 en modo False. Intentamos también hacerlo al pin 2
     pero no hace efecto ya que esta fuera del intervalo de pines que tenemos
     configurados.
  */
  PCF8574_MULTI_A.SetPinStatus(5, PIN_STATUS_OFF);
  PCF8574_MULTI_A.SetPinStatus(11, PIN_STATUS_OFF);
  PCF8574_MULTI_A.SetPinStatus(2, PIN_STATUS_OFF);
  Serial.println("OFF 5, 11, 2!");
  delay(1000);


  /*
     Leemos el estado de los pines 5 y 7.
     También leeremos el pin 2. Esta opción sí que está disponible siempre. Podremos
     leer el estado de cualquier pin, pero no podremos modificar su estado.
  */
  int ValPIN2 = PCF8574_MULTI_A.ReadPinStatus(2);
  int ValPIN5 = PCF8574_MULTI_A.ReadPinStatus(5);
  int ValPIN7 = PCF8574_MULTI_A.ReadPinStatus(7);
  Serial.println("READ STATUS:");
  Serial.print("PIN2:"); Serial.println(ValPIN2);
  Serial.print("PIN5:"); Serial.println(ValPIN5);
  Serial.print("PIN7:"); Serial.println(ValPIN7);
  delay(1000);

  /*
    Podremos cambien los pines que controlamos en cualquier momento, para modificar
    a la vez el pin inicial y el final podremos usar la siguiente función.
    Ahora configuramos el objeto para que controle de los pines 4 al 12.
  */
  PCF8574_MULTI_A.Pins(4, 12);
  Serial.println("PINS 4,12!");
  delay(1000);
}

void loop() {
  /*
     Leemos el estado de todos los pines configurados y los enviamos al puerto serie
     en modo binario. 0 false, 1 true.
     Tal como lo hemos dejado configurado antes leeremos el estado de los pines
     del 4 al 12.
  */
  String vreturn;
  PCF8574_MULTI_A.DebugStatusPin(vreturn);
  Serial.print("DATOS:");
  Serial.println(vreturn);
  delay(1000);
}
