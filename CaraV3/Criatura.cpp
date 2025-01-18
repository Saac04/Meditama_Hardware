#include "Criatura.h"
#include "xbm.h"
/*#include <M5Stack.h>  // Librería específica del hardware
#include <Arduino.h>  // Librería de Arduino para delay()*/

// Constructor de la clase
Criatura::Criatura() {}

// Inicializar la felicidad predeterminada
void Criatura::iniciar() {
    felicidad = 4;  // Nivel inicial de felicidad (máxima)
}

// Obtener el nivel actual de felicidad
int Criatura::getFelicidad() {
    return felicidad;
}

// Establecer un nuevo nivel de felicidad
void Criatura::setFelicidad(int felicidad_nueva) {
    felicidad = felicidad_nueva;
}

// Incrementar felicidad si no está en el nivel máximo
void Criatura::aumentarFelicidad() {
    if (felicidad < 4) {
        felicidad++;
    }
}

// Reducir felicidad si no está en el nivel mínimo
void Criatura::disminuirFelicidad() {
    if (felicidad > 1) {
        felicidad--;
    }
}
/*
// Mostrar una animación de parpadeo
void Criatura::parpadear() {
    int indiceArray1 = (4 - felicidad) * 2;      // Bitmap "abierto"
    int indiceArray2 = (4 - felicidad) * 2 + 1; // Bitmap "cerrado"

    // Dibujar la animación en la pantalla
    const unsigned char* bitmap1 = arrayDeArrays[indiceArray1];
    const unsigned char* bitmap2 = arrayDeArrays[indiceArray2];

    M5.Lcd.drawXBitmap(0, 0, bitmap1, ancho, alto, 0x0000);
    delay(150);
    M5.Lcd.fillScreen(0xFFFF);
    M5.Lcd.drawXBitmap(0, 0, bitmap2, ancho, alto, 0x0000);
    delay(200);
    M5.Lcd.fillScreen(0xFFFF);
    M5.Lcd.drawXBitmap(0, 0, bitmap1, ancho, alto, 0x0000);
}

// Mostrar la cara correspondiente al nivel actual de felicidad
void Criatura::mostrarCara() {
    int indiceArray = (4 - felicidad) * 2;  // Obtener el bitmap adecuado
    const unsigned char* bitmap = arrayDeArrays[indiceArray];
    M5.Lcd.fillScreen(0xFFFF);
    M5.Lcd.drawXBitmap(0, 0, bitmap, ancho, alto, 0x0000);
}
*/