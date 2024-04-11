# SentinelEye-WIDS: Wireless Intrusion Detection and User Awareness System

The 'Sentinel Eye' system vigilantly monitors wireless network environments to detect any signs of intrusion, such as unsolicited deauthentication attempts. Upon detecting potential threats, it swiftly alerts network clients with a notification bearing essential details.

## Contents

- `esp8266_intrusion_detection`: This directory contains the Arduino script that is uploaded to the ESP8266 microcontroller. It continuously monitors the Wi-Fi environment and detects any deauthentication packets, which could signify an attack.

- `telegram_bot`: This directory contains a Python script for a Telegram bot. The bot is designed to alert users of potential Wi-Fi intrusions and provides helpful information on immediate steps to take, common attacks, and general security tips.

- `certificates`: This directory contains the necessary certificates to ensure secure communication with the Pushover API for sending notifications.

## Features

### ESP8266 Intrusion Detection

- Real-time monitoring of Wi-Fi channels for deauthentication packets
- Automated alert system via Pushover API when potential intrusion is detected
- System checks to minimize false alarms and promote accurate notifications

### Telegram Bot

- Command handling for various requests such as `/help`, `/immediate_help`, and `/security_tips`
- Detailed guidance on immediate steps to take upon a Wi-Fi attack
- Information on common Wi-Fi attacks, prevention tips, and how to respond
- An interactive and user-friendly interface to enhance user awareness

## Installation
### ESP8266 Intrusion Detection Setup
The ESP8266 module can detect and alert you to potential deauthentication attacks in real-time by using a cloud service like Pushover, which is free for the first 30 days. Follow the steps below to set it up:

1. **Pushover Account Setup:**
   - Create a Pushover account and obtain your User and API tokens.
     This process is not covered here, but a detailed setup guide is available at [Pushover's documentation page](https://pushover.net/faq).

2. **Loading the Sketch:**
   - Open Arduino IDE and copy the code provided above into a new sketch.
   - Insert the correct values for your Wi-Fi credentials, Pushover User Token, and API Key into the sketch.
```cpp
     const char* ssid = "Your Wifi Name";
     const char* password = "Your Wifi Password";
     const char* apiToken = "Your Pushover API Token";
     const char* userToken = "Your Pushover User Token";
```
Upload the sketch to your ESP8266 module.

3. **Setting Up Certificates:**

-Ensure the Pushover root CA certificate is included in the certificates directory and properly referenced in the script.

4.**Operational Behaviour:**

-After an attack is no longer recognized or has stopped, the ESP8266 will send a notification to your smartphone.
-Please note: upon connecting the ESP8266 to USB for the first time, a notification will be sent to your smartphone. This is a false positive and should be disregarded.

5.**Restart After Attack:**

-In the event of the detection of a deauthentication attack, the ESP8266 is programmed to restart to ensure it reconnects to the Wi-Fi network and sends out an alert

## Configuration

For configuration details, please refer to the comments within the script itself, which provide specific pointers on setting various parameters such as LED pin, Baud rate, scan time per channel, and packet rates.
