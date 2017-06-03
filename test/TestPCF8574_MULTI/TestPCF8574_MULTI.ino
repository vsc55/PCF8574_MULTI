#include <PCF8574_MULTI.h>

PCF8574_MULTI PCF8574_MULTI_A;

void setup() {
  Serial.begin(9600);

  PCF8574_MULTI_A.TypeDev(PCF8574_MULTI_TDEV_PCF8574A);
  PCF8574_MULTI_A.NumBoars(1);
  PCF8574_MULTI_A.begin();
}

void loop() {

  PCF8574_MULTI_A.pinMode(0, OUTPUT);
  PCF8574_MULTI_A.ResetPinStatus();
  delay(1000);


  Serial.println("TODO ONNNNN");
  PCF8574_MULTI_A.digitalWrite(0, PIN_STATUS_ON);
  delay(1000);
  Serial.println("TODO OFFFF");
  PCF8574_MULTI_A.digitalWrite(0, PIN_STATUS_OFF);
  delay(2000);
  Serial.println("-----------------------");



  Serial.println("TODO ON");
  PCF8574_MULTI_A.digitalWrite(0, PIN_STATUS_ON);

  Serial.println("CHANGE MODE PIN 5,6");
  PCF8574_MULTI_A.pinMode(5, INPUT);
  PCF8574_MULTI_A.pinMode(6, INPUT);

  Serial.println("TODO OFF");
  PCF8574_MULTI_A.digitalWrite(0, PIN_STATUS_OFF);
  delay(2000);
  Serial.println("-----------------------|");


  Serial.print("Num Boards:");
  Serial.println(PCF8574_MULTI_A.NumBoars());
  delay(500);


  byte numPinAll = PCF8574_MULTI_A.NumPinsAll();
  Serial.print("Num Pin All:");
  Serial.println(numPinAll);
  Serial.println("-----------------------|");
  delay(500);


  String sStatus = "";
  for (byte ii = 1; ii <= numPinAll; ii++) {
    Serial.print("PIN "); Serial.println(ii);
    
    Serial.println("    > ON");
    PCF8574_MULTI_A.digitalWrite(ii, PIN_STATUS_ON);
    delay(500);

    //PCF8574_MULTI_A.DebugStatusPin(vreturn);
    //Serial.print("DATOS ON:"); Serial.println(vreturn);
    //sStatus = "";

    delay(500);
    Serial.println("    > OFF");
    PCF8574_MULTI_A.digitalWrite(ii, PIN_STATUS_OFF);
    delay(500);
 
    //PCF8574_MULTI_A.DebugStatusPin(vreturn);
    //Serial.print("DATOS OFF:"); Serial.println(vreturn);
    //sStatus = "";

    Serial.println("-----------------------|");
    delay(1000);
  }
  
  delay(1000);
}
