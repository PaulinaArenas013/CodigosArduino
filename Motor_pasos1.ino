#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//stepper motor
#define IN1 A5
#define IN2 A4
#define IN3 1//13
#define IN4 6


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '/'}, //{'7','8','9','/'}
  {'4', '5', '6', 'x'},
  {'7', '8', '9', '-'},
  {'o', '0', '=', '+'}
};
byte rowPins[ROWS] = {A3, A2, A1, A0};
byte colPins[COLS] = {10, 9, 8, 7};

Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int angle;
int stepCounter = 0;
int retardo = 20;
int a = 256 / 180;
int UnPaso = 6; //variable para botones A y B, un paso se considera como 6 grados
//Carga datos calculadora
char num[7]; //numero a ingresar max de 7 digitos
byte indice = 0;
byte pos = 0;
char key;

float num1 = 0;//variables que se usan para la operacion
float num2 = 0;
char operacion = '+';//variable de operacion
float division = 0; //para los decimales en la

///Variables de calculo///
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
}

//////////////////Imprimir LCD////////////////////
void imprimirlcd()
{ lcd.setCursor(pos + 7, 0); //indice
  lcd.print(key);
}

///Mostrar los numeros en la pantalla LCD/////////////
void cargar() {
  if (indice >= 3) {
  }
  else {
    num[indice] = key;//Carga de numero en pantalla maximo 7
    indice++;//Se incrementa el indice con la varible que se muestra en pantalla
    pos++;//Se incrementa la posicion en el array
    Serial.print(key);
    lcd.setCursor(0, 0);
    lcd.print("Angulo=");

    imprimirlcd();//Imprimir en pantalla
  }
}


/*********Stepper-Motor****/
const int numSteps = 4;
const int stepsLookup[4] = { B1000, B0100, B0010, B0001 };
int aux = 0;
void clockwise()
{
  stepCounter++;
  if (stepCounter >= numSteps) stepCounter = 0;
  setOutput(stepCounter);
}

void anticlockwise()
{
  stepCounter--;
  if (stepCounter < 0) stepCounter = numSteps - 1;
  setOutput(stepCounter);
}

void setOutput(int step)
{
  digitalWrite(IN4, bitRead(stepsLookup[step], 0));
  digitalWrite(IN3, bitRead(stepsLookup[step], 1));
  digitalWrite(IN2, bitRead(stepsLookup[step], 2));
  digitalWrite(IN1, bitRead(stepsLookup[step], 3));
}


void setup() {

  lcd.begin(16, 2);
  lcd.print("Proyecto Stepper");
  lcd.setCursor(0, 1);
  lcd.print("Motor");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0); //posicion inicial
  lcd.print("Angulo=");


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  key = myKeypad.getKey();//Lectura del Keypad

  if (key) {
    switch (key) {
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

      case '0'://Carga en pantalla numero 0
        cargar();
        break;
      case '/': //A
        num1 = UnPaso;
        angle = (int)(num1 * 256 / 180);

        for (int i = 0; i < 4 * angle; i++) // 512*4 = 2048 pasos
        {

          clockwise();

          delay(retardo);
        }
        break;
      case 'x': //B
        num1 = UnPaso;
        angle = (int)(num1 * 256 / 180);

        for (int i = 0; i < 4 * angle; i++) // 512*4 = 2048 pasos
        {
          anticlockwise();
          delay(retardo);
        }
        lcd.clear();
        lcd.setCursor(0, 0); //posicion inicial
        lcd.print("Angulo=0");


        break;
      case 'o': //comando para limpiar pantalla * * *
        borrenum();//Se hace el array que contiene los elementos de la operacion 0
        lcd.clear();
        pos = 0;
        lcd.setCursor(0, 0); //posicion inicial
        lcd.print("Angulo=");
        break;

      case '+'://D
        num1 = atof(num);
        angle = (int)(num1 * 256 / 180);

        for (int i = 0; i < 4 * angle; i++) // 512*4 = 2048 pasos
        {

          clockwise();

          delay(retardo);
        }
        aux = 2; // se usa para comprobar que se ejecutó el case +


        //Stop
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        //stepper.moveDegreesCW (num1);
        break;

      case '-'://C C C


        angle = (int)(num1 * 256 / 180);

        for (int i = 0; i < 4 * angle; i++) // 512*4 = 2048 pasos
        {
          anticlockwise();
          delay(retardo);
        }
        lcd.clear();
        lcd.setCursor(0, 0); //posicion inicial
        lcd.print("Angulo=0");
        break;
    }
  }

  //(key!='o' || key!='=' ||key!='+'||key!='-'||key!='x'||key!='/' )
  if ( (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0' ) && aux == 2) { // se comprueba el uso del case + para solo ejecutar el if si es así
    borrenum();//Se hace el array que contiene los elementos de la operacion 0
    lcd.clear();
    pos = 0;
    lcd.setCursor(0, 0); //posicion inicial
    lcd.print("Angulo=");
    aux = 0;

  }
}
