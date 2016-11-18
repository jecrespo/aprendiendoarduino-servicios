#include <Ethernet.h>
#include <SPI.h>

#define PIN "0000"

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11
};
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
String webString = "";
String telefono = "";
String mensaje = "";

void setup()
{
  Ethernet.begin(mac, ip, DNS, gateway, subnet);
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  String webString = "";
  String telefono = "";
  String mensaje = "";

  Serial.println("Manda un SMS en caso de Alerta.");
  Serial.println("Introduce Telefono:");
  while (Serial.available() == 0) {
  }
  do {
    char caracter_leido = Serial.read();
    if (caracter_leido == ' ') continue;
    if (caracter_leido == '\r') continue;
    if (caracter_leido == '\n') continue;
    telefono += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);
  Serial.println(telefono);

  Serial.println("Introduce Mensaje:");
  while (Serial.available() == 0) {
  }
  do {
    char caracter_leido = Serial.read();
    if (caracter_leido == ' ') caracter_leido = '-';
    if (caracter_leido == '\r') continue;
    if (caracter_leido == '\n') continue;
    mensaje += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);
  Serial.println(mensaje);

  grabaDatos(telefono, mensaje);
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

void grabaDatos(String telefono, String mensaje) {
  Serial.println("enviando mensaje... ");

  Serial.println("connecting to server...");
  if (client.connect(url, 80)) {
    Serial.println("connected");
    client.print("GET /servicios/SMS/saveSMS.php?telefono=");
    client.print(telefono);
    client.print("&mensaje=");
    client.print(mensaje);
    client.print("&pin=");
    client.print((String)PIN);
    client.println(" HTTP/1.1");
    client.println("Host: www.aprendiendoarduino.com");
    client.println("Connection: close");
    client.println();
    Serial.print("GET /servicios/mensajes/grabaMensajes.php?telefono=");
    Serial.print(telefono);
    Serial.print("&mensaje=");
    Serial.println(mensaje);
  }
  else {
    Serial.println("connection failed");
  }
}
