#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "espconn.h"
#include "mem.h"
 
static volatile os_timer_t test_timer;
struct espconn user_tcp_conn;
struct _esp_tcp user_tcp;
ip_addr_t tcp_server_ip;
struct ip_info ip;

int len, count;
char buf[32];
uint32 oldip;
uint8 *mac;
 

void ICACHE_FLASH_ATTR
user_tcp_sent_cb(void *arg)
{
	espconn_disconnect(&user_tcp_conn); 
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void ICACHE_FLASH_ATTR
user_tcp_discon_cb(void *arg)
{
	wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void ICACHE_FLASH_ATTR
user_sent_data(struct espconn *pespconn)
{
	espconn_sent(pespconn, buf, len);
 	wifi_set_sleep_type(LIGHT_SLEEP_T);
}
 

void ICACHE_FLASH_ATTR
user_tcp_connect_cb(void *arg)
{
    struct espconn *pespconn = arg;
    /*
    uint32_t keeplive; 

	espconn_set_opt(pespconn, ESPCONN_KEEPALIVE); // enable TCP keep alive

	keeplive = 1800; 
	espconn_set_keepalive(pespconn, ESPCONN_KEEPIDLE, &keeplive); 
	keeplive = 5; 
	espconn_set_keepalive(pespconn, ESPCONN_KEEPINTVL, &keeplive); 
	keeplive = 3; //try times 
	espconn_set_keepalive(pespconn, ESPCONN_KEEPCNT, &keeplive); 
	*/
    //espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	espconn_regist_sentcb(pespconn, user_tcp_sent_cb);
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);
    user_sent_data(pespconn);
}
 

void ICACHE_FLASH_ATTR
user_tcp_recon_cb(void *arg, sint8 err)
{
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void ICACHE_FLASH_ATTR
user_check_ip(void)
{ 
    wifi_get_ip_info(STATION_IF, &ip);
 
    if (wifi_station_get_connect_status() == STATION_GOT_IP && ip.ip.addr != 0 && ip.gw.addr != oldip) 
   	{ 
      	user_tcp_conn.proto.tcp = &user_tcp;
      	user_tcp_conn.type = ESPCONN_TCP;
      	user_tcp_conn.state = ESPCONN_NONE;

 
		const char esp_tcp_server_ip[4] = {192, 168, 0, 150}; 
 
		os_memcpy(user_tcp_conn.proto.tcp->remote_ip, esp_tcp_server_ip, 4);
		user_tcp_conn.proto.tcp->remote_port = 8080;
       	user_tcp_conn.proto.tcp->local_port = espconn_port(); 
       	
       	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
       	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);
 		len = os_sprintf(buf, "5c:cf:7f:93:3c:9c %d.%d.%d.%d", IP2STR(&ip.gw.addr));
		oldip = ip.gw.addr;
		
       	espconn_connect(&user_tcp_conn); 
 
    } 
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void wifi_event_cb(System_Event_t *evt) {
	if (evt->event == EVENT_STAMODE_CONNECTED) {
	    user_tcp_conn.proto.tcp = &user_tcp;
      	user_tcp_conn.type = ESPCONN_TCP;
      	user_tcp_conn.state = ESPCONN_NONE;

 
		const char esp_tcp_server_ip[4] = {192, 168, 0, 150}; 
 
		os_memcpy(user_tcp_conn.proto.tcp->remote_ip, esp_tcp_server_ip, 4);
		user_tcp_conn.proto.tcp->remote_port = 8080;
       	user_tcp_conn.proto.tcp->local_port = espconn_port(); 
       	
       	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
       	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);

		len = os_sprintf(buf, "5c:cf:7f:93:3c:9c %s %s", *mac, evt->event_info.connected.bssid);

		espconn_connect(&user_tcp_conn); 
	}
}
 
void ICACHE_FLASH_ATTR
user_set_station_config(void)
{
	if (!wifi_station_get_auto_connect()) wifi_station_set_auto_connect(1);
   // Wifi configuration 
   char ssid[32] = "Lothlorien"; 
   char password[64] = "JarJarBinks&R2D2"; 
   struct station_config stationConf; 
    
   os_memset(stationConf.ssid, 0, 32);
   os_memset(stationConf.password, 0, 64);
    
   //need not mac address
   stationConf.bssid_set = 0; 
    
   //Set ap settings 
   os_memcpy(&stationConf.ssid, "Lothlorien", 32); 
   os_memcpy(&stationConf.password, "JarJarBinks&R2D2", 64); 
   wifi_station_set_config(&stationConf); 
 
   //set a timer to check whether got ip from router succeed or not.
   os_timer_disarm(&test_timer);
    os_timer_setfn(&test_timer, (os_timer_func_t *)user_check_ip, NULL);
	
	//OLD BEHAVIOR
    //os_timer_arm(&test_timer, 5000, 1); 
	
	//NEW BEHAVIOR
	wifi_set_event_handler_cb(wifi_event_cb);
 
}
 
void user_init(void)
{   
   	wifi_set_opmode(STATION_MODE); 
	wifi_get_macaddr(STATION_IF, mac);
 	
   	user_set_station_config();
   	
   	espconn_init();
}
