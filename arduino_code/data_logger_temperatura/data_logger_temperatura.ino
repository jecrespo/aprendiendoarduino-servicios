#include <Ethernet.h>
#include <SPI.h>
#include "Timer.h"

#define NUM_ARDUINO 5

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 
  10, 22, 72, 30 };
byte DNS[] = {
  8,8,8,8};
byte gateway[] = {
  10, 22, 72, 1};
byte subnet[] = {
  255,255,255,0};
char url[] = "www.aprendiendoarduino.com";

EthernetClient client;
Timer t;
String webString = "";

void setup()
{
  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  Serial.begin(9600);
  Serial.println("Iniciando datalogger...");
  delay(1000);
  t.every(5000,grabaDatos);
}

void loop()
{
  webString = "";
  t.update();
  if (client.available()) {
    Serial.println("Respuesta del Servidor---->");
    while (client.available()){
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);
    if (webString.indexOf("GRABADOS") > 0) Serial.println("Datos guardados correctamente");
    else Serial.println("Error al guardar los datos");
    
   client.stop();
  }
}

void grabaDatos(){
  Serial.println("leyendo temperatura... ");
  int sensorVal = analogRead(A0);
  float voltage = (sensorVal/1024.0)*5.0;
  float temperature = (voltage - 0.5)*100; //Sonda temperatura kit Arduino
  Serial.print("Temperatura Leida: ");
  Serial.println(temperature);
  
  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/datos/grabaDatos.php?arduino="+(String)NUM_ARDUINO+"&dato=");
    client.print(temperature);
    client.println(" HTTP/1.1");
    client.println("Host: www.aprendiendoarduino.com");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed");
  }
}
