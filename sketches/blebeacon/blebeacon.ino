#include <bluefruit.h>


void setup() 
{
  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  Bluefruit.setName("TestTag");
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.start();
}

void loop() 
{
}
