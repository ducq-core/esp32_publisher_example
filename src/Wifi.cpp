#include <Arduino.h>

#include <esp_event.h>
#include <esp_wifi.h>

#include "Wifi.hpp"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
static EventGroupHandle_t s_wifi_event_group;


u32_t ip = 0;
char ipstr[16] = "";

// forward declardation
esp_err_t event_handler(void *ctx, system_event_t *event);



Wifi::Wifi(const char *ssid, const char *password) :
	ssid(ssid),
	password(password)
{ }


const char *Wifi::getIp() {
	snprintf(ipstr, 16, "%d.%d.%d.%d",
		ip >>  0 & 0xff,
		ip >>  8 & 0xff,
		ip >> 16 & 0xff,
		ip >> 24 & 0xff
	);
	return ipstr;
}
bool Wifi::init() {
	s_wifi_event_group = xEventGroupCreate();

	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, this));
	// esp_event_handler_instance_t instance_any_id;
	// esp_event_handler_instance_t instance_got_ip;
	// ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
	// 																										ESP_EVENT_ANY_ID,
	// 																										&event_handler,
	// 																										NULL,
	// 																										&instance_any_id));
	// ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
	// 																										IP_EVENT_STA_GOT_IP,
	// 																										&event_handler,
	// 																										NULL,
	// 																										&instance_got_ip));
	
	Serial.println("wifi initialization... ");
	wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&config));
	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );

	wifi_config_t conf = {};
	memcpy(conf.sta.ssid,     ssid,     32);
	memcpy(conf.sta.password, password, 64);
	conf.sta.bssid_set = false;
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &conf));

	tcpip_adapter_init();
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_connect());

	Serial.println("waiting for initialization... ");
	EventBits_t bits = xEventGroupWaitBits(
		s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
		pdFALSE, pdFALSE,
		portMAX_DELAY
	);

	if(bits & WIFI_CONNECTED_BIT) {
		Serial.println("wifi connected.");
		return true;
	} 
	else if(bits & WIFI_FAIL_BIT) {
		Serial.println("wifi failed to connected.");
		return false;
	}
	else {
		Serial.println("wifi unexpecterd event.");
		return false;
	}

}




