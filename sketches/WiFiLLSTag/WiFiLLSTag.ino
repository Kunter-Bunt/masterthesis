#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


extern "C" {
  #include "user_interface.h"
  bool wifi_set_sleep_type(sleep_type_t);
}

const char* ssid     = "Lothlorien";
const char* password = "JarJarBinks&R2D2";

char buf[256];
int l;

WiFiUDP Udp;

void scan_done(void *arg, STATUS status)
{
    struct bss_info *bss_link = (struct bss_info *)arg;
    bss_link = bss_link->next.stqe_next;//ignore the first one , it's invalid.

    while (bss_link != NULL)
    {
      if (l < 220) l += os_sprintf(buf+l, " %02x:%02x:%02x:%02x:%02x:%02x %4d;", MAC2STR(bss_link->bssid), bss_link->rssi);
      bss_link = bss_link->next.stqe_next;  
    }
    
    Udp.beginPacket("192.168.0.150", 8080);
    Udp.write(buf, l); 
    Udp.endPacket();
    
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

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
    Serial.println(buf);
    l = 0;
    l += os_sprintf(buf, "5c:cf:7f:c6:a0:f1; ");
    
    wifi_station_scan(NULL,scan_done);
    
    wifi_set_sleep_type(LIGHT_SLEEP_T);
    delay(5000);
}
