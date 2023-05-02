#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LOLIN_HP303B.h>

LOLIN_HP303B HP303B;

// OLED display setup
#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  // I2C setup
  Wire.begin(8, 10);
  // OLED display setup
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  // HP303B sensor setup
  HP303B.begin(); // I2C address = 0x77
  // HP303B.begin(0x76); //I2C address = 0x76
}

void loop() {
  // Clear the display buffer.
  display.clearDisplay();
  display.setCursor(0, 0);

  int32_t temperature;
  int32_t pressure;
  int16_t oversampling = 7;
  int16_t ret;

  // Measure temperature
  ret = HP303B.measureTempOnce(temperature, oversampling);
  if (ret != 0) {
    display.setTextSize(1);
    display.println("T: error");
  } else {
    display.setCursor(35,10);
    display.setTextSize(1);
    display.println("Temperature:");
    display.setCursor(40,21);
    display.setTextSize(1);
    display.println(temperature);
    display.display();
    delay(3000);
  }

  // Measure pressure
  ret = HP303B.measurePressureOnce(pressure, oversampling);
  if (ret != 0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.println("P: error");
  } else {
    display.clearDisplay();
    display.setCursor(35,10);
    display.setTextSize(1);
    display.println("Pressure:");
    display.setCursor(40,21);
    display.setTextSize(1);
    display.println(pressure);
    display.display();
  }

  // Delay before looping again
  delay(3000);
}
