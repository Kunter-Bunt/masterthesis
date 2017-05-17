#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "gpio.h"
#include "espconn.h"
	
struct espconn sendResponse;
esp_udp udp;
	sint8 err;
static volatile os_timer_t connect_timer, send_timer;

void connect(void *arg) {
	wifi_station_connect();
	//if (wifi_station_connect())
		//gpio_output_set((1 << 4), 0, 0, 0);
	//wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void send_UDP(void *arg) {
	sendResponse.type = ESPCONN_UDP;
	sendResponse.state = ESPCONN_NONE;
	sendResponse.proto.udp = &udp;
	IP4_ADDR((ip_addr_t *)sendResponse.proto.udp->remote_ip, 192, 168, 0, 150);
	sendResponse.proto.udp->remote_port = 8080; // Remote port
	err = espconn_create(&sendResponse);
	err = espconn_send(&sendResponse, "123456", 6);
	err = espconn_delete(&sendResponse);
}

void initDone() {
	wifi_set_opmode_current(STATION_MODE);
	struct station_config stationConfig;
	strncpy(stationConfig.ssid, "Lothlorien", 32);
	strncpy(stationConfig.password, "JarJarBinks&R2D2", 64);
	wifi_station_set_config(&stationConfig);
}

void ICACHE_FLASH_ATTR user_init() {
	/*
	gpio_init();
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U, FUNC_GPIO1); 
  	gpio_output_set(0, 0, (1 << 4), 0);
  	*/
  	initDone();
	
  	os_timer_setfn(&connect_timer, (os_timer_func_t *)connect, NULL);
  	os_timer_arm(&connect_timer, 10, 0); //timer, milliseconds, repeating
  	
  	os_timer_setfn(&send_timer, (os_timer_func_t *)send_UDP, NULL);
  	os_timer_arm(&send_timer, 250, 1); //timer, milliseconds, repeating
}
