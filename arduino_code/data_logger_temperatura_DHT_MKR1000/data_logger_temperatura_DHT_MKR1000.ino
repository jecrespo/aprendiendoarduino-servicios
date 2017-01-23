/*
  Sketch para Arduino MKR1000
  Sonda de temperatura y humedad DHT22
*/

#include <SPI.h>
#include <WiFi101.h>
#include <DHT.h>
#include <DHT_U.h>
#include "Timer.h"

#define NUM_ARDUINO 4	//Sustituir X por el numero de Arduino correcto
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN 7

char ssid[] = "AndroidAP4628"; //  your network SSID (name)
char pass[] = "esp8266wifi";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char url[] = "www.aprendiendoarduino.com";

WiFiClient client;
WiFiClient client2;

Timer t;
DHT sondaT(DHTPIN, DHTTYPE);

String webString = "";

void setup()
{
  sondaT.begin();
  Serial.begin(9600);
  delay(2000);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

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

  float h = sondaT.readHumidity();
  // Read temperature as Celsius (the default)
  float t = sondaT.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperatura Leida: ");
  Serial.println(t);
  Serial.print("Humedad Leida: ");
  Serial.println(h);

  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/datos/grabaDatos.php?arduino=" + (String)NUM_ARDUINO + "&dato=");
    client.print(t);
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
    client2.print(h);
    client2.println(" HTTP/1.1");
    client2.println("Host: www.aprendiendoarduino.com");
    client2.println("Connection: close");
    client2.println();
  }
  else {
    Serial.println("connection failed");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
