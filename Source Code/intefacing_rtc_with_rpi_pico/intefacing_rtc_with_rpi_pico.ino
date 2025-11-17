#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

// SET THESE BASED ON YOUR SCAN
#define DS3231_ADDR 0x68
#define LCD_ADDR    0x27   // change to 0x3F if your backpack is 0x3F

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

void setup() {
  Serial.begin(115200);
  Wire.begin(); // default for Pico (SDA=GP4, SCL=GP5)
  lcd.begin();
  lcd.backlight();
  delay(200);

  if (!rtc.begin()) {
    lcd.clear(); lcd.setCursor(0,0); lcd.print("RTC NOT FOUND");
    while (1);
  }

  if (rtc.lostPower()) {
    // Set to compile time once: uncomment to set time, then re-upload/disable
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Or explicit:
    // rtc.adjust(DateTime(2025, 11, 14, 15, 0, 0));
  }

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("DS3231 -> Pico -> LCD");
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();
  float temp = rtc.getTemperature();

  char line1[21], line2[21], line3[21], line4[21];
  snprintf(line1, 21, "RTC with Pico");
  snprintf(line2, 21, "Date: %04u-%02u-%02u", now.year(), now.month(), now.day());
  snprintf(line3, 21, "Time: %02u:%02u:%02u", now.hour(), now.minute(), now.second());
  snprintf(line4, 21, "Temp: %.2f C", temp);

  lcd.setCursor(0,0); lcd.print(line1);
  lcd.setCursor(0,1); lcd.print(line2);
  lcd.setCursor(0,2); lcd.print(line3);
  lcd.setCursor(0,3); lcd.print(line4);

  delay(1000);
}
