#include <ESP8266WiFi.h>
void setup() {
  //WiFi.scanNetworks(async, show_hidden);
  WiFi.scanNetworks(false, false);
  ESP.deepSleep(5 * 1000000);
}

void loop() {
}
