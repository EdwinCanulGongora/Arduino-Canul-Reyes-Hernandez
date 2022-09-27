#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd (0x27,16,2); // 0x27 Se ha definido la dirección del bus de la pantalla LCD y el tamaño de esta.
RTC_DS1307 RTC; // Se declara el objeto LCD.
#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 11
#define DHTPIN 2 // Se define el puerto al que conectamos el Sensor: pin digital 2.
DHT dht(DHTPIN, DHTTYPE); // Se define el objeto dht

void setup () {
  Wire.begin(); // Inicia el puerto I2C
  RTC.begin(); // Inicia la comunicaci¢n con el RTC
        // Comentar una vez establecida la hora
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora
  // el anterior se usa solo en la configuracion inicial

  // Serial.begin(9600); // Establece la velocidad de datos del puerto serie si se van a extraer los datos por el
  lcd.init(); // Se inicia el lcd
  lcd.backlight(); // Se enciende la luz del lcd
  lcd.clear(); // Se borra la pantalla del lcd
  dht.begin(); // se inicia la lectura del dht
}

void loop(){
  char buffer[30]; // Se crea el buffer y se define su longitud
  int h = dht.readHumidity(); // Lee la humedad
  int t= dht.readTemperature(); // Lee la Temperatura
  char g= (char)223; // Se crea el simbolo de grados
  char p='%'; // Se crea el simbolo de porcentaje
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  
  sprintf(buffer, "%02d:%02d - %02d/%02d/%2d", now.hour(), now.minute(), now.day(), now.month(), now.year()); // Se crea la primera linea desde el buffer y se le da formato
  //Serial.print(buffer); // Se escribe en el puerto serie si se desea verlo por ahí
  lcd.setCursor(0,0); // Se situa el cursor en la primera linea del lcd
  lcd.print(buffer); // Se escribe la primera linea en el lcd
  sprintf(buffer,"Temp:%02d%c Hum:%02d%c", t, g, h, p); //Se crea la segunda linea desde el buffer y se le da formato
  //Serial.print(buffer); // Se escribe en el puerto serie si se desea verlo por ahí
  lcd.setCursor(0,1); // Se situa el cursor en la segunda linea del lcd
  lcd.print(buffer); // Se imprimer la segunda linea en el lcd
  delay(1000); // La informaci¢n se actualiza cada 1 seg.
}
