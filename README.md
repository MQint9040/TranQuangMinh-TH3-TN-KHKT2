# Thực hành 3 - Tầng mạng: kết nối không dây trên ESP32

- Môn: Thí nghiệm Khoa học Kỹ thuật 2 (AET2022) - BCSE 2025
- Sinh viên: Trần Quang Minh (MQint) - MSSV 25119040
- Nhóm: nhom-03
- Công cụ: PlatformIO (VS Code), Fritzing, nRF Connect for Mobile, MQTTX
- Board: ESP32 (framework Arduino)

## Cấu trúc repo

```
.
├── README.md
├── anh-ket-qua/   ảnh, video kết quả của 5 bài
├── bai1/          Wi-Fi: AP và Station
├── bai2/          BLE server
├── bai3/          ESP-NOW (transmitter, receiver)
├── bai4/          HTTP web server điều khiển LED (kèm sơ đồ Fritzing)
├── bai5/          MQTT publish/subscribe
└── TH3-tang-mang-khong-day.pdf   đề bài
```

Mỗi `baiN` là một project PlatformIO riêng (`platformio.ini`, `src/main.cpp`). Nạp bằng `pio run -t upload` trong thư mục bài tương ứng.

## Bài 1 - Wi-Fi: Access Point và Station

- Ví dụ 1: ESP32 phát AP, SSID `<SSID nhóm>`, mật khẩu `<mật khẩu>`. Serial in IP của AP: `192.168.4.1`.
- Ví dụ 2: ESP32 làm Station nối vào AP/router, IP nhận được: `<IP STA>`.
- Kết quả: `anh-ket-qua/<tên ảnh Serial AP>`, `anh-ket-qua/<tên ảnh Serial STA>`.

## Bài 2 - BLE server

- ESP32 làm BLE server, tên thiết bị `<tên nhóm>`, một service và một characteristic.
- Giá trị characteristic: `<thông điệp / MSSV>`. Đã thêm `PROPERTY_WRITE`, ghi giá trị mới bằng nRF Connect rồi đọc lại để xác nhận.
- UUID service: `4fafc201-1fb5-459e-8fcc-c5c9c331914b`
- UUID characteristic: `beb5483e-36e1-4688-b7f5-ea07361b26a8`
- Kết quả: `anh-ket-qua/<tên ảnh nRF Connect>`.

## Bài 3 - ESP-NOW

- Transmitter gửi struct `GoiTin { int dem; }` mỗi 2 giây tới MAC của Receiver, Receiver in số đếm ra Serial.
- MAC Receiver: `<xx:xx:xx:xx:xx:xx>`
- MAC Transmitter: `<xx:xx:xx:xx:xx:xx>`
- Cả hai kit đặt `WIFI_STA`, struct hai bên giống hệt nhau.
- Thử chéo nhóm: `<đã làm / chưa làm>`, kết quả: `<nhóm khác có nhận được hay không>`.
- Kết quả: `anh-ket-qua/<tên ảnh Serial Receiver>`.

## Bài 4 - HTTP web server

- ESP32 làm Station, chạy WebServer cổng 80, LED nối GPIO2.
- Route: `/` (hiển thị trạng thái BẬT/TẮT), `/on`, `/off`.
- Mở IP của ESP32 trên trình duyệt (điện thoại cùng mạng) rồi bấm bật/tắt.
- Sơ đồ Fritzing: `bai4/<tên file .fzz>`.
- Kết quả: `anh-ket-qua/<ảnh trang web>`, `anh-ket-qua/<ảnh/video LED đổi trạng thái>`.

## Bài 5 - MQTT

- Broker: `test.mosquitto.org`, cổng 1883. Thư viện: PubSubClient.
- Topic nhóm 03:

  | Topic | Kit A | Kit B |
  |---|---|---|
  | `bcse/th3/nhom-03/demA` | publish số đếm | - |
  | `bcse/th3/nhom-03/demB` | - | publish số đếm |
  | `bcse/th3/nhom-03/ledA` | subscribe | publish lệnh |
  | `bcse/th3/nhom-03/ledB` | publish lệnh | subscribe |

- Lệnh LED: `1` bật, `0` tắt. Client id mỗi kit khác nhau (`esp32-th3-<MAC>`).
- Nạp: `pio run -e kit_a -t upload` hoặc `pio run -e kit_b -t upload`.
- Kiểm tra bằng MQTTX: subscribe `bcse/th3/nhom-03/#`, publish `1`/`0` vào `ledA`/`ledB`.
- Kết quả: `anh-ket-qua/<ảnh MQTTX nhận số đếm>`, `anh-ket-qua/<video LED bật/tắt>`.
