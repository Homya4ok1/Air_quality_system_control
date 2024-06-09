
#include <SPI.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Tigra.h"
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>  // Core graphics library
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

//used pins
#define TFT_CS 17     //diplay chip select 17
#define TFT_DC 16     //display d/c 16
#define TFT_MOSI 23   //diplay MOSI 23
#define TFT_CLK 18    //display clock 18
#define TFT_RST 4     //display reset 4
#define TFT_MISO 19   //display MISO 19
#define TFT_LED 26    //display background LED 26
#define TOUCH_CS 5    //touch screen chip select 5
#define TOUCH_IRQ 15  //touch screen interrupt 15
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//Output variable to GPIO pins
#define PIN_LED1 32  // AUTO/HAND
#define PIN_LED2 33  // AIR CONTROL
#define PIN_LED3 25  // CONDSTSONER

#define TEMPERATURE_MIN 18
#define TEMPERATURE_MAX 30

// Початкове значення температури слайдера на екрані пристрою
int temperature = 20;
const int perioddelay = 100;  // значення часу до якого викликається disconnect
//#define SPI_FREQUENCY 24000000  // Задаємо частоту SPI, наприклад, 1 МГц

const char* ssid = "MyESP32AP";  // Назва мережі (SSID) для підключення до базової станції
const char* password = "password123";
const int serverPort = 75;
const int serverPortwEB = 80;
// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;
//////////////////////////////////////////////
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3900
#define TS_MINY 3850
#define TS_MAXX 250
#define TS_MAXY 250

IPAddress Actual_IP;
//////////////////////////////////

// Variable to store the HTTP request
String header;
TS_Point p;
int levelTemp = 20;  // змінна значення слайдеру (0 - 255)
int valslayder = 0;
bool LED1 = false, LED2 = false, LED3 = false;
bool qw = 0;

uint32_t SensorUpdate = 0;
int airtemp = 20;

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];
// just some buffer holder for char operations
char buf[32];
unsigned long previousMillis2 = 0;    // Попередній час
const unsigned long interval = 3000;  // Інтервал підсвітки екрану в мілісекундах (30 секунд)
int brightness = 255;                 // Початкова яскравість
// Current time
unsigned long currentTime = millis();

// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
//const long timeoutTime = 5000;

const int NUM_DEVICES = 6;  // Кількість пристроїв 5 + 0
const int DATA_SIZE = 5;    // Розмір масиву даних

const int heightButton = 50;  //висота
const int widthButton = 70;   //ширина
float valavrco2 = 0;
float valavrTemp = 0;
float valavrhum = 0;
float avrhum = 0;
float avrTemp = 0;
float dataFromDevices[NUM_DEVICES][(DATA_SIZE - 2)];  // двомірний масив dataFromDevices зберігає 5 строк в кожній по 3 ряди даних



const int posX_disc = 2;
const int posY_disc = 7;
const int positionX_Co2 = 126;
const int positionY_Co2 = 30;
const int positionX_Hum = 179;
const int positionY_Hum = 30;
const int positionX_Temp = 231;
const int positionY_Temp = 30;
int positionX_Charg1 = 284;  //positionX_Charg1 = positionX_Charg 1 батарея
int positionY_Charg1 = 5;
const int positionX_Charg = 284;
const int positionY_Charg = 5;
const int positionX_Charg2 = 284;  //2 батарея
const int positionY_Charg2 = 15;
const int positionX_Charg3 = 284;  //3 батарея
const int positionY_Charg3 = 25;
const int positionX_Charg4 = 284;  //4 бвтарея
const int positionY_Charg4 = 35;
const int positionX_Charg5 = 284;  //5 батарея
const int positionY_Charg5 = 45;

int flag1 = 0;  // флаг обробки підключень wifi
int flag2 = 0;  //
bool flag3 = 0;
bool flag4 = 0;  //flag setting button
bool flag5 = 0;

int countbut1 = 0;  // обробник натиску кнопки автоматичного режиму
int countbut2 = 0;  // обробник натиску кнопки Air control
int countbut3 = 0;  // обробник натиску кнопки Conditioner
int countbut4 = 0;  // обробник натиску кнопки налаштування
int r = 0;
int val_count = 0;  //кількість підключених кліентів
int count2 = 0;     //підрахунок з'єднання Wifi клієнтів
int count7 = 0;     //підрахунок
int count5 = 0;     // лічільник сброса даних масиву clients_name[ ]
int count6 = 0;     // лічільник кількості підключених клієнтів
int name = 0;
int avrco2 = 0;
int charge = 0;
int devicesReceivedData = 0;
int clients_name[6][2];      // [ім'я клієнта] [рівень заряду]
int e[NUM_DEVICES] = { 0 };  //кількість періодів пропусків сигналу передачи каналів по кожному клієнту
int co2 = 0;
int arrowY = 0;
int arrowY2 = 0;
int arrowY3 = 0;

//WiFiClient webclient;
WiFiClient clients[NUM_DEVICES];
WiFiServer server(serverPort);
WebServer server1(serverPortwEB);


