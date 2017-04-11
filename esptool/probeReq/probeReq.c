#include "ets_sys.h"
#include "os_type.h"
#include "osapi.h"
#include "mem.h"
#include "user_interface.h"
#include "gpio.h"

// ProbeRequest Packet buffer
uint8_t packet[128] = { 
				/*0*/ 	0x40, //Version (2bit), Type (2bit), Subtype(4bit)
				/*1*/ 	0x00, //Flags 
				/*2*/ 	0x00, 0x00, //Duration
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //destination MAC
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //source MAC
                /*16*/  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //BSSID all ff is Broadcast
                /*22*/  0xc0, 0x6c, //Sequence Number (12bit), Fragment Number (4bit) [Hier endet probe request]
                /*24*/  0x83, //Tag Number (Path Reply 131) [Ab hier managemant tags]
                /*25*/ 	0x21, //Tag length
                /*26*/ 	0xf7, //HWMP flags
                /*27*/ 	0x8f, //HWMP Hop Count
                /*28*/ 	0x0f, //HWMP TTL
                /*29*/ 	0x00, 0x00, 0x00, 0x64, 0x00, 0x01, //Target STA Address
                /*35*/  0x04, 0x00, 0x06, 0x72, //Target HWMP Sequence Number
                /*39*/ 	0x72, 0x72, 0x72, 0x72, 0x72, 0x01, //Target External Address
                /*45*/ 	0x08, 0x82, 0x84, 0x8b, //HWMP Lifetime
                /*49*/ 	0x96, 0x24, 0x30, 0x48, //HWMP Metric
                /*54*/ 	0x6c, 0x03, 0x01, //Listet Wireshark nicht!
                /*57*/  0x01};     //channel                  


static volatile os_timer_t some_timer;

void some_timerfunc(void *arg)
{
	wifi_send_pkt_freedom(packet, 57, 0);
	system_deep_sleep(5000000);
	//wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void ICACHE_FLASH_ATTR user_init()
{
  os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
  os_timer_arm(&some_timer, 0, 0); //timer, milliseconds, repeating
}
