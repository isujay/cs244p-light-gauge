#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_GFX.h>

#define SERVO_PORT 27

#define LCD_CS 15
#define LCD_DC 2
#define LCD_RST 4

Adafruit_ST7789 lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);

// put function declarations here:
int myFunction(int, int);

Servo servo;

void setup() {
  // servo.attach(SERVO_PORT);
  Serial.begin(9600);
  lcd.init(135, 240);
  lcd.fillScreen(ST77XX_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  // servo.write(50);
  Serial.println("Hello Sujay Hegde");
  lcd.setCursor(0, 0);
  lcd.setTextColor(5000);
  lcd.setTextSize(3);
  lcd.println("Suj");
  lcd.println("Tech");
  lcd.println("STUDIOS");
  lcd.drawCircle(3, 3, 100, 134);
  sleep(3);
  lcd.fillScreen(ST7735_BLACK);
  sleep(2);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}