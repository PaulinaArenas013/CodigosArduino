#include <LiquidCrystal.h>
#include <Keypad.h>

//Se define el objeto LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

///////////////Definicion parameteros de Keypad//////////////// 4 filas 4 columnas
const byte ROWS = 4; //Keypad 4x4
const byte COLS = 4; 

// Definición de los botones del keypad, esta es mi versión pero ustedes pueden poner la que gusten
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','/'},
  {'4','5','6','x'},
  {'7','8','9','-'},
  {'o','0','=','+'}
};

// pines de conexión (estoy usando los analógicos y los digitales. no pasa nada, no se quema. el que tenga miedo de morir que no nazca)
byte rowPins[ROWS] = {A3, A2, A1, A0}; 
byte colPins[COLS] = {10, 9, 8, 7}; 

// se define el objeto keypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);//Se define el objeto keypad

///////////////////////////////////////////////////////////////////////

// foquillos
int imp_led = 0;
int imp_num = 1;
int imp_sym = 13;
 
//Carga datos calculadora
// variable que lleva los caracteres del keyboard
char key;
//números de 7 dígitos
char num[7]; 

// variables contadores
byte indice = 0; // para el dígito
byte pos = 0;    // para la posición en el lcd


// variables para las operaciones
float num1 = 0;
float num2 = 0;
char operacion = '+';//variable de operación
float division=0; //para los decimales en la división

///función para limpiar dígito e índice///
void borrenum()
{
  num[0] = 0;
  num[1] = 0;
  num[2] = 0;
  num[3] = 0;
  num[4] = 0;
  num[5] = 0;
  num[6] = 0;
  indice = 0;
  digitalWrite(imp_num, LOW);
}

//////////////////Imprimir LCD////////////////////
void imprimirlcd()
{ lcd.setCursor(pos, 0); // posición de cursor del lcd
  lcd.print(key); // manda a imprimir lo que tiene key
  digitalWrite(imp_led, HIGH);
  delay(300);
  digitalWrite(imp_led, LOW);
}

