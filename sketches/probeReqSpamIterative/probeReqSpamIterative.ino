#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

byte channel;

// Beacon Packet buffer
uint8_t packet[128] = { 0x40, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                /*22*/  0xc0, 0x6c, 
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32*/  0x64, 0x00, 
                /*34*/  0x01, 0x04, 
                /* SSID */
                /*36*/  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /*56*/  0x04};                       


void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
}



void loop() {
    if (channel < 12) channel++;
    else channel = 1;
    wifi_set_channel(channel);  
    packet[56] = channel;
    
    wifi_send_pkt_freedom(packet, 57, 0);
    wifi_send_pkt_freedom(packet, 57, 0);
    wifi_send_pkt_freedom(packet, 57, 0);
    delay(1);
}