void led();
void rectangle();
void rectangle2();
void valCharge();
void numbers();
void timer();
void zeroData();
void disconnect();
void tftprint();
void graf();
void buttons();
void tochsk();
void body();
void webPage();
void UpdateSlider();
void ProcessButton_0();
void ProcessButton_1();
void ProcessButton_2();
void ProcessButton_3();
void SendWebsite();
void SendXML();
void printWifiStatus();
void automatic();
void drawUI();
void buttonset();

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);  //створення точки доступа
                                // WiFi.begin(ssid, password); // підключення до існуючої точки доступа
  //SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
  setCpuFrequencyMhz(270);

  // Ініціалізація дисплею  з деякими параметрами
  tft.begin();  // Ініціалізуємо дисплей з роздільною здатністю 240x320
  ts.begin();
  Serial.println("Touchscreen started.");
  Serial.print("tftx =");
  Serial.print(tft.width());
  Serial.print(" tfty =");
  Serial.println(tft.height());

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(TFT_LED, OUTPUT);

  // turn off led
  LED1 = false;
  LED2 = false;
  LED3 = false;
  digitalWrite(PIN_LED1, LED1);
  digitalWrite(PIN_LED2, LED2);
  digitalWrite(PIN_LED3, LED3);
  digitalWrite(TFT_LED, HIGH);

  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);

  server1.on("/", SendWebsite);
  server1.on("/xml", SendXML);
  server1.on("/UPDATE_SLIDER", UpdateSlider);
  server1.on("/BUTTON_0", ProcessButton_0);
  server1.on("/BUTTON_1", ProcessButton_1);
  server1.on("/BUTTON_2", ProcessButton_2);
  server1.on("/BUTTON_3", ProcessButton_3);  //перезагрузка есп

  tft.fillScreen(ILI9341_BLACK);  // Заповнення екрана чорним кольором
  // tft.setRotation(2);
  tft.setTextWrap(1);
  // Виведення тексту
  tft.setCursor(0, 0);  // Встановлення позиції курсора
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);  // Встановлення кольору тексту
  tft.setRotation(1);
  tft.setTextSize(1);                             // Встановлення розміру тексту
  tft.println("    air quality control system");  // Виведення тексту  tft.setRotation(2);
  delay(1000);
  tft.println("    developed by Valerii Dikhtiaruk");
  tft.println("    password password123");
  tft.print("    IP address: ");
  tft.println(WiFi.softAPIP());
  delay(3000);


  // Отримання IP-адреси точки доступу
  // Print IP address and start web server
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  server1.begin();
  printWifiStatus();
  server.begin();
}


void loop() {

  webPage();
  automatic();
  timer();
  zeroData();
  disconnect();
  if (flag4 == 0) {  //відключення оновлення в режимі налаштування

    tftprint();
    buttons();
  }
  body();
  tochsk();
  buttonset();
}


// функція виводу інформації на дисплей
void tftprint() {

  // Write to the display the Variable1 with left text alignment:
  rectangle(1);
  tft.setCursor(positionX_Co2, positionY_Co2);      // Set position (x,y)
  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);                               // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(avrco2, 0);

  rectangle(2);
  tft.setCursor(positionX_Temp, positionY_Temp);    // Set position (x,y)
  tft.setTextColor(ILI9341_ORANGE, ILI9341_BLACK);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);                               // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(avrTemp, 1);                          // Print a text or value

  rectangle(3);
  tft.setCursor(positionX_Hum, positionY_Hum);    // Set position (x,y)
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);                             // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(avrhum, 1);                         // Print a text or value

  if (name != 0) {
    valCharge();
    rectangle2();
    tft.setCursor(positionX_Charg1, positionY_Charg1);  // Set position (x,y)
    tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);     // Set color of text. First is the color of text and after is color of background
    tft.setTextSize(1);
    tft.print(name);
    tft.print(" ");
    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);  // Set color of text. First is the color of text and after is color of background
    tft.print(charge, 0);                          // Print a text or value
    tft.println("%");
  }
}

// обробка затримки роботи світлодіодів
void led(int x) {
  static unsigned long previousMillis = 0;



  if (millis() > previousMillis + x) {
    previousMillis = millis();

    flag3 = !flag3;
  }
  if (flag3 == 1) {
    tft.fillCircle(300, 220, 5, ILI9341_GREEN);  // Малюємо зелелний круг

  } else {
    tft.fillCircle(300, 220, 5, ILI9341_BLACK);  // Малюємо чорний круг
  }
}


