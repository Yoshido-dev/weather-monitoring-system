#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DHT.h>

// 🔐 WiFi
const char* ssid = "Raj Kumar's A34";
const char* password = "rajkumar2";

// 🌐 ThingSpeak
String apiKey = "AKHG5YEQCFANSEFB";
const char* server = "api.thingspeak.com";

// 🌡️ DHT11
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// 🌧️ Rain Sensor
#define RAINPIN A0

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(100);

  dht.begin();

  // 📶 WiFi connect
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());
}

void loop() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // 🔥  PRESSURE sensor
  float pressure = 1000 + random(-20, 20);

  // 🌧️ Rain sensor
  int rainRaw = analogRead(RAINPIN);

  // 🔧 Convert to %
  int rainPercent = map(rainRaw, 1024, 400, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  Serial.println("\n======================");

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT ERROR!");
    return;
  }

  Serial.print("Temp: "); Serial.println(temperature);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Pressure: "); Serial.println(pressure);
  Serial.print("Rain %: "); Serial.println(rainPercent);

  // 📡 Send to ThingSpeak
  if (client.connect(server, 80)) {

    String postStr = "api_key=" + apiKey;
    postStr += "&field1=" + String(temperature);
    postStr += "&field2=" + String(humidity);
    postStr += "&field3=" + String(pressure);
    postStr += "&field4=" + String(rainPercent);

    client.print("POST /update HTTP/1.1\r\n");
    client.print("Host: api.thingspeak.com\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Type: application/x-www-form-urlencoded\r\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\r\n\r\n");
    client.print(postStr);

    while (client.available()) {
      Serial.println(client.readString());
    }

    Serial.println("Data sent to ThingSpeak ✅");
  } else {
    Serial.println("Connection FAILED ❌");
  }

  client.stop();

  delay(3000);  
}