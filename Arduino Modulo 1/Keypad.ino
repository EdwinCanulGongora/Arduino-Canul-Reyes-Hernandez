#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte filas = 4;
const byte columnas = 4;

byte pinsFilas[filas] = {9,8,7,6};
byte pinsColumnas[columnas] = {5,4,3,2};

char teclas[filas][columnas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
LiquidCrystal_I2C lcd(0x3F, 16,2);
Keypad teclado = Keypad(makeKeymap(teclas), pinsFilas, pinsColumnas, filas, columnas);

char tecla;
char datos[16];
int conteo = 0;

String password = "13";
String cambio;

boolean menuBool = false;

void setup() {
lcd.begin(16,2);

lcd.print("Digite Password:");
lcd.setCursor(0,1);
}

void loop() {
tecla = teclado.getKey();
if(tecla != NO_KEY){
  
  if(conteo <= 16){
    if(tecla != "*" && tecla != "#"){
      datos[conteo] = tecla;
      conteo++;
      
      lcd.print("*");
       }//teclas * y #
    }else{
      lcd.clear();
      lcd.print("Digite Password: ");
      lcd.setCursor(0,1);

      for(int i = 0; i < sizeof(datos); i++){
        datos[i] = (char)0;
      }
      conteo = 0;
      cambio = "";
    }// if cont
    if(tecla == '*'){
      lcd.clear();
      lcd.print("Comprobando");
      lcd.setCursor(0,1);
      lcd.print("Password");

      for(int i = 0; i <2;i++){
        lcd.noDisplay();
        delay(500);
      }
    for(int i = 0; i <conteo; i++){
      cambio.concat(datos[i]);
    }
    if(password == cambio){
      lcd.clear();
      lcd.print("Acceso Correcto");
      delay(1500);

      lcd.clear();
      lcd.print("Bienvenido");
      lcd.setCursor(0,1);
      lcd.print("Tu nombre :)");
      delay(1500);

      menuBool = true;
      lcd.clear();
      
      menu();
    }else{
      lcd.clear();
      lcd.print("Acceso Denegado");
      
      lcd.clear();
      lcd.print("Digite Password:");
      lcd.setCursor(0,1);

      conteo = 0;
      cambio = "";
    }
    }else if(tecla == '#'){
      int borrar = conteo - 1;
      
      if (borrar >= 0){
        for(int i = 0;i<conteo;i++){
          datos[i] = (char)0;
        }
        lcd.setCursor(borrar,1);
        lcd.print(" ");
        lcd.setCursor(borrar,1);
        conteo -= 1;
      }
    }
  }// if tecla
}//loop
  
void menu(){
  while(menuBool == true){
  lcd.home();
    lcd.print("Bienvenido al menu");
    tecla = teclado.getKey();

    if(tecla!= NO_KEY){
      if(tecla =='*'){
      menuBool = false;
      lcd.clear();
      lcd.print("Saliendo del menu: ");
      delay(1500);
      
      lcd.print("Digite Password: ");
      lcd.setCursor(0,1);
      
      for(int i = 0; i<sizeof(datos); i++){
        datos[i] = (char)0;
      }
          conteo = 0;
          cambio = "";
      }
    }
  }
 }

