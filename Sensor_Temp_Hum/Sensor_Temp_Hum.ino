#include "DHT.h"
#include "claseUdp.h" // Archivo de cabecera para la clase UDP
#include "claseWifi.h"
// Definir el pin de la ESP32 donde está conectado el DHT11
#define DHTPIN 16  // Pin GPIO 16

// Definir el tipo de sensor (DHT11)
#define DHTTYPE DHT11

#define ssid "POCO_NSFW"  // SSID de la red WiFi
#define password "bromitanomas"  // Contraseña de la red WiFi

claseUdp conexion;  // Instancia de la clase UDP
claseWifi wifi;

// Crear un objeto DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializar el monitor serie
  Serial.begin(9600);
  dht.begin();
  Serial.println("Sensor DHT11 iniciado...");

  wifi.declararWifiSSID_Y_Contrasenya(ssid, password);
  wifi.setUpWifi();

  conexion.declararCanal(9989);  // Configurar canal UDP
  conexion.setupCliente(); 
}

void loop() {
  // Esperar 2 segundos entre lecturas

  // Leer la humedad
  float humedad = dht.readHumidity();
  
  // Leer la temperatura en grados Celsius
  float temperatura = dht.readTemperature();

  // Comprobar si las lecturas fallaron e imprimir un error si es necesario
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer del sensor DHT11");
    return;
  }

  // Imprimir los valores de temperatura y humedad en el monitor serie
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print(" %\t");
  const String hum = "humedad" + String(humedad);
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  const String temp = "temperatura"+ String(temperatura);

  conexion.enviarStringACliente(std::string(hum.c_str()));
  delay(500);
  conexion.enviarStringACliente(std::string(temp.c_str()));


  delay(10000);
}
