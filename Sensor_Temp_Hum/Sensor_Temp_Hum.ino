#include "DHT.h"

// Definir el pin de la ESP32 donde está conectado el DHT11
#define DHTPIN 16  // Pin GPIO 16

// Definir el tipo de sensor (DHT11)
#define DHTTYPE DHT11

// Definir los pines para los colores del LED bicolor
int redPin = 13;  // Pin para el color rojo
int greenPin = 14; // Pin para el color verde

// Definir el pin para el nuevo LED
int ledPin = 12; // Pin para el nuevo LED


// Crear un objeto DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializar el monitor serie
  Serial.begin(9600);
  

    // Configurar los pines del LED bicolor como salida
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  // Configurar el pin del nuevo LED como salida
  pinMode(ledPin, OUTPUT);
  // Inicializar el sensor DHT
  dht.begin();
  Serial.println("Sensor DHT11 iniciado...");
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
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Encender el color rojo en el LED bicolor
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);  // Asegurarse de que el verde esté apagado
  digitalWrite(ledPin, HIGH);   // Encender el LED adicional
  delay(1000); // Mantener el estado por 1 segundo
  
  // Encender el color verde en el LED bicolor
  digitalWrite(redPin, LOW);  // Apagar el rojo
  digitalWrite(greenPin, HIGH);
  digitalWrite(ledPin, LOW);   // Apagar el LED adicional
  delay(1000); // Mantener el estado por 1 segundo
  
  // Encender ambos colores en el LED bicolor
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(ledPin, HIGH);   // Encender el LED adicional
  delay(1000); // Mantener el estado por 1 segundo
  
  // Apagar ambos colores en el LED bicolor y el LED adicional
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(ledPin, LOW);   // Apagar el LED adicional
  delay(1000);
  
}
