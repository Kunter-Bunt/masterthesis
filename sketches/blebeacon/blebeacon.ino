#include <bluefruit.h>

void setup() 
{
  Serial.begin(115200);
  Bluefruit.begin();
  Bluefruit.setName("Bluefruit52");
  Bluefruit.stopConnLed();
  //Bluefruit.setTxPower(-4);
  Serial.println(Bluefruit.getTxPower());

  // Setup the advertising packet
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addName();

  // Start advertising
  Bluefruit.Advertising.start();
}

void loop() 
{
}
