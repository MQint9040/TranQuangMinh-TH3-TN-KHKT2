#include <WiFi.h>
#include <esp_now.h>

// SUA thanh MAC cua Receiver
uint8_t macNhan[] = {0x30, 0x76, 0xF5, 0xE8, 0x44, 0x48};

typedef struct { int dem; } GoiTin;
GoiTin goi;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_peer_info_t p = {};
  memcpy(p.peer_addr, macNhan, 6);
  p.channel = 0;
  p.encrypt = false;
  esp_now_add_peer(&p);
}

void loop() {
  goi.dem++;
  esp_now_send(macNhan, (uint8_t*)&goi, sizeof(goi));
  delay(2000);
}
