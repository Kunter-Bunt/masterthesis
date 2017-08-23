#include <SPI.h>
#include <RH_RF95.h>
#include "ArduinoLowPower.h"

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

#define RF95_FREQ 868.0

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  
  rf95.init();
  rf95.setFrequency(RF95_FREQ);
  rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);
  rf95.setTxPower(5, false);

}

void loop() {
  char radiopacket[8] = "123456 ";
  radiopacket[6] = 0;

  rf95.send((uint8_t *)radiopacket, 8);
  delay(10);
  rf95.waitPacketSent();
  
  LowPower.sleep(10000);
  //delay(10000);
}

