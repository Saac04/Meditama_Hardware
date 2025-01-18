#include "claseUdp.h"

template <typename T>
const char* claseUdp::convertirACadena(T valor) {
    ostringstream stream;
    stream << valor;
    char* resultado = strdup(stream.str().c_str());
    return resultado;
}

void claseUdp::declararWifiSSID_Y_Contrasenya(char* nueva_ssid, char* nueva_password) {
    ssid = nueva_ssid;
    password = nueva_password;
}

void claseUdp::declararCanal(int nuevo_canal) {
    canal = nuevo_canal;
}

void claseUdp::setupServer() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while (1) {
            delay(1000);
        }
    }

    if (udp.listen(canal)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.write(packet.data(), packet.length());
            Serial.println();
        });
    }
}

void claseUdp::setupCliente() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while (1) {
            delay(1000);
        }
    }

    if (udp.listen(canal)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());

        udp.onPacket([this](AsyncUDPPacket packet) {
            int i = 20;
            while (i--) {
                texto[i] = packet.data()[i];
            }
            rec = 1;
        });
    }
}

void claseUdp::enviarIntACliente(int data) {
    const char* new_data = convertirACadena(data);
    udp.broadcastTo(new_data, canal);
}

void claseUdp::enviarDoubleACliente(double data) {
    const char* new_data = convertirACadena(data);
    udp.broadcastTo(new_data, canal);
}

void claseUdp::enviarStringACliente(string data) {
    const char* new_data = convertirACadena(data);
    udp.broadcastTo(new_data, canal);
}

String claseUdp::recibirData() {
    if (rec) {
        rec = 0;
        udp.broadcastTo("Recibido", canal);
        Serial.println(texto);
        return texto;
    }
    return "mensaje no recibido";
}