// закриття порожніх значень параметрів
void rectangle(int x) {
  switch (x) {
    case 1:             //чорний квадрат для значення СО2
      if (avrco2 < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Co2 + 12), positionY_Co2, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (avrco2 < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Co2 + 24), positionY_Co2, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (avrco2 < 1000)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Co2 + 36), positionY_Co2, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      break;
    case 2:              //чорний квадрат для значення температури
      if (avrTemp < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Temp + 12), positionY_Temp, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (avrTemp < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Temp + 24), positionY_Temp, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      //if (avrTemp < 1000)  // If Variable1 is less than 100...
      // {
      // Fill the other digit with background color:
      //  tft.fillRect((positionX_Temp + 36), positionY_Temp, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      //}
      break;
    case 3:             //чорний квадрат для значення вологості
      if (avrhum < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Hum + 12), positionY_Hum, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (avrhum < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Hum + 24), positionY_Hum, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      // if (avrhum < 1000)  // If Variable1 is less than 100...
      // {
      // Fill the other digit with background color:
      //   tft.fillRect((positionX_Hum + 36), positionY_Hum, 12, 16, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      // }
      break;
    case 4:  //чорний квадрат для рівня заряду 1 батареї

      break;
    case 5:
      if (flag1 == 1 && flag2 == 0 && flag4 == 0)  //чорний квадрат для diskonect
      {
        // Fill the other digit with background color:
        // tft.fillRect((posX_disc + 40), posY_disc, 24, 14, ILI9341_BLACK);   // Draw filled rectangle (x,y,width,height,color)
        // tft.fillRect(posX_disc, (posY_disc + 20), 120, 14, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
        tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_BLACK);
        flag2 = 1;
      }

      break;
    default:
      // Якщо вхідна команда не 1 або 2, не виконувати жодної дії
      break;
  }
}
// обробка рівня заряду батареї
void valCharge() {
  switch (name) {
    case 1:
      positionX_Charg1 = positionX_Charg;
      positionY_Charg1 = positionY_Charg;

      break;
    case 2:
      positionX_Charg1 = positionX_Charg2;
      positionY_Charg1 = positionY_Charg2;

      break;
    case 3:
      positionX_Charg1 = positionX_Charg3;
      positionY_Charg1 = positionY_Charg3;

      break;
    case 4:
      positionX_Charg1 = positionX_Charg4;
      positionY_Charg1 = positionY_Charg4;

      break;
    case 5:
      positionX_Charg1 = positionX_Charg5;
      positionY_Charg1 = positionY_Charg5;

      break;
    default:
      // Якщо вхідна команда не 1 або 2, не виконувати жодної дії
      break;
  }
}
//закриття порожніх значень заряду батареї
void rectangle2() {
  switch (name) {
    case 0:
      tft.fillRect((positionX_Charg), positionY_Charg, 36, 8, ILI9341_BLACK);
      tft.fillRect((positionX_Charg2), positionY_Charg2, 36, 8, ILI9341_BLACK);
      tft.fillRect((positionX_Charg3), positionY_Charg3, 36, 8, ILI9341_BLACK);
      tft.fillRect((positionX_Charg4), positionY_Charg4, 36, 8, ILI9341_BLACK);
      tft.fillRect((positionX_Charg5), positionY_Charg5, 36, 8, ILI9341_BLACK);
      break;
    case 1:
      if (charge < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg + 18), positionY_Charg, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg + 24), positionY_Charg, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 1000)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg + 30), positionY_Charg, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      break;
    case 2:
      if (charge < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg2 + 18), positionY_Charg2, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg2 + 24), positionY_Charg2, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 1000)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg2 + 30), positionY_Charg2, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      break;
    case 3:
      if (charge < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg3 + 18), positionY_Charg3, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg3 + 24), positionY_Charg3, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 1000)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg3 + 30), positionY_Charg3, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      break;
    case 4:
      if (charge < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg4 + 18), positionY_Charg4, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg4 + 24), positionY_Charg4, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 1000)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg4 + 30), positionY_Charg4, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      break;
    case 5:
      if (charge < 10)  // If Variable1 is less than 10...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg5 + 18), positionY_Charg5, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 100)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg5 + 24), positionY_Charg5, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      if (charge < 1000)  // If Variable1 is less than 100...
      {
        // Fill the other digit with background color:
        tft.fillRect((positionX_Charg5 + 30), positionY_Charg5, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)
      }
      break;
    default:
      // Якщо вхідна команда не 1 або 2, не виконувати жодної дії
      break;
  }
}

void numbers() {  // назва клієнта заноситься в масив
  switch (name) {
    case 1:
      clients_name[1][0] = 1;
      clients_name[1][1] = charge;
      e[1] = 0;
      // Serial.print(" k1 ");
      //Serial.println(clients_name[ ][1]);

      break;
    case 2:
      clients_name[2][0] = 2;
      clients_name[2][1] = charge;
      e[2] = 0;
      //  Serial.print(" k2 ");
      //Serial.println(clients_name[ ][2]);
      break;
    case 3:
      clients_name[3][0] = 3;
      clients_name[3][1] = charge;
      e[3] = 0;
      // Serial.print(" k3 ");
      //Serial.println(clients_name[ ][3]);

      break;
    case 4:
      clients_name[4][0] = 4;
      clients_name[4][1] = charge;
      e[4] = 0;

      break;

    case 5:
      clients_name[5][0] = 5;
      clients_name[5][1] = charge;
      e[5] = 0;

      break;
      /*
    case 6:
      clients_name[6][0] = 1;
      e[6] = 0;

      break;
    case 7:
      clients_name[7][0] = 1;
      e[7] = 0;

      break;
    case 8:
      clients_name[8][0] = 1;
      e[8] = 0;

      break;
    case 9:
      clients_name[9][0] = 1;
      e[9] = 0;

      break;
    case 10:
      clients_name[10][0] = 1;
      e[10] = 0;

      break;*/
    default:
      // Якщо вхідна команда не 1 або 2, не виконувати жодної дії
      break;
  }
}

void timer() {  // підрахунок кількості  online (5)

  for (int q = 1; q < NUM_DEVICES; q++) {  // підрахунок кількості  online (5)
    if (clients_name[q][0] > 0) {
      count6++;
    }
    // Serial.print(" q ");
    //Serial.print(q);
    if (q == (NUM_DEVICES - 1)) {  //(5) кожні 5 ітерацій записує змінну та скидає лічильник
      val_count = count6;

      count6 = 0;
    }
  }


  /* 
  Serial.print(" name ");
  Serial.print(name);
  Serial.print(" charge ");
  Serial.print(charge);
  Serial.print(" val_count ");
  Serial.print(val_count);
  Serial.print(" count5 ");
  Serial.println(count5);


   Serial.print(" clients_name[a][0] ");
  Serial.print(clients_name[1][0]);
  Serial.print(" clients_name[ ][b] ");
  Serial.print(clients_name[2][0]);
  Serial.print(" e[1] ");
  Serial.print(e[2]);
  Serial.print(" e[2] ");
  Serial.println(e[2]);*/
}

