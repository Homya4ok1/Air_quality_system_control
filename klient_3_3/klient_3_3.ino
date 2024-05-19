#include <WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "SparkFun_SCD4x_Arduino_Library.h"  // Підключення бібліотеки для сенсора SCD41

WiFiClient client;  // Клієнт для підключення до базової станції
SCD4x airSensor;    // Об'єкт для сенсора SCD41

void sleep();
void Charge();
void led(int x, int a);

const char* ssid = "MyESP32AP";        // Назва мережі (SSID) для підключення до базової станції
const char* password = "password123";  // Пароль для підключення до базової станції
const char* serverIP = "192.168.4.1";  // IP-адреса базової станції

// Пін для першого світлодіода стан підключення
const int ledPin1 = 2;  //esp32c pin2; esp32s pin3; wroom 27 

// Пін для другого світлодіода контроль СО2
const int ledPin2 = 3;  //esp32c pin3; esp32s pin4; wroom 26

// Пін для третього світлодіода контроль стану зарядки
const int ledPin3 = 6;  //esp32c pin6; esp32s pin4; wroom 33

const long receivedChar = 0;
const int ChargePin = 1;  //esp32c pin1; esp32s pin34; wroom 36
float valC02 = 0;   //esp32c 50; esp32s 100
float valTemp = 0;  //esp32c 400; esp32s 200
float valHum = 0;   //esp32c 100; esp32s 300
float name = 1;  //назва пристрою esp32c 2; esp32s 1

int ChargeValue = 0;
int ChargeValue2 = 0;
bool flag = 0;
bool flag1 = 0; // led1 normal 
bool flag2 = 0; // led2 bed co2, 
bool flag3 = 0; // led3 bed lvl charge
int count2 = 0;  //
int count3 = 0;
int ChargeValue3 = 0;
unsigned long lastEventTime = 0;
//onst int WINDOW_SIZE = 20;  // Розмір вікна для середнього значення

// Оголошуємо змінну для зберігання інтервалу заміру заряду акумулятора
const unsigned long eventInterval =  60000;  // 1 хвилинa * 60 секунд * 1000 мілісекунд

//int readings[WINDOW_SIZE];  // Масив для зберігання останніх значень
//int index1 = 0;             // Індекс для зберігання поточного значення в масиві


void setup() {
  Serial.begin(115200);
  Wire.begin();

  //set the resolution to 12 bits(0 - 4096), 10(1024)
  analogReadResolution(10);
  setCpuFrequencyMhz(80);
  pinMode(ledPin1, OUTPUT);     // Налаштування піну для першого світлодіода
  pinMode(ledPin2, OUTPUT);     // Налаштування піну для другого світлодіода
  pinMode(ledPin3, OUTPUT); 
  airSensor.enableDebugging();  // Uncomment this line to get helpful debug messages on Serial

  // Підключення до мережі Wi-Fi базової станції
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Перевірити підключення до Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    led(1000, 1);
    sleep();
    delay(1000);
  }

  Serial.println("");
  Serial.println("WiFi connected");

  airSensor.begin();  // Ініціалізація сенсора SCD41


  //By default, the SCD4x has data ready every five seconds.
  //We can enable low power operation and receive a reading every ~30 seconds

  //But first, we need to stop periodic measurements otherwise startLowPowerPeriodicMeasurement will fail
  if (airSensor.stopPeriodicMeasurement() == true) {
    Serial.println(F("Periodic measurement is disabled!"));
  } 
  /*
  //Now we can enable low power periodic measurements
  if (airSensor.startLowPowerPeriodicMeasurement() == true) {
    Serial.println(F("Low power mode enabled!"));
  }*/

  //Now we can call .begin and set skipStopPeriodicMeasurements to true
  if (airSensor.begin(true, true, true) == false)
  //measBegin_________/     |     |
  //autoCalibrate__________/      |
  //skipStopPeriodicMeasurements_/
  {
    Serial.println(F("Sensor did not begin correctly. Please check wiring. Freezing..."));
    while (1)
      ;
  }
  //The SCD4x has data ready every thirty seconds
  //There is no getAmbientPressure command
  bool success = airSensor.setAmbientPressure(101306);  // установка атмосферного тиску 98700 Pascals
  if (success) {
    Serial.println(F("setAmbientPressure was successful"));
  }

  airSensor.persistSettings();  // Uncomment this line to store the sensor settings in EEPROM
  char serialNumber[13];        // The serial number is 48-bits. We need 12 bytes plus one extra to store it as ASCII Hex
}

