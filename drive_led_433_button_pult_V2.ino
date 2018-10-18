#include <VirtualWire.h>
#include <IRremote.h>
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
#include "Adafruit_NeoPixel.h";
#define LED_COUNT 300
#define LED_PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN);
uint32_t a = 16762985; //переменная задаёт цвет
String color; //строковая переменная задаёт цвет
int d = 2; //пин для светодиода
int pinButton = 4;
boolean flagButton = false;
boolean flagLed = false;
boolean stateButton = LOW;
boolean lastButton = LOW;

void setup() {
  Serial.begin(9600);
  vw_set_ptt_inverted(true); // Необходимо для DR3100
  vw_setup(2000); // Задаем скорость приема
  vw_rx_start(); // Начинаем мониторинг эфира
  strip.begin();
  pinMode(d, OUTPUT);
  pinMode(pinButton, INPUT);
  irrecv.enableIRIn();
  strip.begin();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Буфер для сообщения
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Длина буфера

  //----------обработка 433 МГц-----------------------
  if (vw_get_message(buf, &buflen)) // Если принято сообщение (символы приходят как ascii)
  {
    // Начинаем разбор
    // Если сообщение адресовано не нам, выходим
    if (buf[0] != 'c')
    {
      return;
    }
    Serial.print("длинна:"); //для отладки
    Serial.println(buflen); //для отладки
    if (buf[1] == '1') {
      flagLed = true;

      for (int i = 1; i < buflen; i++) { //перевод ascii в цифры для кода цвета
        buf[i] = buf[i] - 48;
        Serial.println(buf[i]);
      }

      for (int i = 2; i < buflen; i++) { //формирование из массива строковое значение цвета
        color = color + buf[i];
      }
      Serial.println(color); //для отладки
      a = color.toInt(); //перевод строки в цифровой тип данных
      led();
      color = "";
      digitalWrite(d, HIGH);
    }
    if (buf[1] == '2') {
      flagLed = false;
      led();
      digitalWrite(d, LOW);
    }
  }

  //-----------обработка кнопки-----------------
  stateButton = digitalRead(pinButton);
  if (stateButton == HIGH && flagButton == false) {
    flagButton = true;
    a = 16762985; //цвет включения от кнопки
    flagLed = !flagLed;
    led();
  }
  delay(100);
  stateButton = digitalRead(pinButton);
  if (stateButton == LOW) {
    flagButton = false;
  }
  //-----------обработка пульта-----------
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFA25D) {
      flagLed = !flagLed;
      a = 16762985;
      led();
    }
    irrecv.resume();
  }
//--------------------------------------------
}

//-----------функция включения/выключения ленты---------
void led() {
  if (flagLed == true) {
    digitalWrite(d, HIGH);
  }
  if (flagLed == false) {
    a = 0;
    digitalWrite(d, LOW);
  }
  for (int i = 1; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, a);
  }
  strip.show();
}
