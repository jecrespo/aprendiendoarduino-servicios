/*
   Ejemplo para ESP8266
*/

#include <ESP8266WiFi.h>

const char* ssid     = "AndroidAP4628";
const char* password = "esp8266wifi";

char url[] = "www.aprendiendoarduino.com";

WiFiClient client;

String webString = "";
String nombre = "";
String mensaje = "";

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  String webString = "";
  String nombre = "";
  String mensaje = "";

  Serial.println("Manda un mensaje al servidor.");
  Serial.println("Introduce Nombre:");
  while (Serial.available() == 0) {
  }
  do {
    char caracter_leido = Serial.read();
    if (caracter_leido == ' ') caracter_leido = '_';
    if (caracter_leido == '\r') continue;
    if (caracter_leido == '\n') continue;
    nombre += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);
  Serial.println(nombre);

  Serial.println("Introduce Mensaje:");
  while (Serial.available() == 0) {
  }
  do {
    char caracter_leido = Serial.read();
    if (caracter_leido == ' ') caracter_leido = '%20';
    if (caracter_leido == '!') caracter_ledio = '%21';
    if (caracter_leido == '\r') continue;
    if (caracter_leido == '\n') continue;
    mensaje += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);
  Serial.println(mensaje);

  grabaDatos(nombre, mensaje);
  delay(200);

  while (client.available() == 0) {
  }

  if (client.available()) {
    Serial.println("Respuesta del Servidor---->");
    while (client.available()) {
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);
    if (webString.indexOf("GRABADOS") >= 0) Serial.println("Datos guardados correctamente");
    else Serial.println("Error al guardar los datos");

    client.stop();

  }
}

void grabaDatos(String nombre, String mensaje) {
  Serial.println("enviando mensaje... ");

  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/mensajes/grabaMensajes.php?nombre=");
    client.print(nombre);
    client.print("&mensaje=");
    client.print(mensaje);
    client.println(" HTTP/1.1");
    client.println("Host: www.aprendiendoarduino.com");
    client.println("Connection: close");
    client.println();
    Serial.print("GET /servicios/mensajes/grabaMensajes.php?nombre=");
    Serial.print(nombre);
    Serial.print("&mensaje=");
    Serial.println(mensaje);
  }
  else {
    Serial.println("connection failed");
  }
}
