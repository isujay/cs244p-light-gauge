#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_GFX.h>

// peripheral constants
#define LED_PIN 2   // built-in LED
#define SERVO_PIN 27
#define PHOTO_RESISTER 25

// LCD constants
#define LCD_CS 15
#define LCD_DC 2
#define LCD_RST 4

// peripheral objects
Adafruit_ST7789 lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
Servo servo;

// state variables
 uint16_t minPhotoResistence;
 uint16_t maxPhotoResistence;

// put function declarations here:
int myFunction(int, int);
void initDataBus();
void initServo();
void hideLogo();


void setup() {
  initDataBus();
  initServo();
  initLcd();
  initLED();
  pinMode(PHOTO_RESISTER, INPUT);
}

void initLED()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // servo.write(50);
  Serial.println("All OK");
  uint16_t photoResistance = analogRead(PHOTO_RESISTER);
  Serial.println(photoResistance);
  showLogo();
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  hideLogo();
  digitalWrite(LED_PIN, LOW);
  sleep(1);
}

void showLogo()
{
  lcd.setCursor(0, 0);
  lcd.setTextColor(5000);
  lcd.setTextSize(3);
  lcd.println("Suj");
  lcd.println("Tech");
  lcd.println("STUDIOS");
  lcd.drawCircle(3, 3, 100, 134);
}

void hideLogo() {
    lcd.fillScreen(ST7735_BLACK);
}

void initServo()
{
  servo.attach(SERVO_PIN);
}

void initDataBus()
{
  Serial.begin(9600);
}

void initLcd()
{
  lcd.init(135, 240);
  lcd.fillScreen(ST77XX_BLACK);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}