// обробка відключення клієнтів
void disconnect() {
  if (WiFi.status() == WL_CONNECTED) {  //обробник з'єднання клієнта
  } else {
    if (count2 > 0) {
      count2--;
    }
  }

  if (count2 <= 1 && flag4 == 0) {
    flag1 = 0;                                                                         //виклик функції disconnect
    tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_BLACK);  // Малюємо зелений круг
  }
  if (flag1 == 0) {                                     // визначення відсутності клієнтів
                                                        // Set position (x,y)
    if (flag4 == 0) {                                   //відключення оновлення в режимі налаштування
      LED1 = 0;                                         // відключення автоматичного режиму
      tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);  // Set color of text. First is the color of text and after is color of background
      tft.setTextSize(2);
      tft.setCursor((posX_disc + 40), posY_disc);
      tft.println("no");
      tft.setCursor(posX_disc, (posY_disc + 20));
      tft.println("connection");
    }
    flag2 = 0;
    charge = 0;
    name = 0;
    avrco2 = 0;
    avrhum = 0;
    avrTemp = 0;
    led(100);

    for (int i = 1; i < (NUM_DEVICES - 1); i++) {
      clients_name[i][0] = { 0 };
      clients_name[i][1] = { 0 };
    }
  }
  if (e[count5] >= 20) {              // кількість періодів пропусків сигналу передачи канала
    clients_name[count5][0] = { 0 };  // обнуляє регістр якщо не надходе імя клієнта 20 раз.
    clients_name[count5][1] = { 0 };
    e[count5] = { 0 };
  }

  if (count5 == (NUM_DEVICES - 1)) {  //
    count5 = 0;
  }
  count5++;
}

