const int pinLaser=13;
const int pinLed=12;
const int pinBuzzer=11;
const int pinLDR=A0;

int valorLDR =0;

void setup() {
  pinMode(pinLaser, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer,OUTPUT);
  pinMode(pinLDR, INPUT);

  digitalWrite(pinLaser, HIGH);

}

void loop() {
  valorLDR= analogRead(pinLDR);

  if(valorLDR <= 250){
    for(int i =1; i <= 5; i++){
      sonido();
    }
  }
}

void sonido(){
  digitalWrite(pinBuzzer,HIGH);
  digitalWrite(pinLed,HIGH);
  delay(1000);
  digitalWrite(pinBuzzer, LOW);
  digitalWrite(pinLed,LOW);
  delay(500);
}
