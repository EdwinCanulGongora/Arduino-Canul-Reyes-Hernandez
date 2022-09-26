#include "U8glib.h"
#include "RTClib.h"
#include "DHT.h"

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

#define DHTPIN 2
#define DHTTYPE DHT22

RTC_DS1307 rtc;
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  rtc.begin();
  dht.begin();

  oled.firstPage();
  do{
    oled.setFont(u8g_font_fur14);
    oled.drawStr(20, 15, "Bienvenido");

    oled.setFont(u8g_font_9x18B);
    oled.drawStr(45,40,"Tu Nombre");

  }while(oled.nextPage());
  delay(3000);

}

void loop() {
  sensores();

}

void sensores(){
  DateTime fecha = rtc.now();

  float h=dht.readHumidity();
  float t=dht.readTemperature();

  oled.firstPage();
  do{
    oled.setFont(u8g_font_helvB08);
    oled.setPrintPos(0,15);

    imprimirDig(fecha.hour());
    oled.print(":");
    imprimirDig(fecha.minute());
    oled.print(":");
    oled.print(fecha.second());

    oled.print("    ");

    imprimirDig(fecha.day());
    oled.print("/");
    imprimirDig(fecha.month());
    oled.print("/");
    oled.print(fecha.year());

    //Temp y Hum
    oled.drawStr(0,30, "Temp:");
    oled.drawStr(0,50, "Hum:");

    oled.setPrintPos(65,30);
    oled.print(t);
    oled.print(" C");

    oled.setPrintPos(65,50);
    oled.print(h);
    oled.print("%");

    segundero(fecha.second());

  }while(oled.nextPage());

}

void imprimirDig(int num){
  if(num<10){
    oled.print("0");
  }
  oled.print(num, DEC);
}

void segundero(int segundo){
  float cuadrante = ((float)128/59)- 0.01;
  float operacion = cuadrante * segundo;

  oled.drawBox(0,55,operacion,9);
}