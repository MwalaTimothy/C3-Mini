#include <stdio.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BH1750.h>

#define OLED_RESET 7  // GPIO22
Adafruit_SSD1306 display(OLED_RESET);

BH1750 light(0x23);

void setup() {

  Serial.begin(115200);
   Wire.begin(8, 10);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

void loop() {


  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(40, 10);
  display.setTextColor(WHITE);

  if (light.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    display.println("Light: ");
    display.setTextSize(1);
    display.setCursor(40, 21);
    display.print(light.readLightLevel());

  }
  else
  {
    display.println("Error!");
  }
  display.display();
  delay(1000);

}
