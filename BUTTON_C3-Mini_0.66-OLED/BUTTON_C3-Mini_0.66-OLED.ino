
 #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "avdweb_Switch.h"

#define OLED_RESET 7 // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

const byte buttonPin =7;

int i;

Switch button = Switch(buttonPin);  // Switch between a digital pin and GND

void setup() {
  Serial.begin(9600);
  Wire.begin(8,10);
  display.println("Examples using Switch library");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
      
  button.poll();
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(45, 15);
  display.setTextColor(WHITE);
 
  if (button.switched()) {
     display.setTextSize(1);
    display.setCursor(45, 13);
    display.print("switched");
    display.display();
  }

  if (button.pushed()) {
    display.setTextSize(1);
    display.setCursor(45, 21);
    display.print("pushed ");
    display.print(++i);
    display.print(" ");
    display.display();
  }

  if (button.longPress()) {
     display.setTextSize(1);
    display.setCursor(45, 15);
    display.print("longPress ");
    display.display();
  }

  if (button.doubleClick()) {
    display.setTextSize(1);
    display.setCursor(45, 10);
    display.print("doubleClick ");
    display.display();
  }

  if (button.released()) {
    display.setTextSize(1);
    display.setCursor(45, 21);
    display.print("released");
    display.display();
  }
    
}
