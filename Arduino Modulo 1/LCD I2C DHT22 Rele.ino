#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd (0x3F, 16, 2);
DHT dht(DHTPIN,DHTTYPE);

const int pinRele=3;
int activacion =0;
void setup() {
  lcd.init();
  dht.begin();

  pinMode(pinRele, OUTPUT);
}

void loop() {
  delay(500);
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  lcd.home();
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0,1);

  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  if(t >= 28){
    activacion +=1;
    digitalWrite(pinRele, HIGH);
  }else if(t<=25){
    activacion=0;
    digitalWrite(pinRele,LOW);
  }

  if(activacion ==1){
    lcd.clear();
    lcd.print("Encendiendo");
    lcd.setCursor(0,1);
    lcd.print("Ventilador");

    for(int i=0; i<3; i++){
      lcd.noDisplay();
      delay(500);

      lcd.display();
      delay(500);
    }
    lcd.clear();
  }

}
