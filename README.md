# SentinelEye-WIDS: Wireless Intrusion Detection and User Awareness System

The 'Sentinel Eye' system vigilantly monitors wireless network environments to detect any signs of intrusion, such as unsolicited deauthentication attempts. Upon detecting potential threats, it swiftly alerts network clients with a notification bearing essential details.

## Contents

- `esp8266_intrusion_detection`: This directory contains the Arduino script that is uploaded to the ESP8266 microcontroller. It continuously monitors the Wi-Fi environment and detects any deauthentication packets, which could signify an attack.

- `telegram_bot`: This directory contains a Python script for a Telegram bot. The bot is designed to alert users of potential Wi-Fi intrusions and provides helpful information on immediate steps to take, common attacks, and general security tips.

- `certificates`: This directory contains the necessary certificates to ensure secure communication with the Pushover API for sending notifications.