void zeroData() {  // стирання масиву при відсутності підключення
                   /*
  Serial.print(" c1 ");
  Serial.print(dataFromDevices[1][0]);
  Serial.print(" c2 ");
  Serial.print(dataFromDevices[1][1]);
  Serial.print(" c3 ");
  Serial.println(dataFromDevices[1][2]);*/

  if (clients_name[1][0] == 0) {
    dataFromDevices[1][0] = 0;
    dataFromDevices[1][1] = 0;
    dataFromDevices[1][2] = 0;
    tft.fillRect((positionX_Charg), positionY_Charg, 36, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[1]++;
    //  Serial.print(" e[1] ");
    // Serial.println(e[1]);
  }
  if (clients_name[2][0] == 0) {
    dataFromDevices[2][0] = 0;
    dataFromDevices[2][1] = 0;
    dataFromDevices[2][2] = 0;
    tft.fillRect((positionX_Charg2), positionY_Charg2, 36, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[2]++;
    // Serial.print(" e[2] ");
    // Serial.println(e[2]);
  }

  if (clients_name[3][0] == 0) {
    dataFromDevices[3][0] = 0;
    dataFromDevices[3][1] = 0;
    dataFromDevices[3][2] = 0;
    tft.fillRect((positionX_Charg3), positionY_Charg3, 36, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[3]++;
    //Serial.print(" e[3] ");
    //Serial.println(e[3]);
  }
  if (clients_name[4][0] == 0) {
    dataFromDevices[4][0] = 0;
    dataFromDevices[4][1] = 0;
    dataFromDevices[4][2] = 0;
    tft.fillRect((positionX_Charg4), positionY_Charg4, 36, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[4]++;
    // Serial.print(" e[4] ");
    // Serial.println(e[4]);
  }

  if (clients_name[5][0] == 0) {
    dataFromDevices[5][0] = 0;
    dataFromDevices[5][1] = 0;
    dataFromDevices[5][2] = 0;
    tft.fillRect((positionX_Charg5), positionY_Charg5, 36, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

    //Serial.print(" e[5] ");
    //Serial.println(e[5]);
  } else {
    e[5]++;
  }
  /*
  if (clients_name[6][0] == 0) {
    dataFromDevices[6][0] = 0;
    dataFromDevices[6][1] = 0;
    dataFromDevices[6][2] = 0;
    tft.fillRect((positionX_Charg6 + 18), positionY_Charg6, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[6]++;
  }
  if (clients_name[7][0] == 0) {
    dataFromDevices[7][0] = 0;
    dataFromDevices[7][1] = 0;
    dataFromDevices[7][2] = 0;
    tft.fillRect((positionX_Charg7 + 18), positionY_Charg7, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[7]++;
  }
  if (clients_name[8][0] == 0) {
    dataFromDevices[8][0] = 0;
    dataFromDevices[8][1] = 0;
    dataFromDevices[8][2] = 0;
    tft.fillRect((positionX_Charg8 + 18), positionY_Charg8, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[8]++;
  }
  if (clients_name[9][0] == 0) {
    dataFromDevices[9][0] = 0;
    dataFromDevices[9][1] = 0;
    dataFromDevices[9][2] = 0;
    tft.fillRect((positionX_Charg9 + 18), positionY_Charg9, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[9]++;
  }
  if (clients_name[10][0] == 0) {
    dataFromDevices[10][0] = 0;
    dataFromDevices[10][1] = 0;
    dataFromDevices[10][2] = 0;
    tft.fillRect((positionX_Charg10 + 18), positionY_Charg10, 6, 8, ILI9341_BLACK);  // Draw filled rectangle (x,y,width,height,color)

  } else {
    e[10]++;
  }*/
}

void graf() {  //вивод графіків на екран

  if (qw == 0 && flag4 == 0) {  // виклик функції графіки
    tft.fillScreen(ILI9341_BLACK);
    qw = 1;
  }

  tft.drawRoundRect(124, 5, 52, 44, 5, ILI9341_CYAN);  // Draw rounded rectangle (x,y,довжина,висота,radius,color)
  tft.drawRoundRect(176, 5, 52, 44, 5, ILI9341_CYAN);  // Draw rounded rectangle (x,y,довжина,висота,radius,color)
  tft.drawRoundRect(228, 5, 52, 44, 5, ILI9341_CYAN);  // Draw rounded rectangle (x,y,довжина,висота,radius,color)
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);  // Встановлення кольору тексту
  tft.setCursor(127, 8);            // Встановлення позиції курсора
  tft.println("CO2 PPM");
  tft.setCursor(178, 8);  // Встановлення позиції курсора
  tft.println("Humidity");
  tft.setCursor(178, 18);  // Встановлення позиції курсора
  tft.println("   %");
  tft.setCursor(230, 8);  // Встановлення позиції курсора
  tft.println("Temp. C");

  if (count7 == 0) {
    //шкала СО2
    tft.fillRect(124, 50, 50, 75, ILI9341_RED);      // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(124, 125, 50, 35, ILI9341_ORANGE);  // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(124, 160, 50, 35, ILI9341_YELLOW);  // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(124, 195, 50, 45, ILI9341_GREEN);   // Біла основа шкали (x, y, ширина, висота)

    // Відображення стрілки шкала СО2

    int arrowX = 134;
    if (avrco2 <= 600) {
      // Позиція стрілки на шкалі green (value, minval, maxval, точкапочатку, точка кінця)
      arrowY = 0 + map(avrco2, 400, 600, 240, 195);
      if (flag1 == 1) {
        tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_GREEN);  // Малюємо зелений  прямокутник стану со2
        tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);                                    // Set color of text. First is the color of text and after is color of background
        tft.setTextSize(1);

        tft.setCursor(25, 25);
        tft.print("GOOD QUALITY");
        tft.setCursor(54, 44);
        tft.print("AIR");
      }
    }
    if (avrco2 > 600 && avrco2 < 1000) {
      arrowY = 0 + map(avrco2, 601, 1000, 195, 160);  // Позиція стрілки на шкалі yellow
      if (flag1 == 1) {
        tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_YELLOW);  // Малюємо жовтий  прямокутник стану со2
        tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);                                     // Set color of text. First is the color of text and after is color of background
        tft.setTextSize(1);
        tft.setCursor(30, 25);
        tft.print("PERMISSIBLE");
        tft.setCursor(30, 44);
        tft.print("QUALITY AIR");
      }
    }
    if (avrco2 >= 1000 && avrco2 <= 1500) {
      arrowY = 0 + map(avrco2, 1000, 1500, 160, 125);  // Позиція стрілки на шкалі orange
      if (flag1 == 1) {
        tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_ORANGE);  // Малюємо помаранчовий  прямокутник стану со2
        tft.setTextColor(ILI9341_WHITE, ILI9341_WHITE);                                     // Set color of text. First is the color of text and after is color of background
        tft.setTextSize(1);
        tft.setCursor(42, 17);
        tft.print("LIMITED");
        tft.setCursor(30, 36);
        tft.print("PERMISSIBLE");
        tft.setCursor(30, 55);
        tft.print("QUALITY AIR");
      }
    }
    if (avrco2 > 1500 && avrco2 <= 5000) {
      arrowY = 0 + map(avrco2, 1500, 5000, 125, 50);  // Позиція стрілки на шкалі red
      if (flag1 == 1) {
        //tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_GREEN);// Малюємо зелений прямокутник стану со2
        tft.fillRoundRect(2, 5, (widthButton + 50), heightButton + 15, 5, ILI9341_RED);  // Малюємо червоний прямокутник стану со2
        tft.setTextColor(ILI9341_WHITE, ILI9341_WHITE);                                  // Set color of text. First is the color of text and after is color of background
        tft.setTextSize(1);
        tft.setCursor(30, 33);
        tft.print("HARMFUL AIR");
      }
    }
    // Вертикальна позиція стрілки шкала СО2
    tft.fillTriangle(arrowX, arrowY, arrowX - 10, arrowY - 10, arrowX + 10, arrowY - 10, ILI9341_BLUE);  // Відображення стрілки


    //шкала вологості
    tft.fillRect(176, 50, 50, 75, ILI9341_BLUE);     // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(176, 125, 50, 70, ILI9341_GREEN);   // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(176, 195, 50, 45, ILI9341_YELLOW);  // Біла основа шкали (x, y, ширина, висота)
                                                     // Відображення стрілки шкала СО2
    int arrowX2 = 186;
    if (avrhum <= 40) {
      arrowY2 = 0 + map(avrhum, 0, 40, 240, 195);  // Позиція стрілки на шкалі yellow
    }
    if (avrhum > 40 && avrhum < 60) {
      arrowY2 = 0 + map(avrhum, 40, 60, 195, 125);  // Позиція стрілки на шкалі green
    }
    if (avrhum >= 60 && avrhum <= 100) {
      arrowY2 = 0 + map(avrhum, 60, 100, 125, 50);  // Позиція стрілки на шкалі blue
    }

    // Вертикальна позиція стрілки шкала СО2
    tft.fillTriangle(arrowX2, arrowY2, arrowX2 - 10, arrowY2 - 10, arrowX2 + 10, arrowY2 - 10, ILI9341_RED);  // Відображення стрілки

    //шкала температури
    tft.fillRect(228, 50, 50, 75, ILI9341_ORANGE);  // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(228, 125, 50, 70, ILI9341_GREEN);  // Біла основа шкали (x, y, ширина, висота)
    tft.fillRect(228, 195, 50, 45, ILI9341_BLUE);   // Біла основа шкали (x, y, ширина, висота)

    int arrowX3 = 238;
    if (avrTemp <= 19) {
      arrowY3 = 0 + map(avrTemp, -10, 19, 240, 195);  // Позиція стрілки на шкалі temp blue
    }
    if (avrTemp > 19 && avrTemp < 26) {
      arrowY3 = 0 + map(avrTemp, 19, 26, 195, 125);  // Позиція стрілки на шкалі temp green
    }
    if (avrTemp >= 26 && avrTemp <= 60) {
      arrowY3 = 0 + map(avrTemp, 26, 60, 125, 50);  // Позиція стрілки на шкалі temp orange
    }

    // Вертикальна позиція стрілки шкала temp
    tft.fillTriangle(arrowX3, arrowY3, arrowX3 - 10, arrowY3 - 10, arrowX3 + 10, arrowY3 - 10, ILI9341_RED);  // Відображення стрілки шкала temp

    count7++;
  } else {
    count7++;
    if (count7 == 5) {  //3
      count7 = 0;
    }
  }
}

