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
