#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

//#include <WiFi.h>
#include <PubSubClient.h>
#include <functional>
#include "claseWifi.h"

class MQTTHandler {
private:
    const char* ssid;           // Wi-Fi SSID
    const char* password;       // Wi-Fi password
    const char* broker;         // MQTT broker address
    int port;                   // MQTT broker port
    const char* clientId;       // MQTT client ID

    WiFiClient espClient;

    claseWifi wifi;

    PubSubClient client;
    static MQTTHandler* instance; // Pointer to the current instance

    // Callback function to handle incoming messages
    std::function<void(const char* topic, const char* message)> userCallback;

    // Internal callback to bridge the MQTT library and user-provided callback
    static void internalCallback(char* topic, byte* payload, unsigned int length);

public:
    // Constructor
    MQTTHandler(const char* ssid, const char* password, const char* broker, int port, const char* clientId);

    // Set user-defined callback for received data
    void setCallback(std::function<void(const char* topic, const char* message)> callback);

    // Connect to Wi-Fi
    //void connectWiFi();

    // Connect to MQTT broker
    void connectMQTT();

    // Subscribe to a topic
    void subscribe(const char* topic);

    // Publish data to a topic
    void sendData(const char* topic, const char* payload);

    // Maintain MQTT connection
    void loop();
};

#endif // MQTTHANDLER_H
