#include "claseUdp.h"

// Configurar el canal UDP
void claseUdp::declararCanal(int nuevo_canal) {
    canal = nuevo_canal;
}

// Inicializar el servidor UDP
void claseUdp::setupServer() {
    // Iniciar escucha UDP en el canal especificado
    if (udp.listen(canal)) {
        Serial.print("Escuchando UDP en IP: ");
        Serial.println(wifi.getIp());

        // Callback para manejar paquetes entrantes
        udp.onPacket([this](AsyncUDPPacket packet) {
            // Convertir los datos recibidos a String y almacenarlos
            ultimoMensajeRecibido = String((char*)packet.data(), packet.length());
            Serial.println("Mensaje recibido: " + ultimoMensajeRecibido);
        });
    } else {
        Serial.println("Error al iniciar el servidor UDP");
    }
}


// Inicializar el cliente UDP
void claseUdp::setupCliente() {

    if (udp.listen(canal)) {
        Serial.print("Escuchando UDP en IP: ");
        Serial.println(wifi.getIp());

        udp.onPacket([this](AsyncUDPPacket packet) {
            // Copiar los datos recibidos al buffer
            strncpy(texto, (char*)packet.data(), sizeof(texto) - 1);
            texto[sizeof(texto) - 1] = '\0';  // Asegurarse de que la cadena esté terminada en nulo
            rec = true;  // Marcar como recibido
        });
    }
}

// Enviar un entero al cliente
void claseUdp::enviarIntACliente(int data) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", data);
    udp.broadcastTo(buffer, canal);  // Enviar vía UDP
}

// Enviar un double al cliente
void claseUdp::enviarDoubleACliente(double data) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.6f", data);  // Convertir a cadena
    udp.broadcastTo(buffer, canal);  // Enviar vía UDP
}


// Enviar un string al cliente
// Enviar un string al cliente
void claseUdp::enviarStringACliente(const std::string& data) {
    udp.broadcastTo(data.c_str(), canal);  // Enviar el string directamente como cadena C
}

String claseUdp::recibirData() {
    String temp = ultimoMensajeRecibido;
    ultimoMensajeRecibido = ""; // Limpiar después de leer
    return temp;
}


