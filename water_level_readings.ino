#include <WiFi.h>
#include <HTTPClient.h>

#define TRIG_PIN 5  // Trigger pin
#define ECHO_PIN 18 // Echo pin

const char* ssid = "OPPO F23 5G";       
const char* password = "arjunhotspot";  

// InfluxDB Cloud URL (Replace with your actual instance)
const char* influx_url = "https://us-east-1-1.aws.cloud2.influxdata.com/api/v2/write?bucket=iot&precision=s";

// Your InfluxDB API Token
const char* influx_token = "Nl69xZKGoHnW2PBhaDpDhdXBBc5AHqj_6ZNdMPkAly0GjFLWfwJcG80mFQKIG6EyCgtbI-r2vWDf1kpFV4qjZg==";

// Function to calculate water level in liters
float calculateWaterLevel(float distance) {
    return 3.5 - ((3.5 / (22.23 - 2.32)) * (distance - 2.32));
}

void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        float distance_cm = getDistance();
        float water_level = calculateWaterLevel(distance_cm);

        Serial.print("Distance: ");
        Serial.print(distance_cm);
        Serial.print(" cm, Water Level: ");
        Serial.print(water_level);
        Serial.println(" L");

        sendToInfluxDB(distance_cm, water_level);
    } else {
        Serial.println("WiFi Disconnected! Reconnecting...");
        WiFi.begin(ssid, password);
    }

    delay(5000); // Send data every 5 seconds
}

// Function to measure distance from ultrasonic sensor
float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    return (duration * 0.0343) / 2;  // Convert to cm
}

// Function to send data to InfluxDB Cloud
void sendToInfluxDB(float distance, float waterLevel) {
    HTTPClient http;
    http.begin(influx_url);
http.addHeader("Authorization", "Token " + String(influx_token));
http.addHeader("Content-Type", "text/plain; charset=utf-8");


    // Prepare Line Protocol Data
    String payload = "water_level,sensor=ultrasonic distance=" + String(distance) + ",liters=" + String(waterLevel) + " " + String(millis() * 1000000);

    int httpResponseCode = http.POST(payload);
    Serial.print("Server Response Code: ");
    Serial.println(httpResponseCode);
    Serial.println(payload);

    http.end();
}
