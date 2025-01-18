#ifndef CLASEUDP_H
#define CLASEUDP_H

#include <WiFi.h>
#include <AsyncUDP.h>
#include <TimeLib.h>
#include <Arduino.h>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>

using namespace std;

class claseUdp {
private:
    char* ssid;
    char* password;

    int canal;
    boolean rec = 0;
    char texto[20];

    int ultimoIntRecibido;
    double ultimoDoubleRecibido;
    string ultimoStringRecibido;

    AsyncUDP udp;

    template <typename T>
    const char* convertirACadena(T valor);

public:
    void declararWifiSSID_Y_Contrasenya(char* nueva_ssid, char* nueva_password);
    void declararCanal(int nuevo_canal);
    void setupServer();
    void setupCliente();
    void enviarIntACliente(int data);
    void enviarDoubleACliente(double data);
    void enviarStringACliente(string data);
    String recibirData();
};

#endif
