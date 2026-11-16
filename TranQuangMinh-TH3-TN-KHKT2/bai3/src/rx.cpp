#include <WiFi.h>
#include <esp_now.h>

typedef struct { int dem; } GoiTin;
GoiTin goi;

#if ESP_ARDUINO_VERSION_MAJOR >= 3
void onRecv(const esp_now_recv_info_t* info, const uint8_t* data, int len) {
#else
void onRecv(const uint8_t* mac, const uint8_t* data, int len) {
#endif
  memcpy(&goi, data, sizeof(goi));
  Serial.print("Nhan dem = ");
  Serial.println(goi.dem);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(500);
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  esp_now_init();
  esp_now_register_recv_cb(onRecv);
}

void loop() {}