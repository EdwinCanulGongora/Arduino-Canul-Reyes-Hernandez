#include <OneWire.h>
#include <DallasTemperature.h>

int pinDS = 2;
int pinRele = 4;
int pinLedR = 5;
int pinLedA = 6;

float temperatura;
int brillo;
int estado;

OneWire ds(pinDS);
DallasTemperature sensor (&ds);

void setup() {
sensor.begin();

pinMode (pinRele, OUTPUT);
pinMode (pinLedR, OUTPUT);
pinMode (pinLedA, OUTPUT);

Serial.begin(9600);

}

void loop() {
sensor.requestTemperatures();
temperatura = sensor.getTempCByIndex(0);

brillo = map(temperatura, 0, 50, 0, 255);
brillo = constrain (brillo, 0, 255);

analogWrite(pinLedR, brillo); 
analogWrite(pinLedA, (255 - brillo));

estado = (temperatura >= 28) ? HIGH : LOW;
digitalWrite(pinRele, estado);

Serial.print (temperatura);
Serial.println(" C");
delay(500);
}