void buttons() {
  tft.setTextSize(1);
  if (LED1 == 1) {

    tft.fillRoundRect(20, 75, widthButton, heightButton, 8, ILI9341_RED);  // Малюємо червону кнопку
    tft.setTextColor(ILI9341_WHITE, ILI9341_RED);                          // Set color of text. First is the color of text and after is color of background
    tft.setCursor(34, 90);
    tft.print("control");
    tft.setCursor(43, 100);
    tft.print("auto");
  } else {
    tft.fillRoundRect(20, 75, widthButton, heightButton, 8, ILI9341_GREEN);  // Малюємо червоний круг
    tft.setTextColor(ILI9341_WHITE, ILI9341_GREEN);                          // Set color of text. First is the color of text and after is color of background
    tft.setCursor(34, 90);
    tft.print("control");
    tft.setCursor(43, 100);
    tft.print("hand");
  }
  if (LED2 == 1) {
    tft.fillRoundRect(20, 130, widthButton, heightButton, 8, ILI9341_RED);  // Малюємо червоний круг
    tft.setCursor(35, 150);
    tft.setTextColor(ILI9341_WHITE, ILI9341_RED);  // Set color of text. First is the color of text and after is color of background
    tft.print("air on");
  } else {
    tft.fillRoundRect(20, 130, widthButton, heightButton, 8, ILI9341_GREEN);  // Малюємо червоний круг
    tft.setTextColor(ILI9341_WHITE, ILI9341_GREEN);                           // Set color of text. First is the color of text and after is color of background
    tft.setCursor(35, 150);
    tft.print("air off");
  }
  if (LED3 == 1) {
    tft.fillRoundRect(20, 185, widthButton, heightButton, 8, ILI9341_RED);  // Малюємо червоний круг
    tft.setTextColor(ILI9341_WHITE, ILI9341_RED);
    tft.setCursor(22, 200);
    tft.println("conditioner");
    tft.setCursor(46, 210);
    tft.print("on");
  } else {
    tft.fillRoundRect(20, 185, widthButton, heightButton, 8, ILI9341_GREEN);  // Малюємо червоний круг
    tft.setTextColor(ILI9341_WHITE, ILI9341_GREEN);                           // Set color of text. First is the color of text and after is color of background
    tft.setCursor(22, 200);
    tft.println("conditioner");
    tft.setCursor(45, 210);
    tft.print("off");
  }
}
void buttonset() {  // Кнопка налаштування
  tft.fillRoundRect(288, 170, 25, 25, 4, ILI9341_CYAN);
  tft.setTextColor(ILI9341_BLACK, ILI9341_CYAN);
  tft.setTextSize(2);
  tft.setCursor(295, 175);
  tft.print("H");
}

