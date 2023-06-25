#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int carWidth = 8;
const int carHeight = 4;
int carX = SCREEN_WIDTH/2 - carWidth/2;
int carY = SCREEN_HEIGHT/2 - carHeight/2;

const int obstWidth = 6;
const int obstHeight = 20;
int obstX = SCREEN_WIDTH;
int obstY = random(0, SCREEN_HEIGHT - obstHeight);

int potPin = A0;
int potValue = 0;

bool gameOver = false;

void setup() {
  pinMode(potPin, INPUT);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  randomSeed(analogRead(0));
 

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 10);
  display.print("JUEGO OBSTACULO");
  display.display();
  delay(900);

  display.clearDisplay();
  display.display();
}

void loop() {
  if (gameOver) {
    display.clearDisplay();
    display.setCursor(SCREEN_WIDTH/2 - 18, SCREEN_HEIGHT/2 - 8);
    display.setTextSize(1.9);
    display.setTextColor(SSD1306_WHITE);
    display.println("Game Over");
    display.display();
    delay(2000);
    gameOver = false;
    obstX = SCREEN_WIDTH;
    obstY = random(0, SCREEN_HEIGHT - obstHeight);
  } else {
    display.clearDisplay();
    display.drawRect(carX, carY, carWidth, carHeight, SSD1306_WHITE);
    display.drawRect(obstX, obstY, obstWidth, obstHeight, SSD1306_WHITE);
    display.display();

    potValue = analogRead(potPin);
    if (potValue < 100 && carY > 0) {
      carY -= 2;
    } else if (potValue > 900 && carY < SCREEN_HEIGHT - carHeight) {
      carY += 2;
    }

    obstX -= 2;
    if (obstX < -obstWidth) {
      obstX = SCREEN_WIDTH;
      obstY = random(0, SCREEN_HEIGHT - obstHeight);
    }

    if (carX + carWidth >= obstX && carX <= obstX + obstWidth) {
      if (carY <= obstY + obstHeight - 1 && carY + carHeight - 1 >= obstY) {
        gameOver = true;
      }
    }
  }
}
