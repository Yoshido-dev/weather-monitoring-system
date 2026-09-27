# 🌦️ Weather Monitoring System

An IoT-based weather monitoring system using **ESP8266**, **DHT11**, and a **Rain Sensor**. The system collects weather data and uploads it to **ThingSpeak** for remote monitoring.

## 🔧 Components
- ESP8266
- DHT11 Temperature & Humidity Sensor
- Rain Sensor
- ThingSpeak

## 📊 Data Monitored
- Temperature
- Humidity
- Atmospheric Pressure
- Rainfall

## ⚙️ How It Works
1. ESP8266 connects to Wi-Fi.
2. Sensors collect weather readings.
3. Data is displayed on the Serial Monitor.
4. Readings are uploaded to ThingSpeak.
5. The data can be monitored remotely through the ThingSpeak dashboard.

## 📚 Libraries
- ESP8266WiFi
- Wire
- DHT

## 🚀 Setup
1. Install the required Arduino libraries.
2. Add your Wi-Fi credentials.
3. Add your ThingSpeak API key.
4. Select the ESP8266 board in Arduino IDE.
5. Upload the code and open Serial Monitor at **115200 baud**.

## 👨‍💻 Author
**Rajkumar Lakkoju**
