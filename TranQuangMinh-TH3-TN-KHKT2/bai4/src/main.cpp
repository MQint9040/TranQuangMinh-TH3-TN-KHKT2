#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MQint-";
const char* pass = "qwertyui";

WebServer server(80);
const int LED = 12;
bool on = false;

void handleRoot() {
  String h = "<!DOCTYPE html><html><head><meta charset='utf-8'>";
  h += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  h += "<title>ESP32 LED</title></head><body style='font-family:sans-serif;text-align:center'>";
  h += "<h1>ESP32 LED</h1>";
  h += on ? "<p><b style='color:green'>LED: dang BAT</b></p>"
          : "<p><b style='color:red'>LED: dang TAT</b></p>";
  h += "<a href='/on'><button style='font-size:24px'>BAT</button></a> ";
  h += "<a href='/off'><button style='font-size:24px'>TAT</button></a>";
  h += "</body></html>";
  server.send(200, "text/html", h);
}

void redirectHome() {
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOn()  { on = true;  digitalWrite(LED, HIGH); redirectHome(); }
void handleOff() { on = false; digitalWrite(LED, LOW);  redirectHome(); }

void handleToggle() {
  on = !on;
  digitalWrite(LED, on);
  redirectHome();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/toggle", handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
}
