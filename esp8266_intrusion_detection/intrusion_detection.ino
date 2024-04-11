#include <WiFiClientSecure.h>

#include <ArduinoJson.h>

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

// include ESP8266 Non-OS SDK functions

extern "C" {

#include "user_interface.h"

}

// ===== SETTINGS ===== //

#define LED 2              /* LED pin (2=built-in LED) */

#define LED_INVERT true    /* Invert HIGH/LOW for LED */

#define SERIAL_BAUD 115200 /* Baudrate for serial communication */

#define CH_TIME 140        /* Scan time (in ms) per channel */

#define PKT_RATE 20         /* Min. packets before it gets recognized as an attack */

#define PKT_TIME 1         /* Min. interval (CH_TIME*CH_RANGE) before it gets recognized as an attack */

const char* ssid = "Yor Wifi Name";

const char* password = "Your Wifi Password";

const char* apiToken = "Your Pushover API Token";

const char* userToken = "Your Pushover User Token";

//Pushover API endpoint

const char* pushoverApiEndpoint = "https://api.pushover.net/1/messages.json";

//Pushover root certificate (valid from 11/10/2006 to 11/10/2031)

const char *PUSHOVER_ROOT_CA = "-----BEGIN CERTIFICATE-----\n"

               "MIIEszCCA5ugAwIBAgIQCyWUIs7ZgSoVoE6ZUooO+jANBgkqhkiG9w0BAQsFADBh\n"
              "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
              "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\n"
              "MjAeFw0xNzExMDIxMjI0MzNaFw0yNzExMDIxMjI0MzNaMGAxCzAJBgNVBAYTAlVT\n"
              "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
              "b20xHzAdBgNVBAMTFlJhcGlkU1NMIFRMUyBSU0EgQ0EgRzEwggEiMA0GCSqGSIb3\n"
              "DQEBAQUAA4IBDwAwggEKAoIBAQC/uVklRBI1FuJdUEkFCuDL/I3aJQiaZ6aibRHj\n"
              "ap/ap9zy1aYNrphe7YcaNwMoPsZvXDR+hNJOo9gbgOYVTPq8gXc84I75YKOHiVA4\n"
              "NrJJQZ6p2sJQyqx60HkEIjzIN+1LQLfXTlpuznToOa1hyTD0yyitFyOYwURM+/CI\n"
              "8FNFMpBhw22hpeAQkOOLmsqT5QZJYeik7qlvn8gfD+XdDnk3kkuuu0eG+vuyrSGr\n"
              "5uX5LRhFWlv1zFQDch/EKmd163m6z/ycx/qLa9zyvILc7cQpb+k7TLra9WE17YPS\n"
              "n9ANjG+ECo9PDW3N9lwhKQCNvw1gGoguyCQu7HE7BnW8eSSFAgMBAAGjggFmMIIB\n"
              "YjAdBgNVHQ4EFgQUDNtsgkkPSmcKuBTuesRIUojrVjgwHwYDVR0jBBgwFoAUTiJU\n"
              "IBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsG\n"
              "AQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMDQGCCsGAQUFBwEB\n"
              "BCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQuY29tMEIGA1Ud\n"
              "HwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEds\n"
              "b2JhbFJvb3RHMi5jcmwwYwYDVR0gBFwwWjA3BglghkgBhv1sAQEwKjAoBggrBgEF\n"
              "BQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzALBglghkgBhv1sAQIw\n"
              "CAYGZ4EMAQIBMAgGBmeBDAECAjANBgkqhkiG9w0BAQsFAAOCAQEAGUSlOb4K3Wtm\n"
              "SlbmE50UYBHXM0SKXPqHMzk6XQUpCheF/4qU8aOhajsyRQFDV1ih/uPIg7YHRtFi\n"
              "CTq4G+zb43X1T77nJgSOI9pq/TqCwtukZ7u9VLL3JAq3Wdy2moKLvvC8tVmRzkAe\n"
              "0xQCkRKIjbBG80MSyDX/R4uYgj6ZiNT/Zg6GI6RofgqgpDdssLc0XIRQEotxIZcK\n"
              "zP3pGJ9FCbMHmMLLyuBd+uCWvVcF2ogYAawufChS/PT61D9rqzPRS5I2uqa3tmIT\n"
              "44JhJgWhBnFMb7AGQkvNq9KNS9dd3GWc17H/dXa1enoxzWjE0hBdFjxPhUb0W3wi\n"
              "8o34/m8Fxw==\n"
                 "-----END CERTIFICATE-----\n";

// Create a list of certificates with the server certificate

X509List cert(PUSHOVER_ROOT_CA);

// Channels to scan on (US=1-11, EU=1-13, JAP=1-14)

const short channels[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13/*,14*/ };

// ===== Runtime variables ===== //

int ch_index { 0 };               // Current index of channel array

int packet_rate { 0 };            // Deauth packet counter (resets with each update)

int attack_counter { 0 };         // Attack counter

unsigned long update_time { 0 };  // Last update time

unsigned long ch_time { 0 };      // Last channel hop time

