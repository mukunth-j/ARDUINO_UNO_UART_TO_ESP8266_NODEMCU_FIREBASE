#include <Wire.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

// WiFi & Firebase credentials
char FIREBASE_AUTH[] = "AIzaSyB6VBECthCvRJU-KRI7LdPHLQT60lBPxyw"; 
char FIREBASE_HOST[] = "https://sms-lil-default-rtdb.firebaseio.com/"; 
char WIFI_SSID[] = "JM";     
char WIFI_PASSWORD[] = "Qwerty31"; 

// Define software serial RX and TX pins
#define RX_PIN D7
#define TX_PIN D8
SoftwareSerial espSerial(RX_PIN, TX_PIN);  // RX, TX

FirebaseData firebaseData;

void setup() {
    Serial.begin(115200);     // Debugging via Serial Monitor
    espSerial.begin(9600);    // Set ESP software serial baud rate

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected to WiFi!");

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
    if (espSerial.available()) {
        String receivedMessage = espSerial.readStringUntil('\n'); // Read data from Arduino
        receivedMessage.trim();

        if (receivedMessage.length() > 0) {
            Serial.println("Received from Arduino: " + receivedMessage);
            if (Firebase.setString(firebaseData, "/data/message", receivedMessage)) {
                Serial.println("Data sent to Firebase: " + receivedMessage);
            } else {
                Serial.println("Firebase Error: " + firebaseData.errorReason());
            }
        }
    }
}
