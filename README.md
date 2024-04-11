# SentinelEye-WIDS: Wireless Intrusion Detection and User Awareness System

The 'Sentinel Eye' system vigilantly monitors wireless network environments to detect any signs of intrusion, such as unsolicited deauthentication attempts. Upon detecting potential threats, it swiftly alerts network clients with a notification bearing essential details.

## Project Structure

```
SentinelEye-WIDS
    /esp8266_intrusion_detection
        - intrusion_detection.ino    
    /telegram_bot
        - telegram_bot.py            
    /certificates
        - pushover_root_ca.pem       
    /README.md
```

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

   - Ensure the Pushover root CA certificate is included in the certificates directory and properly referenced in the script.

4. **Operational Behaviour:**

   - After an attack is no longer recognized or has stopped, the ESP8266 will send a notification to your smartphone.
   - Please note: upon connecting the ESP8266 to USB for the first time, a notification will be sent to your smartphone. This is a false positive and should be disregarded.

5. **Restart After Attack:**

   - In the event of the detection of a deauthentication attack, the ESP8266 is programmed to restart to ensure it reconnects to the Wi-Fi network and sends out an alert

### Telegram Bot Setup

Set up the Telegram bot to interact with users to provide information and alerts:

1. **Bot Creation:**
   
   - Create a new bot via the BotFather on Telegram and obtain the API token.

3. **Script Configuration:**
   
   - Replace the placeholder BOT_TOKEN in the telegram_bot.py script with your bot's API token.

```python
     BOT_TOKEN = 'Your Bot API Token'
```
Set your bot's web link appropriately.

```python
     YOUR_BOT_LINK = 'https://t.me/YourBotUsername'
```
4. **Dependencies Installation:**

   - Ensure you have Python installed on your system.
   - Install the pyTelegramBotAPI library using pip:
```bash
     pip install pyTelegramBotAPI
```
5. **Running the Bot:**

Run the bot script in your environment:
```bash
     python telegram_bot.py
```
The bot should now be live and responding to commands.

6. **Customizing Commands:**

Edit the bot's responses and commands within the script to fit your needs.

## Configuration

For configuration details, please refer to the comments within the script itself, which provide specific pointers on setting various parameters such as LED pin, Baud rate, scan time per channel, and packet rates.

## Usage

After following the installation and setup steps, your system will:
- Monitor for deauthentication packets signaling a possible attack.
- Illuminate an LED or perform other actions as defined in the `intrusion_detection.ino` when an attack is detected.
- Use the Telegram bot to inform users about potential security threats and offer advice on how to act accordingly.
- Ensure all communications for alerts are securely sent through Pushover with the provided certificate.

For further assistance, please refer to the instructions within the respective component directory.

## Contributing
We welcome contributions and suggestions to improve the SentinelEye-WIDS project. Please feel free to submit issues and pull requests through the project's GitHub repository.

### Versioning
We use SemVer for versioning. For the versions available, see the tags on this repository.

### Authors

- Sarath K - Initial work - [sarathk73](https://github.com/sarathk73)

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Thank you for choosing SentinelEye-WIDS to secure your wireless network environment.