void loop() {
  sleep();
  if (client.connect(serverIP, 75)) {

    // Serial.println("Connected to server");
    float values[5] = { name, valC02, valTemp, valHum, ChargeValue };  

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
    delay(40);  // Затримка перед наступною відправкою
    // Перевіряємо, чи минув достатній час з моменту останньої події
    unsigned long currentTime = millis();
    if (flag == 0 || currentTime - lastEventTime >= eventInterval) {
      Charge();
      // Оновлюємо час останньої події
      lastEventTime = currentTime;
      flag = 1;
    }
    led(6000, 1);  //індикація нормальнорго стану системи
  } else {
    Serial.println("Connection Failed");
    led(200, 1);  // індикація відсутності підключення

                   // delay(200);
    return;
  }


  // Отримання даних від сенсора SCD41
  if (airSensor.readMeasurement()) {

    valC02 = airSensor.getCO2();
    valTemp = airSensor.getTemperature();
    valHum = airSensor.getHumidity();
    // Отримання значень CO2, температури та вологості з сенсора
    Serial.println();

    Serial.print(F("CO2(ppm):"));
    Serial.print(airSensor.getCO2());

    Serial.print(F("\tTemperature(C):"));
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(F("\tHumidity(%RH):"));
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();


    // Перевірка перевищення показників датчика
    if (valC02 > 1600) {
      digitalWrite(ledPin2, HIGH);  // Ввімкнення другого світлодіода
    } else {
      digitalWrite(ledPin2, LOW);  // Вимкнення другого світлодіода
    }
  } else
    Serial.print(F("."));
}
// обробник подій  індикація світлодіодна
void led(int x, int a) {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= x) {
    previousMillis = currentMillis;
    switch (a) {
      case 1:
        flag1 = !flag1;
        if (flag1 == 1) {
          digitalWrite(ledPin1, HIGH);  // Увімкнення першого світлодіода
        } else {
          digitalWrite(ledPin1, LOW);  // Вимкнення першого світлодіода
        }
        break;
      case 2:
        flag2 = !flag2;
        if (flag2 == 1) {
          digitalWrite(ledPin2, HIGH);  // Увімкнення другого світлодіода
        } else {
          digitalWrite(ledPin2, LOW);  //
        }
        break;
        case 3:
        flag3 = !flag3;
        if (flag3 == 1) {
          digitalWrite(ledPin3, HIGH);  // Увімкнення другого світлодіода
        } else {
          digitalWrite(ledPin3, LOW);  //
        }
        break;
      default:
        // Якщо вхідна команда не 1 або 2, не виконувати жодної дії
        break;
    }
  }
}


void Charge() {  // обробник заряду батареї

  ChargeValue2 = analogRead(ChargePin);
  ChargeValue = map(ChargeValue2, 2730/4, 4095/4, 0, 100);  //4095 -> 4.2V, 2730 -> 2.82V// 1023 - 814
  Serial.println();
  Serial.printf(" ADC analog value = %d\n", ChargeValue2);
  Serial.println(ChargeValue);

  if (ChargeValue <= 0) {  //від'ємні значення прирівнює до нуля
    ChargeValue = 0;
  }
  //перевірка стану зарядки
  if (ChargeValue <= 2734/4) {  // 4.2В = 4095, 2.82В = 2730
    led(200, 3);
  }
}


//обробник режиму енергозбереження, вмикається при відсутності підключення до мережі WIFI
void sleep() {
  // Перевірити підключення до Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    if (count2 == 40) {
      Serial.println("Wi-Fi not connected. Entering deep sleep...");
      esp_sleep_enable_timer_wakeup(30 * 1000000);  // 5 хвилин сну( 300 сек * 1000000)
      esp_deep_sleep_start();
    }
    count2++;
  }
}
