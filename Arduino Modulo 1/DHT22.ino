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
  Serial.begin(9600);
  lcd.init();
  dht.begin();

  pinMode(pinRele, OUTPUT);
}

void loop() {
  delay(500);
  float h=dht.readHumidity();
  float t=dht.readTemperature();

  lcd.home();
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%");

  Serial.println();

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" C");

  if(t >= 25){
    activacion +=1;
    digitalWrite(pinRele, HIGH);
  }else if(t<=25){
    activacion=0;
    digitalWrite(pinRele,LOW);
  }

  if(activacion ==1){
    lcd.clear();
    Serial.print("Encendiendo");
    Serial.println();
    Serial.print("Ventilador");

    for(int i=0; i<3; i++){
      lcd.noDisplay();
      delay(500);

      lcd.display();
      delay(500);
    }
    lcd.clear();
  }

}

