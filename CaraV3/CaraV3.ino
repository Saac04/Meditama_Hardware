#include <M5Stack.h>  // Librería específica del hardware
#include "xbm.h"      // Librería para las imágenes xbm
#include "Criatura.h" // Archivo de cabecera para la clase Criatura
#include "claseUdp.h" // Archivo de cabecera para la clase UDP
#include <string>
#include "MQTTHandler.h"
#include <ArduinoJson.h>  // Incluir la librería ArduinoJson
#include <analogWrite.h>
#include "claseWifi.h"

// Pines PWM para los colores de la tira LED
const int redPin = 16;    // cable marron
const int greenPin = 17; // cable amarillo
const int bluePin = 26;  // cable gris

// Credenciales WiFi
#define ssid "POCO_NSFW"  // SSID de la red WiFi
#define password "bromitanomas"  // Contraseña de la red WiFi


// Detalles del Broker MQTT
const char* mqtt_broker = "broker.hivemq.com"; // Dirección del broker MQTT
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32_Client";
const char* topic = "test/meditama";

// Instanciar el manejador MQTT
MQTTHandler mqttHandler(ssid, password, mqtt_broker, mqtt_port, mqtt_client_id);
// Objetos globales
Criatura criatura;  // Instancia de la clase Criatura
claseUdp conexion;  // Instancia de la clase UDP

int Red, Green, Blue;

// Función de callback para los mensajes recibidos
void onMessageReceived(const char* topic, const char* message) {
    Serial.println("Mensaje recibido:");
    Serial.println("Mensaje: " + String(message));

    
    // Crear un objeto para parsear el JSON usando DynamicJsonDocument
    DynamicJsonDocument doc(300);  // Usar DynamicJsonDocument con tamaño especificado
    
    // Deserializar el JSON
    DeserializationError error = deserializeJson(doc, message);

    // Verificar si hubo algún error al deserializar
    if (error) {
        Serial.print("Error al leer el JSON: ");
        Serial.println(error.f_str());
        return;
    }

    // Extraer los valores de RGB
    JsonObject rgb = doc["RGB"];
    
    Red = rgb["Red"];
    Green = rgb["Green"];
    Blue = rgb["Blue"];
  
    setColor(Red, Green, Blue);
    
}

claseWifi wifi;

void setup() {

  Serial.begin(115200);  // Inicializar comunicación serial
  M5.begin();            // Inicializar la pantalla M5Stack
  M5.Power.begin();
  M5.Lcd.fillScreen(TFT_WHITE);  // Pantalla en blanco
  criatura.iniciar();         // Inicializar la criatura con valores predeterminados
  criatura.mostrarCara();  

  wifi.declararWifiSSID_Y_Contrasenya(ssid, password);
  wifi.setUpWifi();

  conexion.declararCanal(9989);  // Configurar canal UDP
  conexion.setupServer(); 

  mqttHandler.connectMQTT();   
  mqttHandler.setCallback(onMessageReceived);
  mqttHandler.subscribe(topic);


  // Configurar los pines como salida
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  setColor(0, 0, 0);

}

int counter = 0;  // Contador global para controlar eventos periódicos

void loop() {
    mqttHandler.loop();
    M5.update();  // Actualizar los botones del 


    StaticJsonDocument<200> jsonDoc;
    char jsonPayload[100];

    // Hacer parpadear a la criatura cada 100 ciclos
    if (counter % 100 == 0) {
        criatura.parpadear();
    }

    // Incrementar felicidad si se presiona el botón A
    if (M5.BtnA.isPressed()) {
        criatura.aumentarFelicidad();
        criatura.mostrarCara();
        snprintf(jsonPayload, sizeof(jsonPayload), "{\"Estado_Animo\": %d}", criatura.getFelicidad());
        mqttHandler.sendData(topic, jsonPayload);
    }

    // Reducir felicidad si se presiona el botón B
    if (M5.BtnB.isPressed()) {
        criatura.disminuirFelicidad();
        criatura.mostrarCara();
        snprintf(jsonPayload, sizeof(jsonPayload), "{\"Estado_Animo\": %d}", criatura.getFelicidad());
        mqttHandler.sendData(topic, jsonPayload);
    }

    
    counter++;  // Incrementar contador
    
    delay(200);
    // Recibir datos vía UDP
    String informacion = conexion.recibirData();
    int numero = informacion.toInt();  // Convertir la información recibida a entero

    // Realizar acciones según el valor recibido
    if (numero == 4) {
        Serial.println("info 4");
        criatura.setFelicidad(4);
        criatura.mostrarCara();
    } else if (numero == 1) {
        Serial.println("info 1");
        criatura.setFelicidad(1);
        criatura.mostrarCara();
    } else if (numero == 2) {
        criatura.setFelicidad(2);
        criatura.mostrarCara();
    }


  
   
}

// Función para establecer el color
void setColor(int red, int green, int blue) {
  analogWrite(redPin, 256 - red);   // Controlar el brillo del rojo
  analogWrite(greenPin, 256 - green); // Controlar el brillo del verde
  analogWrite(bluePin, 256 - blue); // Controlar el brillo del azul
}
