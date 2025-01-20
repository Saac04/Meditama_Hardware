#include "claseWifi.h"

// Asignar credenciales WiFi
void  claseWifi::declararWifiSSID_Y_Contrasenya(const char* nueva_ssid, const char* nueva_password) {
    ssid = nueva_ssid;
    password = nueva_password;
}


// Inicializar el servidor UDP
void claseWifi::setUpWifi() {

    // Conectar a WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Verificar conexión exitosa
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Falló");
        Serial.println("Reintentnado");
        setUpWifi();  // Bucle infinito en caso de falla
    }
    Serial.println("Se conecto al wifi");
}


IPAddress claseWifi::getIp(){
  return WiFi.localIP();
}
