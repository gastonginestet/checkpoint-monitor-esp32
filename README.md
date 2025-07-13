# checkpoint-monitor-esp32
## 🏁 Race Checkpoint Tracker (ESP32 + RFID)

A runner control system for street races, using ESP32 and MFRC522 (RFID). This project enables the registration of participants passing through physical checkpoints by detecting RFID cards and sending real-time data via MQTT for storage and monitoring in Grafana/Node-RED.

---

📦 Features:

- Corridor detection via RFID (MFRC522).
- WiFi connection and data transmission via MQTT
- ⏱ Presence recording with timestamp
- 🚨 Alert if a runner remains stopped for more than X minutes.
- Integration with InfluxDB + Grafana for real-time visualisation
- Node-RED + Telegram for notifications.
