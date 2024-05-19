//esp32c3 library VALTRACK+V4_VTS_ESP32C3


#include <WiFi.h>
#include <ArduinoJson.h>
WiFiClient client;  // Клієнт для підключення до базової станції

const char* ssid = "MyESP32AP";        // Назва мережі (SSID) для підключення до базової станції
const char* password = "password123";  // Пароль для підключення до базової станції
const char* serverIP = "192.168.4.1";  // IP-адреса базової станції
const int serverport = 75;
float valC02 = 500.0;  //esp32c 50; esp32s 100
float valTemp = 35.0;  //esp32c 400; esp32s 200
float valHum = 40.0;   //esp32c 100; esp32s 300
float name = 2;        //назва пристрою esp32c3 2; esp32s 1
int ChargeValue = 40;


void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(80);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    // Перевірити підключення до Wi-Fi

    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {


  if (client.connect(serverIP, serverport)) {
    // Serial.println("Connected to server");
    float values[5] = { name, valC02, valTemp, valHum, ChargeValue };  // Приклад значень

    // Упаковка значень у JSON
    StaticJsonDocument<128> doc;
    doc["value1"] = values[0];
    doc["value2"] = values[1];
    doc["value3"] = values[2];
    doc["value4"] = values[3];
    doc["value5"] = values[4];


    // Серіалізація JSON до рядка
    String jsonString;
    serializeJson(doc, jsonString);
    // Відправлення JSON рядка на сервер
    client.println(jsonString);
    delay(100);
    Serial.println("ressive");
    Serial.println(jsonString);
  }
  Serial.print(F("."));
}
