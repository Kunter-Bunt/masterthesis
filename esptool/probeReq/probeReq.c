#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "gpio.h"
//#include "eagle_soc.h"

// ProbeRequest Packet buffer - shortest possible version (sender sided)
uint8_t packet[26] = { 
				/*0*/ 	0x40, //Version (2bit), Type (2bit), Subtype(4bit)
				/*1*/ 	0x00, //Flags 
				/*2*/ 	0x00, 0x00, //Duration
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //destination MAC
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, //source MAC
                /*16*/  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //BSSID all ff is Broadcast
                /*22*/  0x00, 0x00, //Sequence Number (12bit), Fragment Number (4bit) [Hier endet probe request]
	            /*24*/  0x83, //Tag Number (Path Reply 131) [Ab hier managemant tags]
                /*25*/ 	0x00, //Tag length
};              


static volatile os_timer_t some_timer;
uint8 voltage;

void some_timerfunc(void *arg)
{
	wifi_send_pkt_freedom(packet, 26, 0);
	system_deep_sleep(5000000);
	//wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void ICACHE_FLASH_ATTR user_init()
{
	gpio_init();

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U , FUNC_GPIO15);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	GPIO_DIS_OUTPUT(BIT13);
	
	if (!GPIO_INPUT_GET(13)) GPIO_OUTPUT_SET(15, 1);
	
	voltage = system_adc_read() / 10;

  os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
  os_timer_arm(&some_timer, 0, 0); //timer, milliseconds, repeating
}
