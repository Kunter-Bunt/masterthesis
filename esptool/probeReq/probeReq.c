#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
//#include "gpio.h"
       

//Oneplus frame
uint8_t packet[89] = { 
				/*0*/ 	0x40, //Version (2bit), Type (2bit), Subtype(4bit)
				/*1*/ 	0x00, //Flags 
				/*2*/ 	0x00, 0x00, //Duration
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //destination MAC
                /*10*/  0x5c, 0xcf, 0x7f, 0xf0, 0xab, 0x75, //source MAC
                /*16*/  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, //BSSID all ff is Broadcast
                /*22*/  0x00, 0x00, //Sequence Number (12bit), Fragment Number (4bit) [Hier endet probe request]
	            /*24*/  0x00, //Tag Number (Path Reply 131) [Ab hier managemant tags]
                /*25*/ 	0x00, //Tag length
				0x01, 0x04, 0x02, 0x04, 0x0b, 0x16, 0x32, 0x08,
				0x0c, 0x12, 0x18, 0x24, 0x30, 0x48, 0x60, 0x6c, 0x03, 0x01,
 				0x01, 0x2d, 0x1a, 0x2c, 0x01, 0x03,
				0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0x07, 0x00, 
				0x50, 0xf2, 0x08, 0x00, 0x00, 0x00,
				0x7f, 0x05, 0x00, 0x00, 0x0a, 0x02, 0x01,
};


static volatile os_timer_t some_timer;
uint8 voltage;

void some_timerfunc(void *arg)
{
	wifi_send_pkt_freedom(packet, 89, 0);
	/*wifi_set_channel(6);
	wifi_send_pkt_freedom(packet, 26, 0);
	wifi_set_channel(11);
	wifi_send_pkt_freedom(packet, 26, 0);*/
	system_deep_sleep(5000000);
}

void ICACHE_FLASH_ATTR user_init()
{
	//wifi_station_set_auto_connect(0);
	//gpio_init();
	//wifi_set_channel(1);

	/*PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U  , FUNC_GPIO0);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U , FUNC_GPIO15);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	GPIO_DIS_OUTPUT(BIT15);*/
	//PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDO_U); 
	
	//if (!GPIO_INPUT_GET(15)) GPIO_OUTPUT_SET(13, 1);
	
	//voltage = system_adc_read() / 10;
	
  	os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
  	os_timer_arm(&some_timer, 0, 0); //timer, milliseconds, repeating
}
