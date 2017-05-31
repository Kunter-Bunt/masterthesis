
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
extern "C" {
#include "user_interface.h"
  bool wifi_set_sleep_type(sleep_type_t);
}


const char* ssid     = "Lothlorien";
const char* password = "JarJarBinks&R2D2";

const char* host = "192.168.0.150";
const int port = 8080;
WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Access Point: ");
  Serial.println(WiFi.gatewayIP());
}

void loop() {
    Udp.beginPacket(host, port);
    
    String str = "5c:cf:";//7f:c6:a0:f1 " + String(WiFi.gatewayIP()[0]) + "." + String(WiFi.gatewayIP()[1]) + "." + String(WiFi.gatewayIP()[2]) + "." + String(WiFi.gatewayIP()[3]);// + " " + String(WiFi.RSSI());
    Udp.write(str.c_str(), str.length()); 
    
    Udp.endPacket();
    //wifi_set_sleep_type(LIGHT_SLEEP_T);
    delay(5000);
}

