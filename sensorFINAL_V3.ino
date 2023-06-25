#include <LiquidCrystal.h>
#include "Keypad.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

long duracion;
long distancia; // float distancia para obtener decimales
int echo = A4;
int trig = A5;
int LED = 13;

////VARIABLES ////

int numero;
int numeros[6] = {0, 0, 0, 0, 0, 0};
int registro[6] = {0, 0, 0, 0, 0, 0};
int cont;
int cantidad = 0;
int resul1;
int resul2;
int resul3;
String txt = "";

////////////////

const byte ROWS = 4;
const byte COLS = 4;

byte lcdNumCols = 16; // -- número de columnas LCD
int numberOfColumns = 16;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'o', '0', '#', 'D'}};
byte rowPins[ROWS] = {A3, A2, A1, A0};
byte colPins[COLS] = {10, 9, 8, 7};

Keypad myKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Tonos
const int Buzzer = 6;                                                             // Pto PWM para buzzer (3, 5, 6, 9, 10, 12) buzzer
const int tonos[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494}; // Tonos Buzzer
const int countTonos = 10;                                                        // Números de tonos

// cont bar graph

int cont_bar_1 = 0;
int cont_bar_2 = 0;
int cont_bar_3 = 0;

//****************************bar**************************/

byte zero[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000};
byte one[] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000};

byte two[] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000};

byte three[] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100};

byte four[] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110};

byte five[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111};

//////////////////Efectos sonido ////////////////////
void sonido()
{
  for (int iTono = 0; iTono < countTonos; iTono++)
  {
    tone(Buzzer, tonos[iTono]);
    delay(50);
  }
  noTone(Buzzer);
}

/**********************Bar graph***********************/
void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn)
{
  double factor = totalCount / 80.0;  // Define un factor de conteo
  int percent = (count + 1) / factor; // Porcenjate a mostrar
  int number = percent / 5;
  int remainder = percent % 5;
  if (number > 0)
  {
    lcd.setCursor(number - 1, lineToPrintOn); // Fija posición x,y en la pantalla
    lcd.write(5);
  }

  lcd.setCursor(number, lineToPrintOn);
  lcd.write(remainder);
}

void Horizontal_bar()
{
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
}

void distance()
{
  // Para estabilizar nuestro módulo ultrasónico
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  // disparo de un pulso en el trigger de longitud 10us
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Lectura de la duración del pulso HIGH generado hasta recibir el Echo
  duracion = pulseIn(echo, HIGH);

  // Calculo distancia
  distancia = duracion / 58.4; // (cm)
  Serial.println(distancia);
}

void barra_1()
{
  Horizontal_bar();
  for (int ii = 1; ii < (cont_bar_1); ii++)
  {
    updateProgressBar(ii, 100, 1);
  }
}

void barra_2()
{

  while (cont > 0)
  {
    char key1 = myKeypad.getKey();
    if (key1 == 'A')
    {
      cont = -1;
      delay(100);
    }
    else
    {
      distance();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dist=");
      lcd.setCursor(5, 0);
      lcd.print(distancia);
      lcd.setCursor(10, 0);
      lcd.print(" cm");
      cont_bar_1 = distancia;
      barra_1();
      Serial.println(distancia);
      delay(200);
    }
  }
}

void barra_2_versionC()
{

  while (cont > 0)
  {
    lcd.clear();
    char key1 = myKeypad.getKey();
    if (key1 == 'A')
    {
      cont = -1;
      delay(100);
    }
    else
    {
      distance();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dist=");
      lcd.setCursor(5, 0);
      lcd.print(distancia);
      lcd.setCursor(10, 0);
      lcd.print(" cm");
      cont_bar_1 = distancia;
      barra_1();
      Serial.println(distancia);
      delay(200);
    }

    delay(2000);
  }
}

void medir_B()
{
  char key = myKeypad.getKey();
  do
  {
    /* code */
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    distancia = pulseIn(echo, HIGH);
    distancia = distancia / 58; // Se hace la conversión a centímetros
                                // Si quisieramos convertirlo a pulgadas, dividimos entre 148.
    Serial.print("Distancia = ");
    Serial.print(distancia);
    Serial.print(" cm");
    Serial.write(10);
    delay(200);
    //
    lcd.setCursor(0, 0);
    lcd.print("Distancia:");
    lcd.setCursor(0, 1);
    lcd.print(distancia);
    lcd.print(" cm");
    lcd.clear();

    if (distancia == resul1 || distancia == resul2 || distancia == resul3)
    {
      digitalWrite(LED, HIGH);
    }
    else
    {
      digitalWrite(LED, LOW);
    }

  } while (myKeypad.getKey() == NO_KEY);
  Serial.println("fin medir_B");
  lcd.clear();
}

