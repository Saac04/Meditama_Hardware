#include "MQTTHandler.h"

// Initialize the static instance pointer
MQTTHandler* MQTTHandler::instance = nullptr;

MQTTHandler::MQTTHandler(const char* ssid, const char* password, const char* broker, int port, const char* clientId)
    : ssid(ssid), password(password), broker(broker), port(port), clientId(clientId), client(espClient) {
    instance = this; // Set the current instance
}

/*void MQTTHandler::connectWiFi() {
    Serial.print("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED ) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
}*/

void MQTTHandler::connectMQTT() {
    client.setServer(broker, port);
    client.setCallback(internalCallback);
    Serial.println(client.state());

    while (!client.connected()) {
        Serial.print("Connecting to MQTT broker...");
        if (client.connect(clientId)) {
            Serial.println("Connected");
        } else {
            Serial.print("Failed with state ");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void MQTTHandler::subscribe(const char* topic) {
    client.subscribe(topic);
    Serial.println("Subscribed to topic: " + String(topic));
}

void MQTTHandler::sendData(const char* topic, const char* payload) {
    client.publish(topic, payload);
    Serial.println("Published: " + String(payload) + " to topic: " + String(topic));
}

void MQTTHandler::loop() {
    client.loop();
}

void MQTTHandler::setCallback(std::function<void(const char* topic, const char* message)> callback) {
    userCallback = callback;
}

void MQTTHandler::internalCallback(char* topic, byte* payload, unsigned int length) {
    if (instance && instance->userCallback) {
        // Convert payload to a C-style string
        char message[length + 1];
        memcpy(message, payload, length);
        message[length] = '\0';

        // Call the user-defined callback
        instance->userCallback(topic, message);
    }
}
