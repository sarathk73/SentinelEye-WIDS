import telebot
from telebot import types

BOT_TOKEN = 'type your Bot Token'
bot = telebot.TeleBot(BOT_TOKEN)

YOUR_BOT_LINK = 'place your Bot Link'  


@bot.message_handler(commands=['start', 'hello'])
def send_welcome(message):
    welcome_message = ("Welcome to the Sentinel Eye Bot.\n"
                       "Receive alerts and security measures for your network.\n"
                       "To get started, type /help to see how I can assist you.")
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    markup.row('/help', '/security_tips')
    markup.row('/common_attacks', '/preventative_measures')
    markup.row('/immediate_help', '/feedback')
    bot.reply_to(message, welcome_message, reply_markup=markup)


@bot.message_handler(commands=['help'])
def send_help(message):
    help_message = ("Here's what you can do:\n"
                    "/immediate_help - Get immediate actions for a known threat\n"
                    "/security_tips - General Wi-Fi safety tips\n"
                    "/common_attacks - Information on common attacks and how to prevent them\n"
                    "/preventative_measures - Steps to prevent attacks\n"
                    "/feedback - Provide your feedback to improve the bot")
    bot.reply_to(message, help_message)


@bot.message_handler(commands=['preventative_measures'])
def preventative_measures(message):
    prevention_message = "Practicing good Wi-Fi hygiene can prevent many attacks:\n\n"
    prevention_message += "- Regularly update all devices connected to the Wi-Fi network.\n"
    prevention_message += "- Disallow remote management of your router over the internet.\n"
    prevention_message += "- Limit connections to your network as much as possible.\n"
    prevention_message += "- Use a VPN for extra security when accessing sensitive information."
    bot.send_message(message.chat.id, prevention_message, parse_mode='Markdown')


@bot.message_handler(commands=['common_attacks'])
def common_attacks(message):
    attacks_message = "Here are some common Wi-Fi attacks along with preventative measures and what to do if you believe you've been attacked:\n\n"

    
    attacks_message += "📡 *Deauthentication Attack:*\n_Prevent:_ Enable MAC address filtering.\n_If attacked:_ Reconnect and consider using a VPN.\n\n"

    attacks_message += "👹 *Evil Twin Attack:*\n_Prevent:_ Use a VPN and connect only to Wi-Fi networks with WPA2 or WPA3 security.\n_If attacked:_ Forget the network and inform the network administrator.\n\n"


    attacks_message += "🔍 *Packet Sniffing:*\n_Prevent:_ Use encrypted connections (HTTPS, VPNs).\n_If attacked:_ Change any compromised passwords and monitor accounts for suspicious activity.\n\n"


    attacks_message += "🔐 *KRACK Attack:*\n_Prevent:_ Regularly update your devices to patch vulnerabilities.\n_If attacked:_ Disconnect from Wi-Fi and update your device.\n\n"

    bot.send_message(message.chat.id, attacks_message, parse_mode='Markdown')



@bot.message_handler(commands=['immediate_help'])
def immediate_help(message):
    
    security_measures = (
        "🚨 Immediate Steps to Take If You Suspect a Wi-Fi Attack:\n"
        "1️⃣ **Disconnect**: Disconnect from your Wi-Fi network immediately.\n"
        "2️⃣ **Reset Router**: Use a wired connection to reset your router to factory settings.\n"
        "3️⃣ **Firmware Update**: Ensure your router's firmware is updated to the latest version.\n"
        "4️⃣ **Change Passwords**: Change the Wi-Fi password, as well as the admin credentials for the router.\n"
        "5️⃣ **Reconnect Devices**: Reconnect your devices one by one, ensuring they are not compromised.\n"
        "6️⃣ **Monitor Network**: Use network monitoring tools to watch for unusual activity.\n"
        "7️⃣ **Consult Expert**: If the issue persists, consider consulting with a cybersecurity expert.\n\n"
        "Follow the steps carefully, and ensure your network's security is reinstated."
    )
    bot.send_message(message.chat.id, security_measures, parse_mode='Markdown')

@bot.message_handler(commands=['security_tips'])
def send_security_tips(message):
    security_tips = (
        "🔒 Wi-Fi Security Tips:\n"
        "1️⃣ **Use Strong Encryption**: Enable WPA3 encryption on your Wi-Fi network. If not available, use WPA2.\n"
        "2️⃣ **Strong Passwords**: Use complex passwords that are hard to guess. Mix letters, numbers, and special characters.\n"
        "3️⃣ **Regularly Update Passwords**: Change your Wi-Fi password regularly to prevent unauthorized access.\n"
        "4️⃣ **Update Router Firmware**: Keep your router's firmware up to date to protect against the latest threats.\n"
        "5️⃣ **Disable WPS**: Turn off Wi-Fi Protected Setup (WPS) as it can be a security vulnerability.\n"
        "6️⃣ **Limit W-Fi Range**: Adjust the strength of your Wi-Fi signal to cover only your working area.\n"
        "7️⃣ **Guest Network**: Set up a separate network for guests to protect your main network.\n"
        "8️⃣ **Monitor Network Activity**: Keep an eye on your network's activity and connected devices.\n\n"
        "Keep your network safe by following these best practices regularly."
    )
    bot.reply_to(message, security_tips, parse_mode='Markdown')

@bot.message_handler(commands=['feedback'])
def process_feedback(message):
    msg = bot.send_message(message.chat.id, "Please type your feedback and send it to us. Thank you for helping us improve!")
    
    bot.register_next_step_handler(msg, receive_feedback)

def receive_feedback(message):
    thank_you_message = "Thank you for your feedback! We're constantly working to improve your experience."
    bot.send_message(message.chat.id, thank_you_message)


bot.infinity_polling()