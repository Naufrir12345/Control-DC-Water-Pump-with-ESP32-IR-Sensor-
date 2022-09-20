#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
// Initialize Telegram BOT
#define BOTtoken "MyBotToken"
// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "MyChatID"
// Replace with your network credentials
const char* ssid = "AndroidAP";
const char* password = "pyuh6247";
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
const int IRSensor = 12;
const int PinPump = 14;
void setup() {
Serial.begin(115200);
configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
pinMode(IRSensor, INPUT);
pinMode(PinPump, OUTPUT);
digitalWrite(PinPump, LOW);
// Attempt to connect to Wifi network:
Serial.print("Connecting Wifi: ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println("");
Serial.println("WiFi connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
bot.sendMessage(CHAT_ID, "Bot started up", "");
}
void loop() {
int IR = digitalRead(IRSensor);
if (IR == 0) {
bot.sendMessage(CHAT_ID, "Gerakan Terdeteksi! DC Pump Menyala!", "");
Serial.println("Gerakan Terdeteksi! DC Pump Menyala!");
digitalWrite(PinPump, LOW);
delay(10000);
bot.sendMessage(CHAT_ID, "Gerakan Tidak Terdeteksi! DC Pump Mati!", "");
Serial.println("Gerakan Tidak Terdeteksi! DC Pump Mati!");
}
else {
digitalWrite(PinPump, HIGH);
}
}
