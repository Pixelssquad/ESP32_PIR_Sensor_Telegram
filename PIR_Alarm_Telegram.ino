/*
Project by Diego Pellacani
https://github.com/Pixelssquad/ESP32_PIR_Sensor_Telegram
Righe da modificare: 24,25,28,29  ed eventualmente la 17 e 18 se utilizzate piedini diversi sulla vostra dev board


My Youtube Channel: https://www.youtube.com/@PixelsSquad
Ideas from: https://randomnerdtutorials.com/telegram-esp8266-nodemcu-motion-detection-arduino/ https://gist.github.com/nafiesl/4ad622f344cd1dc3bb1ecbe468ff9f8a https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

//Sensorr PIR a Led
#define MOTION_SENSOR_PIN  15  // PIN DELL'ESP32 DOVE è CONNESSA L'USCITA DEL SENSORE HCSR505
#define LED_PIN         2  // PIN DEL LED, SULLA MIA ESP32 DI IDEASPARK L'USCITA 2 è QUELLA DEL LED INTERNO
int motionStateCurrent  = LOW; // current  state of motion sensor's pin
int motionStatePrevious = LOW; // previous state of motion sensor's pin


// Credenziali della tua Wifi
#define WIFI_SSID "OOZTEST"  // Nome della tua rete WiFi
#define WIFI_PASSWORD "diegodiego"  // Password della tua rete WiFi

// Telegram
#define BOT_TOKEN "xxxxxxxxx:yyyyyyyyyyyyyyyyyyy" // Telegram BOT Token (Dal bot Botfather)
#define CHAT_ID "zzzzzzzzzzzzz"   //Recuperalo da https://api.telegram.org/botXXXXXXXXXXXXX/getUpdates dove XXXX è il token del bot


const unsigned long BOT_MTBS = 1000; // mean time between scan messages
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
  }
}

void setup()
{

  pinMode(MOTION_SENSOR_PIN, INPUT); // set ESP32 pin to input mode
  pinMode(LED_PIN, OUTPUT);          // set ESP32 pin to output mode


  Serial.begin(115200);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  //  bot.sendMessage(CHAT_ID, "Bot avviato, allarme in funzione", "");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Bot avviato, allarme in funzione", "");

}

void loop()
{

//bot
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
// /bot

//sensor e led
  motionStatePrevious = motionStateCurrent;            // store old state
  motionStateCurrent  = digitalRead(MOTION_SENSOR_PIN); // read new state

  if (motionStatePrevious == LOW && motionStateCurrent == HIGH) { // pin state change: LOW -> HIGH
    Serial.println("Movimento rilevato, accendo il led");
    digitalWrite(LED_PIN, HIGH); // accende il led
    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
    bot.sendMessage(CHAT_ID, "Movimento rilevato (Sensore 1)", "");



  } else if (motionStatePrevious == HIGH && motionStateCurrent == LOW) { // pin state change: HIGH -> LOW
    Serial.println("Nessun movimento, torno a dormire....");
    digitalWrite(LED_PIN, LOW);  // spegne il led

    secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
    bot.sendMessage(CHAT_ID, ".", "");  

  }
// /sensor e led



}
