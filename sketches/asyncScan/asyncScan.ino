#include <ESP8266WiFi.h>
void setup() {
  //WiFi.scanNetworks(async, show_hidden);
  WiFi.scanNetworks(true, false);
  ESP.deepSleep(5 * 1000000);
}

void loop() {
}
