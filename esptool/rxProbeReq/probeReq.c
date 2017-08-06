#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom, deep_sleep, promiscous commands
#include "gpio.h" //peripheries, gpio_init

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


static volatile os_timer_t start_promisc_timer, send_sleep_timer;
uint8 voltage;

void send_sleep(void *arg)
{
		wifi_send_pkt_freedom(packet, 26, 0);
		system_deep_sleep(5000000);
}

void sleep(void *arg)
{
		system_deep_sleep(5000000);
}

void promisc_cb(uint8_t *buf, uint16_t len)
{
	//if (buf[0] == 0x80) {
	if (len == 128){
		//wifi_promiscuous_enable(0);
		//send_sleep(NULL);	
    }
}

void start_promisc(void *arg)
{
	wifi_set_channel(1);
	wifi_set_promiscuous_rx_cb(promisc_cb);
  	wifi_promiscuous_enable(1);
	wifi_set_opmode(STATION_MODE);
}



void ICACHE_FLASH_ATTR user_init()
{
	gpio_init();

	wifi_station_set_auto_connect(0); //needed for promisc to work

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U , FUNC_GPIO15);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	GPIO_DIS_OUTPUT(BIT15);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDO_U); 
	
	if (!GPIO_INPUT_GET(15)) GPIO_OUTPUT_SET(13, 1);
	
	voltage = system_adc_read() / 10;

  	os_timer_setfn(&start_promisc_timer, (os_timer_func_t *)start_promisc, NULL);
  	os_timer_arm(&start_promisc_timer, 0, 0); //timer, milliseconds, repeating

	os_timer_setfn(&send_sleep_timer, (os_timer_func_t *)sleep, NULL);
  	os_timer_arm(&send_sleep_timer, 600, 0); //timer, milliseconds, repeating
}
