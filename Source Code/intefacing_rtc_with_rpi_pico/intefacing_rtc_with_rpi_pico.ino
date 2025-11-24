#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

// SET THESE BASED ON YOUR SCAN
#define DS3231_ADDR 0x68
#define LCD_ADDR    0x27   // change to 0x3F if needed

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);   // 16x2 LCD

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Pico default: SDA = GP4, SCL = GP5

  lcd.begin();
  lcd.backlight();
  delay(200);

  if (!rtc.begin()) {
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("RTC NOT FOUND");
    while (1);
  }

  if (rtc.lostPower()) {
    // ONE-TIME time setting
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Or manual:
    // rtc.adjust(DateTime(2025, 11, 14, 15, 0, 0));
  }

  lcd.clear();
}

void loop() {

static unsigned long lastSwitch = 0;
static bool showTimeDate = true;

DateTime now = rtc.now();
float temp = rtc.getTemperature();

unsigned long currentMillis = millis();

if (showTimeDate && (currentMillis - lastSwitch >= 5000)) {
    showTimeDate = false;
    lastSwitch = currentMillis;
}
else if (!showTimeDate && (currentMillis - lastSwitch >= 3000)) {
    showTimeDate = true;
    lastSwitch = currentMillis;
}

lcd.clear();

if (showTimeDate) {
    char line1[17], line2[17];
    snprintf(line1, 17, "Time: %02u:%02u:%02u", now.hour(), now.minute(), now.second());
    snprintf(line2, 17, "Date: %02u/%02u/%04u", now.day(), now.month(), now.year());

    lcd.setCursor(0,0); lcd.print(line1);
    lcd.setCursor(0,1); lcd.print(line2);
}
else {
    lcd.setCursor(0,0); lcd.print("Temperature:");
    lcd.setCursor(0,1); lcd.printf("%.2f C", temp);
}

delay(1000);
}