void tochsk() {
  if (!ts.touched()) {
    delay(10);
    return;
  } else {
//countbut4 = 80;
  }
  // Retrieve a point
  TS_Point p = ts.getPoint();  //(x, y)
  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);

  //BUTTON1
  if (p.x >= 20 && p.x <= 20 + widthButton &&  //height (50), width(70)
      p.y >= 75 && p.y <= 75 + heightButton) {
    //Serial.println(" klac ");
    if (countbut1 == 0 && flag4 == 0) {  // обробник натиску кнопки автоматичного режиму
      ProcessButton_0();
      countbut1 = 10;
    }
  }

  //BUTTON2
  if (LED1 == 0 && p.x >= 20 && p.x <= 20 + widthButton &&  //height (50), width(70)
      p.y >= 130 && p.y <= 130 + heightButton) {
    //Serial.println(" klac ");
    if (countbut2 == 0 && flag4 == 0) {  // обробник натиску кнопки автоматичного режиму
      ProcessButton_1();
      countbut2 = 10;
    }
  }

  //BUTTON3
  if (LED1 == 0 && p.x >= 20 && p.x <= 20 + widthButton &&  //height (50), width(70)
      p.y >= 185 && p.y <= 185 + heightButton) {
    //Serial.println(" klac ");
    if (countbut3 == 0 && flag4 == 0) {  // обробник натиску кнопки автоматичного режиму
      ProcessButton_2();
      countbut3 = 10;
    }
  }

  //batton settings
  if ((p.x >= 270) && (p.x <= 270 + 30) && (p.y >= 170) && (p.y <= 170 + 30) && (countbut4 == 0)) {  //height (50), width(70)
    flag4 = !flag4;
    //flag4 = 1;
    countbut4 = 20;

    qw = 0;
  }

  if (flag4 == 1) {  // обробник натиску кнопки автоматичного режиму
                     // Конвертація координат торка в значення температури


    valslayder = map(p.x, 10, 230, TEMPERATURE_MIN, TEMPERATURE_MAX);      //значення слайдеру тфт 10 - 230
    if (valslayder >= TEMPERATURE_MIN && valslayder <= TEMPERATURE_MAX) {  // Перевірка, чи значення в межах діапазону
      airtemp = valslayder;
      Serial.print(" valslayder ");
      Serial.println(valslayder);
    }
    drawUI();
  }
}


void body() {

  if (countbut4 > 0) {
    //Serial.print(" countbut4 ");
    // Serial.println(countbut4);
  }

  for (int i = 0; i < DATA_SIZE; i++) {
    //перевіряє, чи об'єкт клієнта у масиві є недійсним (тобто NULL або 0).
    if (!clients[i]) {

      clients[i] = server.available();
    }

    if (clients[i] && clients[i].connected()) {  //перевіряє чи існує клієнт і чи він підключений

      //перевіряє, чи є доступні дані для читання з клієнта, підключеного до сервера.
      rectangle(5);
      String jsonString = clients[i].readStringUntil('\r\n');
      StaticJsonDocument<128> doc;
      DeserializationError error = deserializeJson(doc, jsonString);

      if (!error) {            // спрацьовує, коли є данні в буфері
        flag1 = 1;             // вимкнення функції disconnect
        count2 = perioddelay;  // обробник підключення мережі (30)

        name = doc["value1"];
        charge = doc["value5"];                    //CargeValue
        dataFromDevices[name][0] = doc["value2"];  //CO2
        dataFromDevices[name][1] = doc["value3"];  //Hum
        dataFromDevices[name][2] = doc["value4"];  //Temp
      }
    } else {
      clients[i].stop();
      clients[i] = WiFiClient();
    }
  }
  for (r = 0; r < NUM_DEVICES; r++) {
    if (val_count >= 1) {  //підключено більше 1 клієнта

      valavrco2 += dataFromDevices[r][0];
      valavrTemp += dataFromDevices[r][1];
      valavrhum += dataFromDevices[r][2];
      led(1000);

      avrco2 = valavrco2 / val_count;
      avrTemp = ((valavrTemp / val_count) - 1);
      avrhum = valavrhum / val_count;
    }

    if (r == 0) {  //0-5 6шт
      valavrco2 = 0;
      valavrTemp = 0;
      valavrhum = 0;
    }
  }
  /*
  Serial.print(" name ");
  Serial.print(name);
  Serial.print(" charge ");
  Serial.print(charge);
  Serial.print(" avrco2 ");
  Serial.print(avrco2);
  Serial.print(" avrTemp ");
  Serial.print(avrTemp);
  Serial.print(" avrhum ");
  Serial.print(avrhum);
  Serial.print(" slider ");
  Serial.println(levelTemp);

  Serial.print(" count2 ");
  Serial.println(count2);*/
  numbers();
  if (flag4 == 0) {  //відключення оновлення графіків в режимі налаштування
    graf();
  }

  //обробка ложних натисків тачскріну
  if (countbut1 > 0) {
    countbut1--;
  }
  if (countbut2 > 0) {
    countbut2--;
  }
  if (countbut3 > 0) {
    countbut3--;
  }
  if (countbut4 > 0) {
    countbut4--;
    //Serial.print(" flag4 ");
    //Serial.println(flag4);
  }
  if (countbut4 == 0) {
    //flag4 = 0;
  }
  // if (flag4 == 1) {
  //  tft.fillRect(levelTemp - 5, 45, 10, 30, ILI9341_RED);
  // }
}

////////////////////////////////////////////
void webPage() {

  server1.handleClient();
}

