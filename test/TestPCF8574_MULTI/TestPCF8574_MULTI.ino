#include <PCF8574_MULTI.h>

PCF8574_MULTI PCF8574_MULTI_A;

void setup() {
  Serial.begin(9600);

  PCF8574_MULTI_A.SetTypeDev(PCF8574_MULTI_TDEV_PCF8574A);
  PCF8574_MULTI_A.begin();
  
  PCF8574_MULTI_A.ResetPinStatus();
}

void loop() {

  PCF8574_MULTI_A.PinIni(1);
  PCF8574_MULTI_A.PinEnd(8);
  PCF8574_MULTI_A.ResetPinStatus();
  delay(1000);


  Serial.println("TODO ONNNNN");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_ON);
  delay(1000);
  Serial.println("TODO OFFFF");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_OFF);
  delay(1000);
  Serial.println("-----------------------");

  Serial.println("TODO ON");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_ON);
  Serial.println("CHANGE PIN");
  PCF8574_MULTI_A.Pins(2,5);
  Serial.println("TODO OFF");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_OFF);
  delay(1000);

  String vreturn;
  PCF8574_MULTI_A.DebugStatusPin(vreturn);
  Serial.println(vreturn);
  delay(5000);






  Serial.print("PIN 1 > ON >");
  PCF8574_MULTI_A.SetPinStatus(1, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(1, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 2 > ON >");
  PCF8574_MULTI_A.SetPinStatus(2, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(2, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 3 > ON >");
  PCF8574_MULTI_A.SetPinStatus(3, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(3, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 4 > ON >");
  PCF8574_MULTI_A.SetPinStatus(4, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(4, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 5 > ON >");
  PCF8574_MULTI_A.SetPinStatus(5, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(5, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 6 > ON >");
  PCF8574_MULTI_A.SetPinStatus(6, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(6, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 7 > ON >");
  PCF8574_MULTI_A.SetPinStatus(7, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(7, PIN_STATUS_OFF);
  delay(1000);



  Serial.print("PIN 8 > ON >");
  PCF8574_MULTI_A.SetPinStatus(8, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  PCF8574_MULTI_A.SetPinStatus(8, PIN_STATUS_OFF);
  delay(1000);

}
