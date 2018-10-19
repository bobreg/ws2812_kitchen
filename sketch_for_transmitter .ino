#include <VirtualWire.h>

String messadge = "c";  //стартовый символ для передачи по 433МГц
char msg[255];
char incomingByte[255];
String color;
int len = 0; //длинна сообщения

void setup() {
  Serial.begin(115200);
  vw_set_ptt_inverted(true); // Необходимо для DR3100
  vw_setup(2000); // Устанавливаем скорость передачи (бит/с)
}

void loop() {
  if (Serial.available() > 0) {
    len = Serial.readBytes(incomingByte, 'Q'); //Q - до этого символа ардуино читает буфер
//----------------                                  
    for(int i = 0; i < len-1; i++){  //объединение массива входных байтов цвета в одну строку
      messadge = messadge + incomingByte[i]; // от 0 до 16+ млн
    }
//----------------    
    for(int i = 0; i < 255; i++){
  incomingByte[i] = 0;   //обнуление массива для входных данных, а то при новых данных не всё может удалиться
  }
   send_433MHz();
  }
}

void send_433MHz(){
  messadge.toCharArray(msg, 255);
  Serial.println(msg);
  vw_send((uint8_t *)msg, strlen(msg));// передача
  vw_wait_tx(); // Ждем пока передача будет окончена
  delay(200);
  messadge = "c";
}
