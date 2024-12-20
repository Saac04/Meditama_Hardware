#ifndef CLASEUDP_H
#define CLASEUDP_H

#include <string>
#include "claseWifi.h"
#include <AsyncUDP.h>

// Declaración de la clase para manejar UDP
class claseUdp {
private:
    // Cambiado ssid y password a const char* porque los literales de cadena son inmutables en C++.
    const char* ssid;  
    const char* password;

    int canal;  // Puerto para la comunicación UDP
    bool rec = false;  // Booleano para indicar recepción de mensaje
    char texto[20];  // Buffer para datos recibidos

    AsyncUDP udp;
    claseWifi wifi;


    // Plantilla para convertir varios tipos de datos a una cadena
    template <typename T>
    void convertirACadena(T valor, char* buffer, size_t size);
    String ultimoMensajeRecibido; // Almacena el último mensaje recibido


public:
    // Parámetros actualizados para compatibilidad con const char*
    //void declararWifiSSID_Y_Contrasenya(const char* nueva_ssid, const char* nueva_password);
    void declararCanal(int nuevo_canal);
    void setupServer();
    void setupCliente();
    void enviarIntACliente(int data);
    void enviarDoubleACliente(double data);
    void enviarStringACliente(const std::string& data);  // Cambiado para usar std::string
    String recibirData();
};

#endif