void medir_B_v2()
{
  cantidad = txt.toInt();
  if (cantidad > 20)
  {
    tone(Buzzer, 450, 100);
    lcd.clear();
    resul1 = cantidad - 20;
    resul2 = cantidad - 10;
    resul3 = cantidad - 5;
    char key = myKeypad.getKey();
    do
    {

      digitalWrite(trig, LOW);
      delayMicroseconds(15);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      distancia = pulseIn(echo, HIGH);
      distancia = distancia / 58; // Se hace la conversión a centímetros

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Distancia en cm");
      lcd.setCursor(0, 1);
      lcd.print(distancia);
      delay(200);

      if (distancia == resul1)
      {
        digitalWrite(LED, LOW);
        delay(300);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        delay(300);
        digitalWrite(LED, HIGH);
        tone(Buzzer, 550, 200);
        delay(300);

      }
      else if (distancia == resul2)
      {
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(LED, HIGH);
        tone(Buzzer, 600, 400);
        delay(200);
      }
      else if (distancia == resul3)
      {
        digitalWrite(LED, LOW);
        delay(100);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        delay(100);
        digitalWrite(LED, HIGH);
        tone(Buzzer, 700, 400);
        delay(100);
      }
      else
      {
        digitalWrite(LED, LOW);
        delay(500);
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        delay(500); 
        digitalWrite(LED, HIGH);
        tone(Buzzer, 200, 200);
        delay(500);
      }

    } while (myKeypad.getKey() == NO_KEY);
  }
  else
  {
    lcd.clear();
    lcd.print("No > a 20");
    delay(5000);
  }

  lcd.clear();
}

void setup()
{
  pinMode(Buzzer, OUTPUT);  // Activa el Pto. 6 para activar Buzzer usando PWM
  lcd.begin(2, lcdNumCols); // Activacion LCD 16x2
  lcd.clear();              // Clear de la pantalla
  lcd.setCursor(0, 0);      // Posición 0,0 del curso
  lcd.print("Proyecto");    // Mensaje línea 1
  lcd.setCursor(0, 1);
  lcd.print("Distancia"); // Mensaje línea 2
  delay(500);
  sonido();            // Efecto de sonido cuando activa
  lcd.clear();         // Clear de la pantalla
  lcd.setCursor(0, 0); // posición inicial

  /// Carga en memoria Array LCD
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);

  // Ultrasonic sensor
  pinMode(trig, OUTPUT); // emisor
  pinMode(echo, INPUT);  // Receptor
  pinMode(LED, OUTPUT);  // LED

  Serial.begin(9600);
}

void loop()
{
  char key = myKeypad.getKey();
  if (key != NO_KEY)
  { // si se presiona una tecla

    switch (key)
    {
    case 'A':
      distance();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dist=");
      lcd.setCursor(5, 0);
      lcd.print(distancia);
      lcd.setCursor(10, 0);
      lcd.print(" cm");
      cont_bar_1 = distancia;
      Serial.println(distancia);
      barra_1();

      delay(200);
      tone(Buzzer, 3 * cont_bar_1, 100);

      lcd.print("   ");

      break;

    case 'B':
      cont = 1;
      barra_2();
      break;

    case 'C':
      cont = 1;
      barra_2_versionC();
      break;

    case 'o': // comando para limpiar pantalla
      cantidad = 0;
      txt = "";
      tone(Buzzer, 450, 100);
      lcd.clear();
      lcd.setCursor(0, 0);   // Posicion 0,0 del curso
      lcd.print("Proyecto"); // Mensaje linea 1
      lcd.setCursor(0, 1);
      lcd.print("Distancia"); // Mensaje linea 2
      delay(500);
      lcd.clear();

      cont_bar_1 = 0;
      cont = 0;
      break;

    case 'D':
      tone(Buzzer, 450, 100);
      lcd.print("Ingrese numero:");
      break;

    case '#':

      medir_B_v2();
      break;

    default:

      numero = key - 48;       // convertir el caracter a valor numerico
      numeros[cont] = numero;  // se guardar caracter por caracter en el arreglo numeros []
      registro[cont] = numero; // variables parqa funcion ordenar()
      txt = txt + String(numero);
      lcd.setCursor(cont, 1);
      lcd.print(numeros[cont]); // desplegar en el lcd
      cont = cont + 1;          // icrementamos la variable cont
      break;
    }
  }
}
