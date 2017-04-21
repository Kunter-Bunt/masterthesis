
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



const char* ssid     = "PhD. Sheldon Cooper";
const char* password = "XCV,234,xcv";

const char* host = "192.168.178.20";
const int port = 8080;
WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
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
    
    String str = "5c:cf:7f:c6:a0:f1 " + String(WiFi.gatewayIP()[0]) + "." + String(WiFi.gatewayIP()[1]) + "." + String(WiFi.gatewayIP()[2]) + "." + String(WiFi.gatewayIP()[3]) + " " + String(WiFi.RSSI());
    Udp.write(str.c_str(), str.length()); 
    
    Udp.endPacket();

    delay(5000);

}
    //Test connection
    //WiFiClient client;
    //if (!client.connect(host, port)) return;
    //client.println("GET / HTTP/1.1");
    //Serial.println(WiFi.gatewayIP());


    //Send as bytes instead
    //byte buffer[10] = {0x5c, 0xcf, 0x7f, 0xc6, 0xa0, 0xf1};
    //byte gateip[] = {WiFi.gatewayIP()};
    //memcpy(buffer+6, gateip, 4);
    //Udp.write(buffer, 10);
