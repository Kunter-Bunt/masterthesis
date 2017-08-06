#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "espconn.h" //udp stuff
	
struct espconn sendResponse;
esp_udp udp;

struct ip_info ip;
static volatile os_timer_t connect_timer, build_timer, send_timer;
uint8 len;
char buf[17];
uint32 oldip;


void connect(void *arg) {
	wifi_station_connect();
}

void build(void *arg) {
	sendResponse.type = ESPCONN_UDP;
	sendResponse.state = ESPCONN_NONE;
	sendResponse.proto.udp = &udp;
	IP4_ADDR((ip_addr_t *)sendResponse.proto.udp->remote_ip, 10, 253, 23, 75);
	sendResponse.proto.udp->remote_port = 8080; // Remote port
	espconn_create(&sendResponse);
}

void send_UDP(void *arg) {
 	wifi_get_ip_info(STATION_IF, &ip);	
 	//if (ip.gw.addr != oldip) {
 		len = os_sprintf(buf, "%d.%d.%d.%d", IP2STR(&ip.gw.addr));
		oldip = ip.gw.addr;
		espconn_send(&sendResponse, buf, len);
	//}
	wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void initDone() {
	//wifi_set_opmode_current(STATION_MODE);
	//if (!wifi_station_get_auto_connect()) wifi_station_set_auto_connect(1);
	struct station_config stationConfig;
	strncpy(stationConfig.ssid, "VCC-Mobile", 32);
	strncpy(stationConfig.password, "VcM0b1L3n3T", 64);
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
