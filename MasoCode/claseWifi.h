#ifndef CLASEWIFI_H
#define CLASEWIFI_H

#include <WiFi.h>

class claseWifi {
private:
    // Cambiado ssid y password a const char* porque los literales de cadena son inmutables en C++.
    const char* ssid;  
    const char* password;
public:
    // Parámetros actualizados para compatibilidad con const char*
    void declararWifiSSID_Y_Contrasenya(const char* nueva_ssid, const char* nueva_password);
    void setUpWifi();
    IPAddress getIp();
};

#endif
