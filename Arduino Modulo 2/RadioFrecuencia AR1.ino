#include <VirtualWire.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht (DHTPIN,DHTTYPE);

const int dataPin = 9;
const int pinLed=13;

String cadenaHT;

void setup() {
  dht.begin();

  vw_setup(2000);
  vw_set_tx_pin(dataPin);
  
  pinMode(pinLed,OUTPUT);
}

void loop() {
  float h= dht.readHumidity();
  float t= dht.readTemperature();

  char envio [VW_MAX_MESSAGE_LEN];

  //Humedad
  cadenaHT= "H" + String(h);

  cadenaHT.toCharArray(envio,sizeof(envio));

  digitalWrite(pinLed, HIGH);
  vw_send((uint8_t *)envio,strlen(envio));
  vw_wait_tx();
  digitalWrite(pinLed,LOW);

  //Temperatura
  cadenaHT= "t" + String(t);

  cadenaHT.toCharArray(envio,sizeof(envio));

  digitalWrite(pinLed, HIGH);
  vw_send((uint8_t *)envio,strlen(envio));
  vw_wait_tx();
  digitalWrite(pinLed,LOW);

  delay(50);

}
