#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Create TinyGPS++ instance
TinyGPSPlus gps;

// Use UART2 (RX=16, TX=17)
HardwareSerial gpsSerial(2);

void setup() {
    Serial.begin(115200);      // Start serial monitor
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // GPS Serial (9600 baud, RX=16, TX=17)

    Serial.println("Waiting for GPS signal...");
}

void loop() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read()); // Parse GPS data

        if (gps.location.isUpdated()) {
            Serial.print("Latitude: ");
            Serial.print(gps.location.lat(), 6);
            Serial.print(" Longitude: ");
            Serial.println(gps.location.lng(), 6);
        }

        if (gps.date.isUpdated()) {
            Serial.print("Date: ");
            Serial.print(gps.date.day());
            Serial.print("/");
            Serial.print(gps.date.month());
            Serial.print("/");
            Serial.println(gps.date.year());
        }

        if (gps.time.isUpdated()) {
            Serial.print("Time: ");
            Serial.print(gps.time.hour());
            Serial.print(":");
            Serial.print(gps.time.minute());
            Serial.print(":");
            Serial.println(gps.time.second());
        }
    }
}
