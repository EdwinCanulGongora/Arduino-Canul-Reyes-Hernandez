#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

const int pinBotonP=6;
const int pinBotonA=7;
const int pinMotor=9;

int contMotor=0;
int velocidad;

int estadoMotor;
int estadoParo;
void setup() {
  lcd.begin(16,2);
  lcd.print("Motor en paro");
  lcd.setCursor(0,1);
  lcd.print("en espera...");

  pinMode(pinBotonP, INPUT);
  pinMode(pinBotonA, INPUT);
  pinMode(pinMotor, OUTPUT);

  // put your setup code here, to run once:

}

void loop() {
  estadoMotor= digitalRead(pinBotonA);

  if(estadoMotor== HIGH){
    delay(500);
    contMotor +=1;

    if(contMotor==1){
      lcd.clear();
      delay(50);
      lcd.print("Motor en Giro");

      for(velocidad =0; velocidad <=255; velocidad++){
        analogWrite(pinMotor, velocidad);
        delay(50);

        lcd.setCursor(0,1);
        lcd.print(porcentaje(velocidad));
        lcd.print("%");
      }//for
    }//if cont
    if(contMotor==2){
      lcd.clear();
      
      lcd.print("PRECAUCION PARO");
      lcd.setCursor(0,1);
      lcd.print("DEL MOTOR!!!");

      for(int i=0; i<3; i++){
        lcd.noDisplay();
        delay(400);

        lcd.display();
        delay(1500);
      }

      lcd.clear();
      
      lcd.print("Parando Motor");

      for(velocidad=255; velocidad>=0; velocidad--){
        analogWrite(pinMotor, velocidad);
        delay(50);

        lcd.setCursor(0,1);
        lcd.print(porcentaje(velocidad));
        lcd.print("%");

        if(porcentaje(velocidad)>= 100){
          lcd.setCursor(3,1);
          lcd.print(" ");
        }else if(porcentaje(velocidad)<= 9){
          lcd.setCursor(2,1);
          lcd.print(" ");
        }

      }//for
        lcd.clear();

        lcd.print("Motor parado");
        lcd.setCursor(0,1);
        lcd.print("0%");

        contMotor=0;

    }//if cont
  }//if estadoMotor

  estadoParo=digitalRead(pinBotonP);

  if(estadoParo==HIGH){
    if(contMotor != 0){
      analogWrite(pinMotor, 0);

      delay(500);
      lcd.clear();
      lcd.print(" PARO DE");
      lcd.setCursor(0,1);
      lcd.print(" EMERGENCIA!!!");
      delay(1000);

      contMotor=0;

      for(int i=0; i< 15; i++){
        lcd.scrollDisplayLeft();
        delay(250);
      }

      for(int i=0; i< 30; i++){
        lcd.scrollDisplayRight();
        delay(250);
      }

      for(int i=0; i< 15; i++){
        lcd.scrollDisplayLeft();
        delay(250);
      }
    }//if contMotor
  }//if estadoParo

}//loop

int porcentaje(int vel){
  int operacion=vel*100;
  int resultado = operacion/255;

  return resultado;
}
