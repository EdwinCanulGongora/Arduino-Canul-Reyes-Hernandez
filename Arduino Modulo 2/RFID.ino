//Librerias
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
//Pines
#define RST_PIN 9
#define SS_PIN 10
#define pinBuzzer 8
#define pinBoton 7
//Crear objetos de los dispositivos
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x2F, 16, 2);
//Datos del usuario del mod RFID
byte usuario[7] = {0x04, 0xE6, 0xAA, 0xAA, 0x9E, 0x33, 0x80};
//Variables
byte lectorUID[7];
int estadoBoton = 0;
int estadoBotonAnt = 0;
int contador = 0;

bool menuBool = false;
void setup() {
  //Inicializar pines y objetos
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinBoton, INPUT);

  SPI.begin();
  mfrc522.PCD_Init();

  //lcd.init();
  //lcd.print("RFID");
  //delay(1500);
  //lcd.clear();
}

void loop() {
  estadoBotonRFID();
  //lcd.home();

  /*Establecer acciones para cada estado del botón
  0 -> Mostrar mensaje de entrada
  1 -> Leer tarjeta escaneada
  2 -> Comprobar tarjeta escaneada
  otros -> Acceso denegado
  */
  if(contador == 0){
    Serial.print("Presione boton");
    //lcd.setCursor(0, 1);
    Serial.println(" Para una opcion");
  }else if(contador == 1){
    Serial.println("Escanear Tarjeta");
    //lcd.setCursor(0, 1);
    if(!mfrc522.PICC_IsNewCardPresent()){
      return;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      return;
    }
    sonido(100,100);
    //Escanear tarjeta
    escanearUsuario();

    mfrc522.PICC_HaltA();
  }else if(contador == 2){
    Serial.print("Acerque la");
    //lcd.setCursor(0, 1);
    Serial.println(" Tarjeta");
    if(!mfrc522.PICC_IsNewCardPresent()){
      return;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      return;
    }
    sonido(100,100);
    //Guardar código de la tarjeta ingresada
    for(byte i = 0; i < mfrc522.uid.size; i++){
      lectorUID[i] = mfrc522.uid.uidByte[i];
    }

    //lcd.clear();
    Serial.print("Comprobando");
    //lcd.setCursor(0, 1);
    Serial.println(" Acceso");

    //for(int i = 0; i < 2; i++){
    //  lcd.noDisplay();
    //  delay(500);
    //  lcd.display();
    //  delay(500);
    //}

    //Comparar códigos
    if(compararUID(lectorUID,usuario)){
      //lcd.clear();
      Serial.print("Bienvenido");
      //lcd.setCursor(0, 1);
      Serial.println(" Pancho Pantera ");
      delay(3000);
      //lcd.clear();

      Serial.print("Iniciado");
      //lcd.setCursor(0, 1);
      Serial.println(" Sesion...");
      delay(1500);
      //lcd.clear();

      menuBool = true;

      mfrc522.PICC_HaltA();
      //Acceder al menú
      menu();
    }else{
      //lcd.clear();
      Serial.print("Error Usuario");
      //lcd.setCursor(0, 1);
      Serial.println(" - No permitido");

      sonido(1000, 500);

      //lcd.clear();

      mfrc522.PICC_HaltA();
    }
  }
  mfrc522.PICC_HaltA();
}

void estadoBotonRFID(){
  //Comprobar si se presionó el botón
  estadoBoton = digitalRead(pinBoton);

  if(estadoBoton != estadoBotonAnt){
    if(estadoBoton == HIGH){
      contador++;
      //lcd.clear();
      if(contador == 3){
        contador = 0;
      }
    }
    delay(20);
  }
  estadoBotonAnt = estadoBoton;
}

void sonido(int T1, int T2){
  //Generar pitido con el buzzer
  digitalWrite(pinBuzzer,HIGH);
  delay(T1);
  digitalWrite(pinBuzzer,LOW);
  delay(T2);
}

void escanearUsuario(){
  //Leer tarjeta ingresada e imprimir el código de esta
  Serial.print("UID: ");
  //lcd.print("UID: ");

  //Hexadecimal
  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    //lcd.print(mfrc522.uid.uidByte[i], HEX);
  }

  Serial.print("  HEX\t\t");

  //Decimal
  for(byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //lcd.print(mfrc522.uid.uidByte[i], DEC);
  }

  Serial.print("  DEC");
}

bool compararUID(byte lector[], byte usuario[]){
  for(byte i = 0; i < mfrc522.uid.size; i++){
    if(lector[i] != usuario[i]){
      return false;
    }
  }
  return true;
}

void menu(){
  //Mostrar menu  
  while(menuBool == true){
    inicio:
    //lcd.home();
    Serial.println("Opcion 1");
    //lcd.setCursor(0, 1);
    Serial.println("Opcion 2");
    //Volver a escanear tarjeta para salir del menu
    if(!mfrc522.PICC_IsNewCardPresent()){
      goto inicio;
    }
    if(!mfrc522.PICC_ReadCardSerial()){
      goto inicio;
    }

    for(byte i = 0; i < mfrc522.uid.size; i++){
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }

    //Guardar código de la tarjeta ingresada
    for(byte i = 0; i < mfrc522.uid.size; i++){
      lectorUID[i] = mfrc522.uid.uidByte[i];
    }

    //Comparar códigos
    if(compararUID(lectorUID,usuario)){

      menuBool = false;
      //lcd.clear();
      Serial.println("");
      Serial.println("Cerrando sesion");
      delay(1500);
      //lcd.clear();
      sonido(300,300);
      sonido(300,300);
      contador = 0;
    }else{
      //Bloquear en caso de no ser el mismo
      //lcd.clear();
      while(true){
        Serial.print("No eres usuario");
        //Serial.setCursor(0, 1);
        Serial.println(" - Bloqueado !!!");
        sonido(10,10);
      }
    }
    mfrc522.PICC_HaltA();
  }
}
