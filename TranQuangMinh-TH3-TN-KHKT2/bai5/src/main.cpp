#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "MQint-";
const char* WIFI_PASS = "qwertyui";
const char* BROKER    = "test.mosquitto.org";   // hoac IP may Mosquitto trong LAN
const int   PORT      = 1883;

#if defined(KIT_A)
  #define LED_SELF  "bcse/th3/nhom-03/ledA"
  #define LED_PEER  "bcse/th3/nhom-03/ledB"
  #define DEM_TOPIC "bcse/th3/nhom-03/demA"
#else
  #define LED_SELF  "bcse/th3/nhom-03/ledB"
  #define LED_PEER  "bcse/th3/nhom-03/ledA"
  #define DEM_TOPIC "bcse/th3/nhom-03/demB"
#endif

const int LED = 12;
const int BTN = 0;          // nut BOOT: bam de gui lenh bat/tat sang kit kia

WiFiClient wifi;
PubSubClient mqtt(wifi);
String clientId;
bool peerState = false;
int dem = 0;
unsigned long tPub = 0, tBtn = 0;

void onMessage(char* topic, byte* payload, unsigned int len) {
  if (len < 1) return;
  if (payload[0] == '1') digitalWrite(LED, HIGH);
  else if (payload[0] == '0') digitalWrite(LED, LOW);
}

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void connectMqtt() {
  while (!mqtt.connected()) {
    if (mqtt.connect(clientId.c_str())) mqtt.subscribe(LED_SELF);
    else delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  clientId = "esp32-th3-" + String((uint32_t)ESP.getEfuseMac(), HEX);
  connectWifi();
  mqtt.setServer(BROKER, PORT);
  mqtt.setCallback(onMessage);
  connectMqtt();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWifi();
  if (!mqtt.connected()) connectMqtt();
  mqtt.loop();

  unsigned long now = millis();

  if (now - tPub >= 2000) {
    tPub = now;
    mqtt.publish(DEM_TOPIC, String(dem++).c_str());
  }

  if (digitalRead(BTN) == LOW && now - tBtn > 300) {
    tBtn = now;
    peerState = !peerState;
    mqtt.publish(LED_PEER, peerState ? "1" : "0");
  }
}