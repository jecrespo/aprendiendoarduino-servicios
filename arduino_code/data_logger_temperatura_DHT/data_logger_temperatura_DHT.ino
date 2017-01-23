/*
  Sketch para Arduino Mega con Ethernet Shield 2
  Sonda de temperatura y humedad DHT22
  Display LCD https://www.sparkfun.com/datasheets/LCD/SerLCD_V2_5.PDF
*/

#include <Ethernet2.h>
#include <SPI.h>
#include <dht.h>
#include "Timer.h"

#define NUM_ARDUINO 2	//Sustituir X por el numero de Arduino correcto
#define DHT22_PIN 7

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x70, 0xCC};	//Sustituir YY por el numero de MAC correcto

byte ip[] = {
  10, 22, 72, 31
};
byte DNS[] = {
  8, 8, 8, 8
};
byte gateway[] = {
  10, 22, 72, 1
};
byte subnet[] = {
  255, 255, 255, 0
};
char url[] = "www.aprendiendoarduino.com";

EthernetClient client;
EthernetClient client2;
Timer t;
dht sondaT;

String webString = "";

void setup()
{
  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Iniciando datalogger...");
  Serial1.write(254); // move cursor to beginning of first line
  Serial1.write(128);
  Serial1.println("Iniciando...");
  delay(1000);
  t.every(5000, grabaDatos);
}

void loop()
{
  webString = "";
  t.update();
  if (client.available()) {
    Serial.println("Respuesta del Servidor---->");
    while (client.available()) {
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);
    if (webString.indexOf("GRABADOS") > 0) Serial.println("Datos guardados correctamente");
    else Serial.println("Error al guardar los datos");

    client.stop();
  }
  
  if (client2.available()) {
    Serial.println("Respuesta del Servidor---->");
    while (client2.available()) {
      char c = client2.read();
      webString += c;
    }
    Serial.println(webString);
    if (webString.indexOf("GRABADOS") > 0) Serial.println("Datos guardados correctamente");
    else Serial.println("Error al guardar los datos");

    client2.stop();
  }
}

void grabaDatos() {
  Serial.println("leyendo temperatura... ");

  int chk = sondaT.read22(DHT22_PIN);

  if (chk == DHTLIB_OK) {

    Serial.print("Temperatura Leida: ");
    Serial.println(sondaT.temperature);
    Serial.print("Humedad Leida: ");
    Serial.println(sondaT.humidity);

    Serial1.write(254); // move cursor to beginning of first line
    Serial1.write(128);
    Serial1.write("                "); // clear display
    Serial1.write("                ");

    Serial1.write(254); // cursor to first line
    Serial1.write(128);
    Serial1.print("Temp: ");
    Serial1.print(sondaT.temperature);
    Serial1.write(254); // cursor to second line
    Serial1.write(192);
    Serial1.print("Hum: ");
    Serial1.print(sondaT.humidity);

    Serial.println("connecting to server...");
    if (client.connect(url, 80)) {
      Serial.println("connected");
      client.print("GET /servicios/datos/grabaDatos.php?arduino=" + (String)NUM_ARDUINO + "&dato=");
      client.print(sondaT.temperature);
      client.println(" HTTP/1.1");
      client.println("Host: www.aprendiendoarduino.com");
      client.println("Connection: close");
      client.println();
    }
    else {
      Serial.println("connection failed");
    }

    if (client2.connect(url, 80)) {
      int ard = (int)NUM_ARDUINO + 1;
      Serial.println("connected");
      client2.print("GET /servicios/datos/grabaDatos.php?arduino=" + (String)ard + "&dato=");
      client2.print(sondaT.humidity);
      client2.println(" HTTP/1.1");
      client2.println("Host: www.aprendiendoarduino.com");
      client2.println("Connection: close");
      client2.println();
    }
    else {
      Serial.println("connection failed");
    }
  }
  else {
    Serial.println("Error sonda: ");
    Serial.println(chk);
  }
}
