#include <SPI.h>
#include <MFRC522.h>

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <PubSubClient.h>

// Pines MFRC522
#define SS_PIN  21
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Instancia lector


// WiFi
const char* ssid = "alumnosInfo";
const char* password = "InformaticaUNLP";

// MQTT
const char* MQTT_BROKER_ADRESS = "broker.mqtt.cool";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP32_Checkpoint";
const char* MQTT_USER = "user";
const char* MQTT_PASS = "password";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("WiFi conectado. IP: " + WiFi.localIP().toString());

  // MQTT
  client.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
  reconnect();

  // SPI y MFRC522
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Acerque una tarjeta RFID al lector...");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lectura de tarjeta
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Leer UID
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  // Simular RSSI
  int fakeRSSI = random(-69, -50);

  // Timestamp
  unsigned long timestamp = millis();

  // Payload JSON
  String payload = "{";
  payload += "\"id\": \"" + uid + "\",";
  payload += "\"rssi\": " + String(fakeRSSI) + ",";
  payload += "\"dentroDeZona\": true,";
  payload += "\"timestamp\": " + String(timestamp);
  payload += "}";

  // Enviar MQTT
  client.publish("carrera/checkpoint", payload.c_str());
  Serial.println(">> Publicado: " + payload);

  mfrc522.PICC_HaltA();  // Detener lectura hasta nueva tarjeta
  mfrc522.PCD_StopCrypto1();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conectar MQTT...");
    if (client.connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASS)) {
      Serial.println("conectado.");
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(". Intentando en 5s...");
      delay(5000);
    }
  }
}
