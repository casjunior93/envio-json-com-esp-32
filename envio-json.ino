#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "Carlos";
const char* password = "";

String serverName = "https://httpbin.org/post";

int status = WL_IDLE_STATUS;
WiFiServer server(80);

int LED_BUILTIN = 2;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }

  Serial.println("Connected to the WiFi network");
}
void loop() {
  Serial.print("ESP32 received: ");
  digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000);
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(1000);

  String toSend;
  HTTPClient http;
  http.begin(serverName.c_str());
  http.addHeader("Content-Type", "application/json");

  toSend = "{\"sinals\":{\"dados\":{\"temepratura\":\"40\",\"luminosidade\":\"200\"}}}";

  int httpResponse = http.POST(toSend.c_str());


  if (httpResponse > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Servidor recebeu: ");    
    delay(100);
    Serial.print(http.getString());      
    delay(10000);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }

  http.end();
}
