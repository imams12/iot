#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Konfigurasi WiFi
const char* ssid = "NamaWiFi";
const char* password = "PasswordWiFi";

// Konfigurasi MQTT
const char* mqtt_server = "mqtt.eclipse.org";
const char* mqtt_topic = "sensor/dht";

// Konfigurasi pin untuk sensor DHT
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi koneksi WiFi
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membaca suhu dan kelembaban dari sensor DHT
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Mengonversi nilai ke dalam string
  String payload = String(temperature) + "," + String(humidity);

  // Mengirimkan data ke broker MQTT
  client.publish(mqtt_topic, (char*) payload.c_str());

  // Delay sejenak sebelum membaca ulang sensor
  delay(5000);
}
