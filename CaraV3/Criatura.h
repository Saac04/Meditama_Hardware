#ifndef CRIATURA_H
#define CRIATURA_H

#include <string>
using namespace std;

// Clase que representa a la criatura en la pantalla
class Criatura {
private:
    int felicidad;  // Nivel de felicidad de la criatura (1-4)

public:
    Criatura();  // Constructor
    void iniciar();  // Inicializar la felicidad predeterminada
    int getFelicidad();  // Obtener el nivel de felicidad actual
    void setFelicidad(int felicidad_nueva);  // Establecer un nivel específico de felicidad
    void aumentarFelicidad();  // Incrementar felicidad
    void disminuirFelicidad();  // Reducir felicidad
    //void parpadear();  // Animación de parpadeo
    //void mostrarCara();  // Mostrar la cara correspondiente al nivel de felicidad
};

#endif // CRIATURA_H
