#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "espconn.h" //udp stuff
	
struct espconn sendResponse;
esp_udp udp;
sint8 err;
static volatile os_timer_t connect_timer, build_timer, send_timer;


void connect(void *arg) {
	wifi_station_connect();
}



void build(void *arg) {
	sendResponse.type = ESPCONN_UDP;
	sendResponse.state = ESPCONN_NONE;
	sendResponse.proto.udp = &udp;
	IP4_ADDR((ip_addr_t *)sendResponse.proto.udp->remote_ip, 192, 168, 0, 150);
	sendResponse.proto.udp->remote_port = 8080; // Remote port
	err = espconn_create(&sendResponse);
}

void ICACHE_FLASH_ATTR send_UDP(void *arg) {
	err = espconn_send(&sendResponse, "123456", 6);
	wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void initDone() {
	wifi_set_opmode_current(STATION_MODE);
	struct station_config stationConfig;
	strncpy(stationConfig.ssid, "WIFI_TAG_TESTING", 32);
	strncpy(stationConfig.password, "key4WIFI!", 64);
	wifi_station_set_config(&stationConfig);
}

void ICACHE_FLASH_ATTR user_init() {
  	initDone();
	
  	os_timer_setfn(&connect_timer, (os_timer_func_t *)connect, NULL);
  	os_timer_arm(&connect_timer, 10, 0); //timer, milliseconds, repeating
  	
  	os_timer_setfn(&build_timer, (os_timer_func_t *)build, NULL);
  	os_timer_arm(&build_timer, 100, 0); //timer, milliseconds, repeating
  	
  	os_timer_setfn(&send_timer, (os_timer_func_t *)send_UDP, NULL);
  	os_timer_arm(&send_timer, 5000, 1); //timer, milliseconds, repeating
}
