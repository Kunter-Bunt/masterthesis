#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "gpio.h"
#include "espconn.h"
	
struct espconn sendResponse;
esp_udp udp;


char buf[256];
int len;

static volatile os_timer_t connect_timer, send_timer;

void scan_done(void *arg, STATUS status)
{
    struct bss_info *bss_link = (struct bss_info *)arg;
    bss_link = bss_link->next.stqe_next;//ignore the first one , it's invalid.

    while (bss_link != NULL)
    {
      if (len < 220) len += os_sprintf(buf+l, " %02x:%02x:%02x:%02x:%02x:%02x %4d;", MAC2STR(bss_link->bssid), bss_link->rssi);
      bss_link = bss_link->next.stqe_next;  
    }
    
    espconn_send(&sendResponse, buf, len);
    //wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void connect(void *arg) {
	wifi_station_connect();
}

void build(void *arg) {
	sendResponse.type = ESPCONN_UDP;
	sendResponse.state = ESPCONN_NONE;
	sendResponse.proto.udp = &udp;
	IP4_ADDR((ip_addr_t *)sendResponse.proto.udp->remote_ip, 192, 168, 0, 150);
	sendResponse.proto.udp->remote_port = 8080; // Remote port
	espconn_create(&sendResponse);
}

void send_UDP(void *arg) {
 	len = 0
	len += += os_sprintf(buf, "5c:cf:7f:c6:a0:f1; ");
	wifi_station_scan(NULL,scan_done);
	//wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void initDone() {
	wifi_set_opmode_current(STATION_MODE);
	struct station_config stationConfig;
	strncpy(stationConfig.ssid, "Lothlorien", 32);
	strncpy(stationConfig.password, "JarJarBinks&R2D2", 64);
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
