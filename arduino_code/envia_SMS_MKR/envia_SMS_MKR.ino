/*
   Ejemplo para MKR1000
*/

#include <SPI.h>
#include <WiFi101.h>

#define PIN "0000"

char ssid[] = "AndroidAP4628"; //  your network SSID (name)
char pass[] = "esp8266wifi";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

char url[] = "www.aprendiendoarduino.com";

int status = WL_IDLE_STATUS;

WiFiClient client;

String webString = "";
String telefono = "";
String mensaje = "";

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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
