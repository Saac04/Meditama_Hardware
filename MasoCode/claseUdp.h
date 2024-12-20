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
      const char* convertirACadena(T valor) {
        ostringstream stream;
        stream << valor;
        // Se necesita liberar la memoria después de obtener el puntero
        char* resultado = strdup(stream.str().c_str());
        return resultado;
      }

    public:

      void declararWifiSSID_Y_Contrasenya( char* nueva_ssid, char* nueva_password ){
          ssid = nueva_ssid;
          password = nueva_password;
      }

      void declararCanal (int nuevo_canal) {
          canal = nuevo_canal;
      }

      void setupServer() { 
          

        //setTime(10, 0, 0, 7, 10, 2018); 
        //hora minuto segundo dia mes año 
  
        WiFi.mode(WIFI_STA); 
        WiFi.begin(ssid, password); 
        if(WiFi.waitForConnectResult() != WL_CONNECTED) { 
            Serial.println("WiFiFailed"); 
              while(1) { delay(1000); } 
        }

        if(udp.listen(canal)) { 
            Serial.print("UDP ListeningonIP: ");
            Serial.println(WiFi.localIP());
            udp.onPacket([](AsyncUDPPacket packet) { 
                Serial.write(packet.data(), packet.length());
                Serial.println(); 
            }); 
        }

      }

      void setupCliente(){
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
            rec = 1; // Indica mensaje recibido
          });
        }
      }

      void enviarIntACliente(int data) {
        const char* new_data = convertirACadena(data);
        udp.broadcastTo(new_data, canal);
        //Serial.println()
      }

      void enviarDoubleACliente(double data) {
        const char* new_data = convertirACadena(data);
        udp.broadcastTo(new_data, canal);
      }

      void enviarStringACliente( string data ){
         //AsyncUDP udp;
          //char texto[] = data;
        const char* new_data = convertirACadena(data);
        udp.broadcastTo(new_data , canal);
      }

      String recibirData() {

        if (rec) {
          // Enviar broadcast
          rec = 0; // Mensaje procesado
          udp.broadcastTo("Recibido", canal); // Envia confirmación
          //udp.broadcastTo(texto, 1234); // Y dato recibido
          //hora = atol(texto); // Paso de texto a entero
          Serial.println(texto);
          //Serial.println(hora);
          return(texto);
        }

        return("mensaje no recibido");
      }

      /*void recibirIntDeCliente() {
        if (udp.listen(canal)){
          udp.onPacket([](AsyncUDPPacket packet) { 
            Serial.write(packet.data(), packet.length());
            Serial.println(); 
            int mensaje = static_cast<int>(packet.data());
            Serial.println(mensaje); 
          });
        }
      }*/

      /*void recibirDoubleDeCliente() {
        udp.listen(canal);
        udp.onPacket([](AsyncUDPPacket packet) {
          //ultimoDoubleRecibido = packet
          memcpy(&ultimoDoubleRecibido, packet.data(), sizeof(double));
        });
      }

      void recibirStringDeCliente() {
        udp.listen(canal);
        udp.onPacket([](AsyncUDPPacket packet) {
          ultimoStringRecibido = string(packet.data());
        });
      }*/




};

#endif 