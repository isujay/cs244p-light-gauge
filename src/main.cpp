#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_GFX.h>

// peripheral constants
#define LED_PIN 13   
#define SERVO_PIN 27
#define PHOTO_RESISTER 25
#define MIN_SERVO_ROTATION 0
#define MAX_SERVO_ROTATION 180

// LCD constants
#define LCD_CS 15
#define LCD_DC 2
#define LCD_RST 4

// peripheral objects
Adafruit_ST7789 lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
Servo servo;

// state variables
 uint16_t minPhotoResistenc = std::numeric_limits<uint16_t>::max();
 uint16_t maxPhotoResistence = std::numeric_limits<uint16_t>::min();

// put function declarations here:
int myFunction(int, int);
void initDataBus();
void initServo();
void hideLogo();
void calibratePhotoResister();

void setup() {
  initDataBus();
  initServo();
  initLcd();
  initLED();
  calibratePhotoResister();
}

void calibratePhotoResister() {
  Serial.println("Attention! Calibration started. Go, go, go!");
  pinMode(PHOTO_RESISTER, INPUT);
  int startTime = millis();
  int endTime = startTime + 10000;
  for (int time = millis(); time < endTime; time = millis()) {
    Serial.println("Calibrating...");
    uint16_t photoResistance = analogRead(PHOTO_RESISTER);
    if (photoResistance > maxPhotoResistence) {
      maxPhotoResistence = photoResistance;
    }
    if (photoResistance < minPhotoResistenc) {
      minPhotoResistenc = photoResistance;
    }
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  }
  Serial.printf("Photo Resistor calibration complete. Min photoResistance=%d, Max photoResistence=%d\n", minPhotoResistenc, maxPhotoResistence);
  digitalWrite(LED_PIN, HIGH);
}

void initLED()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  uint16_t photoResistance = analogRead(PHOTO_RESISTER);
  Serial.printf("Photo resistance = %d\n", photoResistance);
  float photoResistancePercentage = ((float)(photoResistance - minPhotoResistenc)) / (maxPhotoResistence - minPhotoResistenc);
  int servoPosition = (photoResistancePercentage * (MAX_SERVO_ROTATION - MIN_SERVO_ROTATION)) + MIN_SERVO_ROTATION;
  Serial.printf("Servo rotation = %d\n", servoPosition);
  servo.write(servoPosition);

  showLogo();
  delay(1000);
  hideLogo();
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