///Mostrar los números en la pantalla LCD/////////////
void cargar() {
  if (indice >= 7) {
    digitalWrite(imp_num, HIGH);
  }
  else {
    num[indice] = key;//almacena los dígitos en la variable num
    indice++;//Se incrementa el índice para no sobreescribir
    pos++;//Se incrementa la posicion en el lcd 
    imprimirlcd();//llama a la función para impirmir pantalla
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(imp_led, OUTPUT);
  pinMode(imp_num, OUTPUT);
  pinMode(imp_sym, OUTPUT);
  lcd.begin(16, 2);//Activación LCD 16x2
  lcd.clear();//
  lcd.setCursor(0, 0);
  lcd.print("Proyecto");
  lcd.setCursor (0, 1);
  lcd.print("Calculadora");
  delay(300);
  lcd.clear();
  lcd.setCursor(0, 0); 
}

void loop(){
  // Toma una lectura del objeto keypad
  key = myKeypad.getKey();
  if (key) {
    switch (key) {
              
      case '0'://Carga en pantalla numero 0
        cargar();
        break;
        
      case '1'://Carga en pantalla numero 1
        cargar();
        break;
        
      case '2'://Carga en pantalla numero 2
        cargar();
        break;
                
      case '3'://Carga en pantalla numero 3
        cargar();
        break;
                
      case '4'://Carga en pantalla numero 4
        cargar();
        break;
        
      case '5'://Carga en pantalla numero 5
        cargar();
        break;
              
      case '6'://Carga en pantalla numero 6
        cargar();
        break;
                
      case '7'://Carga en pantalla numero 7
        cargar();
        break;
                
      case '8'://Carga en pantalla numero 8
        cargar();
        break;
        
      case '9'://Carga en pantalla numero 9
        cargar();
        break;
        
      case '+'://Carga en pantalla símbolo +, se define la variable de operación '+'
        Serial.println();
        num1 = atof(num); //las funciones atol y atof convierten un char array a un número entero o de coma flotante
        lcd.setCursor(indice + 1, 0);
        borrenum();
        operacion = '+';//variable de operacion  suma '+'
        pos++;
        lcd.print(operacion);
        digitalWrite(imp_sym, HIGH);
        delay(300);
        digitalWrite(imp_sym, LOW);
        break;

      case '-'://Carga en pantalla símbolo +, se define la variable de operación '+'
        Serial.println();
        num1 = atof(num); //las funciones atol y atof convierten un char array a un número entero o de coma flotante
        lcd.setCursor(indice + 1, 0);
        borrenum();
        operacion = '-';//variable de operacion  suma '+'
        pos++;
        lcd.print(operacion);
        digitalWrite(imp_sym, HIGH);
        delay(300);
        digitalWrite(imp_sym, LOW);
        break;

       case 'x'://Carga en pantalla símbolo +, se define la variable de operación '+'
        Serial.println();
        num1 = atof(num); //las funciones atol y atof convierten un char array a un número entero o de coma flotante
        lcd.setCursor(indice + 1, 0);
        borrenum();
        operacion = 'x';//variable de operacion  suma '+'
        pos++;
        lcd.print(operacion);
        digitalWrite(imp_sym, HIGH);
        delay(300);
        digitalWrite(imp_sym, LOW);
        break;

       case '/'://Carga en pantalla símbolo +, se define la variable de operación '+'
        Serial.println();
        num1 = atof(num); //las funciones atol y atof convierten un char array a un número entero o de coma flotante
        lcd.setCursor(indice + 1, 0);
        borrenum();
        operacion = '/';//variable de operacion  suma '+'
        pos++;
        lcd.print(operacion);
        digitalWrite(imp_sym, HIGH);
        delay(300);
        digitalWrite(imp_sym, LOW);
        break;
        
      case 'o': //comando para limpiar pantalla
        Serial.println();
        borrenum();//Se hace el array que contiene los elementos de la operacion 0
        lcd.clear();
        pos = 0;
        lcd.setCursor(0, 0); //posicion inicial
        digitalWrite(imp_num, LOW);
        break;
        
      case '='://comando de igual
        num2 = atof(num);//las funciones atol y atof convierten un char array, a un número entero o de coma flotante,  se almacena la variable 2
        borrenum();
        Serial.println();
        Serial.print(num1);
        Serial.print(operacion);
        Serial.print(num2);
        Serial.print("=");
        lcd.setCursor(0, 1);
        lcd.print('=');
        
        switch (operacion) {//Operaciones 
          case '+'://Suma
            Serial.println(num1);
            Serial.println(num2);
            Serial.println(num1 + num2);
            lcd.print(num1 + num2);//Suma mun1+num2
            lcd.setCursor(0, 0);
            pos = 0;
            num1 = 0;
            num2 = 0;
            break;
            
          case '-'://Resta
            Serial.println(num1);
            Serial.println(num2);
            Serial.println(num1 - num2);
            lcd.print(num1 - num2);//Suma mun1+num2
            lcd.setCursor(0, 0);
            pos = 0;
            num1 = 0;
            num2 = 0;
            break;

          case 'x'://Resta
            Serial.println(num1);
            Serial.println(num2);
            Serial.println(num1 * num2);
            lcd.print(num1 * num2);//Suma mun1+num2
            lcd.setCursor(0, 0);
            pos = 0;
            num1 = 0;
            num2 = 0;
            break; 

         case '/'://Division
           if (num2 == 0) {
            lcd.print("Error div/0");
            //  Serial.println("Error div/0");
            }
            else {
              Serial.print(num1 / num2);
              lcd.print(num1 / num2);
              lcd.setCursor(0, 0);
              pos = 0;
              num1 = 0;
              num2 = 0;
            }
            break;
 
        }
        break;
    }
  }
  
}