void connect(){

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Connecting to WiFi...");

  }

  Serial.println("Connected to WiFi");

  // Set time via NTP, as required for x.509 validation

  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");

  time_t now = time(nullptr);

  while (now < 8 * 3600 * 2) {

    delay(500);

    Serial.print(".");

    now = time(nullptr);

  }

  Serial.println("");

  struct tm timeinfo;

  gmtime_r(&now, &timeinfo);

  Serial.print("Current time: ");

  Serial.print(asctime(&timeinfo));

  //Make HTTPS POST request to send notification

  if (WiFi.status() == WL_CONNECTED) {

    // Create a JSON object with notification details

    // Check the API parameters: https://pushover.net/api

    StaticJsonDocument<512> notification;

    notification["token"] = apiToken;

    notification["user"] = userToken;

    notification["message"] = "Attention: Sentinel Eye has flagged a potential intrusion into your network. For immediate assistance, please consult our Telegram bot: https://t.me/seyewifibot. Note: Disregard the initial alert as it is a system check message and does not indicate an actual intrusion.";

    notification["title"] = "Sentinal Eye";

    notification["url"] = "";

    notification["url_title"] = "";

    notification["html"] = "";

    notification["priority"] = "1";

    notification["sound"] = "seye2";

    notification["timestamp"] = "";

    // Serialize the JSON object to a string

    String jsonStringNotification;

    serializeJson(notification, jsonStringNotification);

    // Create a WiFiClientSecure object

    WiFiClientSecure client;

    // Set the certificate

    client.setTrustAnchors(&cert);

    // Create an HTTPClient object

    HTTPClient http;

    // Specify the target URL

    http.begin(client, pushoverApiEndpoint);

    // Add headers

    http.addHeader("Content-Type", "application/json");

    // Send the POST request with the JSON data

    int httpResponseCode = http.POST(jsonStringNotification);

    // Check the response

    if (httpResponseCode > 0) {

      Serial.printf("HTTP response code: %d\n", httpResponseCode);

      String response = http.getString();

      Serial.println("Response:");

      Serial.println(response);

    } else {

      Serial.printf("HTTP response code: %d\n", httpResponseCode);

    }

    // Close the connection

    http.end();

  }

}

// ===== Sniffer function ===== //

void sniffer(uint8_t *buf, uint16_t len) {

  if (!buf || len < 28) return; // Drop packets without MAC header

  byte pkt_type = buf[12]; // second half of frame control field

  //byte* addr_a = &buf[16]; // first MAC address

  //byte* addr_b = &buf[22]; // second MAC address

  // If captured packet is a deauthentication or dissassociaten frame

  if (pkt_type == 0xA0 || pkt_type == 0xC0) {

    ++packet_rate;

  }

}

// ===== Attack detection functions ===== //

void attack_started() {

  digitalWrite(LED, !LED_INVERT); // turn LED on

  Serial.println("ATTACK DETECTED");

}

void attack_stopped() {

  digitalWrite(LED, LED_INVERT); // turn LED off

  Serial.println("ATTACK STOPPED");

  Serial.begin(115200);

  ESP.restart();

}

// ===== Setup ===== //

void setup() {

  connect();

  Serial.begin(SERIAL_BAUD); // Start serial communication

  pinMode(LED, OUTPUT); // Enable LED pin

  digitalWrite(LED, LED_INVERT);

  WiFi.disconnect();                   // Disconnect from any saved or active WiFi connections

  wifi_set_opmode(STATION_MODE);       // Set device to client/station mode

  wifi_set_promiscuous_rx_cb(sniffer); // Set sniffer function

  wifi_set_channel(channels[0]);        // Set channel

  wifi_promiscuous_enable(true);       // Enable sniffer

  Serial.println("Started \\o/");

}

// ===== Loop ===== //

void loop() {

  unsigned long current_time = millis(); // Get current time (in ms)

  // Update each second (or scan-time-per-channel * channel-range)

  if (current_time - update_time >= (sizeof(channels)*CH_TIME)) {

    update_time = current_time; // Update time variable

    // When detected deauth packets exceed the minimum allowed number

    if (packet_rate >= PKT_RATE) {

      ++attack_counter; // Increment attack counter

    } else {

      if(attack_counter >= PKT_TIME) attack_stopped();

      attack_counter = 0; // Reset attack counter

    }

    // When attack exceeds minimum allowed time

    if (attack_counter == PKT_TIME) {

      attack_started();

    }

    Serial.print("Packets/s: ");

    Serial.println(packet_rate);

    packet_rate = 0; // Reset packet rate

  }

  // Channel hopping

  if (sizeof(channels) > 1 && current_time - ch_time >= CH_TIME) {

    ch_time = current_time; // Update time variable

    // Get next channel

    ch_index = (ch_index+1) % (sizeof(channels)/sizeof(channels[0]));

    short ch = channels[ch_index];

    // Set channel

    //Serial.print("Set channel to ");

    //Serial.println(ch);

    wifi_set_channel(ch);

  }

}
