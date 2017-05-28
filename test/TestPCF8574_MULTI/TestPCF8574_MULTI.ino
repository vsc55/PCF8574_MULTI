#include <PCF8574_MULTI.h>

PCF8574_MULTI PCF8574_MULTI_A;

void setup() {
  Serial.begin(9600);

  PCF8574_MULTI_A.SetTypeDev(PCF8574_MULTI_TDEV_PCF8574A);
  PCF8574_MULTI_A.SetNumBoars(1);
  PCF8574_MULTI_A.begin();
}

void loop() {

  PCF8574_MULTI_A.pinMode(0, OUTPUT);
  PCF8574_MULTI_A.ResetPinStatus();
  delay(1000);


  Serial.println("TODO ONNNNN");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_ON);
  delay(1000);
  Serial.println("TODO OFFFF");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_OFF);
  delay(2000);
  Serial.println("-----------------------");



  Serial.println("TODO ON");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_ON);

  Serial.println("CHANGE MODE PIN 5,6");
  PCF8574_MULTI_A.pinMode(5, INPUT);
  PCF8574_MULTI_A.pinMode(6, INPUT);

  Serial.println("TODO OFF");
  PCF8574_MULTI_A.SetPinStatus(0, PIN_STATUS_OFF);
  delay(2000);

/*
  String vreturn;
  PCF8574_MULTI_A.DebugStatusPin(vreturn);
  Serial.println(vreturn);
  delay(2000);
  */
  Serial.println("-----------------------");



  for (int ii = 1; ii <= 8; ii++) {
    Serial.print("PIN "); Serial.print(ii); Serial.print(" > ON >");
    PCF8574_MULTI_A.SetPinStatus(ii, PIN_STATUS_ON);
    delay(500);
    Serial.println("OFF");
    PCF8574_MULTI_A.SetPinStatus(ii, PIN_STATUS_OFF);
    delay(1000);
  }
  
}
