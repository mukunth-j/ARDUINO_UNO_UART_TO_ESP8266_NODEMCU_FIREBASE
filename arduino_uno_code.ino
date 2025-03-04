#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6);  // RX = 5, TX = 6

void setup() {
    Serial.begin(9600);      // Debugging via Serial Monitor
    espSerial.begin(9600);   // Communication with ESP8266
}

void loop() {
    if (Serial.available()) {
        String message = Serial.readStringUntil('\n'); // Read user input
        message.trim();
        if (message.length() > 0) {
            espSerial.println(message); // Send data to ESP8266
            Serial.println("Sent to ESP8266: " + message);
        }
    }
}
