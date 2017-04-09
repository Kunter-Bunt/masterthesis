#include "ets_sys.h"
#include "os_type.h"
#include "user_interface.h"

// ProbeRequest Packet buffer
uint8_t packet[128] = { 0x40, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //destination MAC
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //source MAC
                /*16*/  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //BSSID all ff is Broadcast
                /*22*/  0xc0, 0x6c, 
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32*/  0x64, 0x00, 
                /*34*/  0x01, 0x04, 
                /*36*/  0x00, 0x06, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, //SSID
                /*44*/  0x01, 0x08, 0x82, 0x84,
                /*48*/  0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /*56*/  0x01};     //channel                  


void ICACHE_FLASH_ATTR user_init()
{
	wifi_send_pkt_freedom(packet, 57, 0);
  	system_deep_sleep(5000000);
}