esp_err_t event_handler(void *ctx, system_event_t *event)
{
	switch(event->event_id) {
		case SYSTEM_EVENT_WIFI_READY:
			Serial.println("ESP32 WiFi ready");
			break;

		case SYSTEM_EVENT_SCAN_DONE:
			Serial.println("ESP32 finish scanning AP");
			break;

		case SYSTEM_EVENT_STA_START:
			Serial.println("ESP32 station start");
			break;

		case SYSTEM_EVENT_STA_STOP:
			Serial.println("ESP32 station stop");
			break;

		case SYSTEM_EVENT_STA_CONNECTED:
			Serial.println("ESP32 station connected to AP");
			break;

		case SYSTEM_EVENT_STA_DISCONNECTED:
			Serial.println("ESP32 station disconnected from AP");
			Serial.printf("reason: %d\n",event->event_info.disconnected.reason);
			delay(10000);
			esp_restart();
			break;

		case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
			Serial.println("the auth mode of AP connected by ESP32 station changed");
			break;

		case SYSTEM_EVENT_STA_GOT_IP: {
			Serial.println("ESP32 station got IP from connected AP");
			ip = event->event_info.got_ip.ip_info.ip.addr;
			Serial.printf("%d.%d.%d.%d\n",
				ip >>  0 & 0xff,
				ip >>  8 & 0xff,
				ip >> 16 & 0xff,
				ip >> 24 & 0xff
			);
			xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
		}
		break;

		case SYSTEM_EVENT_STA_LOST_IP:
			Serial.println("ESP32 station lost IP and the IP is reset to 0");
			break;

		// case SYSTEM_EVENT_STA_BSS_RSSI_LOW:
		// 	Serial.println("ESP32 station connected BSS rssi goes below threshold");
		// 	break;

		case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
			Serial.println("ESP32 station wps succeeds in enrollee mode");
			break;

		case SYSTEM_EVENT_STA_WPS_ER_FAILED:
			Serial.println("ESP32 station wps fails in enrollee mode");
			break;

		case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
			Serial.println("ESP32 station wps timeout in enrollee mode");
			break;

		case SYSTEM_EVENT_STA_WPS_ER_PIN:
			Serial.println("ESP32 station wps pin code in enrollee mode");
			break;

		case SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP:
			Serial.println("ESP32 station wps overlap in enrollee mode");
			break;

		case SYSTEM_EVENT_AP_START:
			Serial.println("ESP32 soft-AP start");
			break;

		case SYSTEM_EVENT_AP_STOP:
			Serial.println("ESP32 soft-AP stop");
			break;

		// case SYSTEM_EVENT_AP_STACONNECTED:
		// 	Serial.println    a station connected to ESP32 soft-AP");
		// 	break;

		// case SYSTEM_EVENT_AP_STADISCONNECTED:
		// 	Serial.println    a station disconnected from ESP32 soft-AP");
		// 	break;

		case SYSTEM_EVENT_AP_STAIPASSIGNED:
			Serial.println("ESP32 soft-AP assign an IP to a connected station");
			break;

		case SYSTEM_EVENT_AP_PROBEREQRECVED:
			Serial.println("Receive probe request packet in soft-AP interface");
			break;

		// case SYSTEM_EVENT_ACTION_TX_STATUS:
		// 	Serial.println("Receive status of Action frame transmitted");
		// 	break;

		// case SYSTEM_EVENT_ROC_DONE:
		// 	Serial.println("Indicates the completion of Remain-on-Channel operation status");
		// 	break;

		// case SYSTEM_EVENT_STA_BEACON_TIMEOUT:
		// 	Serial.println("ESP32 station beacon timeout");
		// 	break;

		// case SYSTEM_EVENT_FTM_REPORT:
		// 	Serial.println("Receive report of FTM procedure");
		// 	break;

		case SYSTEM_EVENT_GOT_IP6:
			Serial.println("ESP32 station or ap or ethernet interface v6IP addr is preferred");
			break;

		case SYSTEM_EVENT_ETH_START:
			Serial.println("ESP32 ethernet start");
			break;

		case SYSTEM_EVENT_ETH_STOP:
			Serial.println("ESP32 ethernet stop");
			break;

		case SYSTEM_EVENT_ETH_CONNECTED:
			Serial.println("ESP32 ethernet phy link up");
			break;

		case SYSTEM_EVENT_ETH_DISCONNECTED:
			Serial.println("ESP32 ethernet phy link down");
			break;

		case SYSTEM_EVENT_ETH_GOT_IP:
			Serial.println("ESP32 ethernet got IP from connected AP");
			break;

		// case SYSTEM_EVENT_ETH_LOST_IP:
		// 	Serial.println("ESP32 ethernet lost IP and the IP is reset to 0");
		// 	break;

		case SYSTEM_EVENT_MAX:
			Serial.println("Number of members in this enum");
			break;

		// case  SYSTEM_EVENT_WIFI_READY:
		// 	Serial.println("wifi ready");
		// 	break;
		// case  SYSTEM_EVENT_STA_START:
		// 	Serial.println("wifi sta start");
		// 	break;
		// case  SYSTEM_EVENT_STA_STOP:
		// 	Serial.println("wifi sta stop");
		// 	break;
		// case  SYSTEM_EVENT_STA_CONNECTED:
		// 	Serial.println("wifi sta connected");
		// 	program->testSocket();
		// 	break;
		// case  SYSTEM_EVENT_STA_DISCONNECTED:
		// 	Serial.println("wifi sta disconnected");
		// 	break;


		default:
			Serial.println("unhandled event");
			break;
			
	}


	return ESP_OK;
}

