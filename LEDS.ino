const int ledPIN1 = 2;//Declaramos los  pines del 1 al 10 para conectar nuestros LEDS
const int ledPIN2 = 3;
const int ledPIN3 = 4;
const int ledPIN4 = 5;
const int ledPIN5 = 6;
const int ledPIN6 = 7;
const int ledPIN7 = 8;
const int ledPIN8 = 9;
const int ledPIN9 = 10;

void setup() {
  pinMode(ledPIN1 , OUTPUT); //definir pin como salida a todos los leds
  pinMode(ledPIN2 , OUTPUT);
  pinMode(ledPIN3 , OUTPUT);
  pinMode(ledPIN4 , OUTPUT);
  pinMode(ledPIN5 , OUTPUT);
  pinMode(ledPIN6 , OUTPUT);
  pinMode(ledPIN7 , OUTPUT);
  pinMode(ledPIN8 , OUTPUT);
  pinMode(ledPIN9 , OUTPUT);

  digitalWrite(ledPIN1 , HIGH);   // poner el Pin en HIGH para encender 
  digitalWrite(ledPIN2 , HIGH);
  digitalWrite(ledPIN3 , HIGH);
  digitalWrite(ledPIN4 , HIGH);
  digitalWrite(ledPIN5 , HIGH);
  digitalWrite(ledPIN6 , HIGH);
  digitalWrite(ledPIN7 , HIGH);
  digitalWrite(ledPIN8 , HIGH);
  digitalWrite(ledPIN9 , HIGH);
  delay(800);
}
 
void loop(){
  digitalWrite(ledPIN1 , HIGH);   // poner el Pin en HIGH para encender 
  delayMicroseconds(16383);
  digitalWrite(ledPIN1 , LOW);    // poner el Pin en LOW para apagar
  delayMicroseconds(16383);
  digitalWrite(ledPIN2 , HIGH);
  delay(100);
  digitalWrite(ledPIN2 , LOW);
  delay(100);
  digitalWrite(ledPIN3 , HIGH);
  delay(150);
  digitalWrite(ledPIN3 , LOW);
  delay(150);
  digitalWrite(ledPIN4 , HIGH);
  delay(200);
  digitalWrite(ledPIN4 , LOW);
  delay(200);
  digitalWrite(ledPIN5 , HIGH);
  delay(300);
  digitalWrite(ledPIN5 , LOW);
  delay(300);
  digitalWrite(ledPIN6 , HIGH);
  delay(500);
  digitalWrite(ledPIN6 , LOW);
  delay(500);
  digitalWrite(ledPIN7 , HIGH);
  delay(700);
  digitalWrite(ledPIN7 , LOW);
  delay(700);
  digitalWrite(ledPIN8 , HIGH);
  delay(1000);
  digitalWrite(ledPIN8 , LOW);
  delay(1000);
  digitalWrite(ledPIN9 , HIGH);
  delay(2000);
  digitalWrite(ledPIN9 , LOW);
  delay(2000);

} 