//рівень web слайдера
void UpdateSlider() {

  String t_state = server1.arg("VALUE");

  // conver the string sent from the web page to an int
  levelTemp = t_state.toInt();  //рівень web слайдера 0 - 255
  Serial.print("UpdateSlider");
  Serial.println(levelTemp);

  // now set the PWM duty cycle
  ledcWrite(0, levelTemp);

  airtemp = map(levelTemp, 0, 255, 18, 30);  //рівень web слайдера 18 до 30 C.
  strcpy(buf, "");
  sprintf(buf, "%d", airtemp);
  //sprintf(buf, buf);

  // now send it back
  server1.send(200, "text/plain", buf);  //Send web page
  if (t_state.toInt() && flag4 == 1) {
    drawUI();
  }
}
//processing button_1 кнопка автоматичного режиму
void ProcessButton_0() {

  LED1 = !LED1;
  digitalWrite(PIN_LED1, LED1);
  // Serial.print("Button 0 ");
  // Serial.println(LED1);

  server1.send(200, "text/plain", "");  //Send web page
}

//processing button_1 Air control
void ProcessButton_1() {

  // just a simple way to toggle a LED on/off. Much better ways to do this
  Serial.println("Button 1 press");
  LED2 = !LED2;

  digitalWrite(PIN_LED2, LED2);
  //Serial.print("Button 1 ");
  //Serial.println(LED2);

  server1.send(200, "text/plain", "");  //Send web page
}

//processing button_2 conditioner
void ProcessButton_2() {

  LED3 = !LED3;
  digitalWrite(PIN_LED3, LED3);
  server1.send(200, "text/plain", "");  //Send web page
}
//processing button_3 restart esp32
void ProcessButton_3() {
  ESP.restart();                        // Ця команда перезапускає ESP32
  server1.send(200, "text/plain", "");  //Send web page
}

void SendWebsite() {

  //Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server1.send(200, "text/html", PAGE_MAIN);
}

void SendXML() {  //відправка даних на базову станцію

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");


  sprintf(buf, "<a0>%d</a0>\n", (int)(avrco2));  //, abs((int)(avrco2 * 10) - ((int)(avrco2)*10)));
  strcat(XML, buf);
  sprintf(buf, "<b0>%d</b0>\n", clients_name[1][0]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);
  sprintf(buf, "<c0>%d</c0>\n", clients_name[1][1]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);

  sprintf(buf, "<a1>%d.%d</a1>\n", (int)(avrhum), abs((int)(avrhum * 10) - ((int)(avrhum)*10)));
  strcat(XML, buf);
  sprintf(buf, "<b1>%d</b1>\n", clients_name[2][0]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);
  sprintf(buf, "<c1>%d</c1>\n", clients_name[2][1]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);

  sprintf(buf, "<a2>%d.%d</a2>\n", (int)(avrTemp), abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);
  sprintf(buf, "<b2>%d</b2>\n", clients_name[3][0]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);
  sprintf(buf, "<c2>%d</c2>\n", clients_name[3][1]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);

  sprintf(buf, "<b3>%d</b3>\n", clients_name[4][0]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);
  sprintf(buf, "<c3>%d</c3>\n", clients_name[4][1]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);

  sprintf(buf, "<b4>%d</b4>\n", clients_name[5][0]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);
  sprintf(buf, "<c4>%d</c4>\n", clients_name[5][1]);  //, abs((int)(avrTemp * 10) - ((int)(avrTemp)*10)));
  strcat(XML, buf);


  // show led1 status
  if (LED1) {
    strcat(XML, "<a3>1</a3>\n");
  } else {
    strcat(XML, "<a3>0</a3>\n");
  }
  if (LED2) {
    strcat(XML, "<a4>1</a4>\n");
  } else {
    strcat(XML, "<a4>0</a4>\n");
  }
  if (LED3) {
    strcat(XML, "<a5>1</a5>\n");
  } else {
    strcat(XML, "<a5>0</a5>\n");
  }

  strcat(XML, "</Data>\n");
  //Serial.println(XML); //////////////////////////////////////////////////
  server1.send(200, "text/xml", XML);
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void automatic() {


  if (LED1 == 1) {
    if (avrco2 > 1600) {
      LED2 = 1;
      digitalWrite(PIN_LED2, 1);

    } else if (co2 < 1000) {
      LED2 = 0;
      digitalWrite(PIN_LED2, 0);
    }

    int difference = abs(airtemp - avrTemp);  //гестеризис температурного рівня
    if (difference >= 3) {
      digitalWrite(PIN_LED3, 1);
      LED3 = 1;
    } else if (difference <= 1) {
      digitalWrite(PIN_LED3, 0);
      LED3 = 0;
    }


  } else {
    digitalWrite(PIN_LED2, LED2);
    digitalWrite(PIN_LED3, LED3);
  }
}



void drawUI() {
  // tft екран слайдеру

  tft.fillScreen(ILI9341_BLACK);  // Очистка екрану


  // Відображення значення температури
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(20, 20);
  tft.print("Temperature: ");
  tft.setCursor(160, 20);
  tft.print(airtemp);
  tft.print(" C");
  // Відображення слайдера на tft екрані
  levelTemp = map(airtemp, TEMPERATURE_MIN, TEMPERATURE_MAX, 10, 255);  //10 - 255
  tft.fillRect(10, 50, 255, 10, ILI9341_BLUE);
  tft.fillRect(levelTemp - 5, 45, 10, 30, ILI9341_RED);
  Serial.print(" airtemp ");
  Serial.println(airtemp);
  // Відображення межових значень температури
  tft.setTextSize(1);
  tft.setCursor(10, 80);
  tft.setTextColor(ILI9341_WHITE);
  tft.print(TEMPERATURE_MIN);
  tft.setCursor(255, 80);
  tft.print(TEMPERATURE_MAX);
}
