const int ledPIN = 9;//Declaramos el pin 9 para conectar nuestro LED
 
void setup() {
  Serial.begin(9600);    //iniciar puerto serie
  pinMode(ledPIN , OUTPUT);  //definir pin como salida
}
 
void loop(){
  digitalWrite(ledPIN , HIGH);   // poner el Pin en HIGH
}
