#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>

#define SV_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CH_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  BLEDevice::init("MQint-ESP32-BLE");            
  BLEServer* sv = BLEDevice::createServer();
  BLEService* se = sv->createService(SV_UUID);
  BLECharacteristic* ch = se->createCharacteristic(
      CH_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  ch->setValue("25119040");                      
  se->start();
  BLEDevice::getAdvertising()->addServiceUUID(SV_UUID);
  BLEDevice::getAdvertising()->start();
}

void loop() { delay(2000); }
