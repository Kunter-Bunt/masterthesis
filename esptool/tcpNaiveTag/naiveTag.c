#include "os_type.h" //os_timer_t
#include "osapi.h" //os_timer_setfn, os_timer_arm
#include "user_interface.h" //wifi_send_pkt_freedom
#include "espconn.h"
#include "mem.h"
 
static volatile os_timer_t test_timer, send_timer;
struct espconn user_tcp_conn;
struct _esp_tcp user_tcp;
ip_addr_t tcp_server_ip;
struct ip_info ip;

int len, count;
char buf[32];
uint32 oldip;
 
 

void ICACHE_FLASH_ATTR
user_tcp_sent_cb(void *arg)
{
   //data sent successfully
 
    os_printf("tcp sent succeed !!! \r\n");
    wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void ICACHE_FLASH_ATTR
user_tcp_discon_cb(void *arg)
{
   //tcp disconnect successfully
    //TODO Cut power
    os_printf("tcp disconnect succeed !!! \r\n");
}

void ICACHE_FLASH_ATTR
user_sent_data(struct espconn *pespconn)
{
   	wifi_get_ip_info(STATION_IF, &ip);
 	if (ip.gw.addr != oldip) {
 		len = os_sprintf(buf, "5c:cf:7f:93:3c:9c %d.%d.%d.%d", IP2STR(&ip.gw.addr));
		oldip = ip.gw.addr;
		espconn_sent(pespconn, buf, len);
 	}
}
 

void ICACHE_FLASH_ATTR
user_tcp_connect_cb(void *arg)
{
    struct espconn *pespconn = arg;
 
    os_printf("connect succeed !!! \r\n");
    
    uint32_t keeplive; 

	espconn_set_opt(pespconn, ESPCONN_KEEPALIVE); // enable TCP keep alive

	//set keepalive: 75s = 60 + 5*3 
	keeplive = 600; 
	espconn_set_keepalive(pespconn, ESPCONN_KEEPIDLE, &keeplive); 
	keeplive = 5; 
	espconn_set_keepalive(pespconn, ESPCONN_KEEPINTVL, &keeplive); 
	keeplive = 3; //try times 
	espconn_set_keepalive(pespconn, ESPCONN_KEEPCNT, &keeplive); 

    //espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	espconn_regist_sentcb(pespconn, user_tcp_sent_cb);
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);
    
	os_timer_setfn(&send_timer, (os_timer_func_t *)user_sent_data, pespconn);
  	os_timer_arm(&send_timer, 5000, 1); //timer, milliseconds, repeating
}
 

void ICACHE_FLASH_ATTR
user_tcp_recon_cb(void *arg, sint8 err)
{
   //error occured , tcp connection broke. user can try to reconnect here. 
    //TODO Cut power
    os_printf("reconnect callback, error code %d !!! \r\n",err);
}

void ICACHE_FLASH_ATTR
user_check_ip(void)
{ 
   //disarm timer first
    os_timer_disarm(&test_timer);
 
   //get ip info of ESP8266 station
    wifi_get_ip_info(STATION_IF, &ip);
 
    if (wifi_station_get_connect_status() == STATION_GOT_IP && ip.ip.addr != 0) 
   {
      os_printf("got ip !!! \r\n");
 
      // Connect to tcp server as NET_DOMAIN
      user_tcp_conn.proto.tcp = &user_tcp;
      user_tcp_conn.type = ESPCONN_TCP;
      user_tcp_conn.state = ESPCONN_NONE;
/*       
#ifdef DNS_ENABLE
      tcp_server_ip.addr = 0;
       espconn_gethostbyname(&user_tcp_conn, NET_DOMAIN, &tcp_server_ip, user_dns_found); // DNS function
 
       os_timer_setfn(&test_timer, (os_timer_func_t *)user_dns_check_cb, &user_tcp_conn);
       os_timer_arm(&test_timer, 1000, 0);
#else*/
 
		const char esp_tcp_server_ip[4] = {192, 168, 0, 150}; 
 
		os_memcpy(user_tcp_conn.proto.tcp->remote_ip, esp_tcp_server_ip, 4);
		user_tcp_conn.proto.tcp->remote_port = 8080;
       	user_tcp_conn.proto.tcp->local_port = espconn_port(); 
       	
       	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb); // register connect callback
       	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb); // register reconnect callback as error handler
       espconn_connect(&user_tcp_conn); 
 
//#endif
    } 
   else
   {
        
        if ((wifi_station_get_connect_status() == STATION_WRONG_PASSWORD ||
                wifi_station_get_connect_status() == STATION_NO_AP_FOUND ||
                wifi_station_get_connect_status() == STATION_CONNECT_FAIL)) 
        {
         os_printf("connect fail !!! \r\n");
         //TODO Cut power
        } 
      else
      {
           //re-arm timer to check ip
            os_timer_setfn(&test_timer, (os_timer_func_t *)user_check_ip, NULL);
            os_timer_arm(&test_timer, 100, 0);
        }
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
    os_timer_arm(&test_timer, 100, 0);
 
}
 
void user_init(void)
{
    os_printf("SDK version:%s\n", system_get_sdk_version());
    
   //Set softAP + station mode 
   wifi_set_opmode(STATIONAP_MODE); 
 
   //ESP8266 connect to router
   user_set_station_config();
   
   espconn_init();
 
}

/*
 
#ifdef DNS_ENABLE
void ICACHE_FLASH_ATTR
user_dns_found(const char *name, ip_addr_t *ipaddr, void *arg)
{
    struct espconn *pespconn = (struct espconn *)arg;
 
    if (ipaddr == NULL) 
   {
        os_printf("user_dns_found NULL \r\n");
        return;
    }
 
   //dns got ip
    os_printf("user_dns_found %d.%d.%d.%d \r\n",
            *((uint8 *)&ipaddr->addr), *((uint8 *)&ipaddr->addr + 1),
            *((uint8 *)&ipaddr->addr + 2), *((uint8 *)&ipaddr->addr + 3));
 
    if (tcp_server_ip.addr == 0 && ipaddr->addr != 0) 
   {
      // dns succeed, create tcp connection
        os_timer_disarm(&test_timer);
        tcp_server_ip.addr = ipaddr->addr;
        os_memcpy(pespconn->proto.tcp->remote_ip, &ipaddr->addr, 4); // remote ip of tcp server which get by dns
 
        pespconn->proto.tcp->remote_port = 80; // remote port of tcp server
       
        pespconn->proto.tcp->local_port = espconn_port(); //local port of ESP8266
 
        espconn_regist_connectcb(pespconn, user_tcp_connect_cb); // register connect callback
        espconn_regist_reconcb(pespconn, user_tcp_recon_cb); // register reconnect callback as error handler
 
        espconn_connect(pespconn); // tcp connect
    }
}
 

void ICACHE_FLASH_ATTR
user_dns_check_cb(void *arg)
{
    struct espconn *pespconn = arg;
 
    espconn_gethostbyname(pespconn, NET_DOMAIN, &tcp_server_ip, user_dns_found); // recall DNS function
 
    os_timer_arm(&test_timer, 1000, 0);
}
#endif
*/
