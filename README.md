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

### Stack: Node-RED, MQTT, InfluxDB, Telegraf, and Grafana

This repository contains the minimum required to run a stack with:

* [NodeRed](https://nodered.org/) Flow oriented programming system (open-source)
* [Mosquitto](https://mosquitto.org/) MQTT server (open-source)
* [InfluxDB](https://www.influxdata.com/products/influxdb-overview/) Time series oriented database (open-source)
* [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/) InfluxDB software agent (open-source)
* [Grafana](https://grafana.com/) Dashboard software (open-source)

#### Run
Run stack:

docker-compose -d up

If everything is OK, you should see:

* [NodeRed IDE](http://localhost:1880)
* [NodeRed UI](http://localhost:1880/ui)

#### Stop

docker-compose stop

#### Remove:

docker-compose down

#### First steps:

##### Add database:

To create the "iot_data_checkpoints" database in InfluxDB, use the following command:

> echo "create database iot_data_checkpoints" | docker exec -i checkpoint-monitor-esp32-influxdb-1 influx

To verify that it was created correctly, use this command:

> echo "show databases" | docker exec -i checkpoint-monitor-esp32-influxdb-1 influx
> echo "SELECT * FROM checkpoints LIMIT 5" | docker exec -i checkpoint-monitor-esp32-influxdb-1 influx -database iot_data_checkpoints

docker exec -it checkpoint-monitor-esp32-influxdb-1 influx


USE iot_data_checkpoints

SHOW MEASUREMENTS


SELECT * FROM checkpoints LIMIT 5
