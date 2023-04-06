#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 7 //Correspond to GPIO0 on ESP8266
Adafruit_SSD1306 display(OLED_RESET);

const int PIR = 7;
int PIRState = 7;
 
void setup() 
{
  Serial.begin(9600);
    Wire.begin(8,10);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
 delay(2000);
 
  pinMode(PIR, INPUT);
 
   
}
 
void loop() 
{
  PIRState = digitalRead(PIR);
 
  if (PIRState == HIGH) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(35, 15);
    display.write("INTRUDER!\n");
    display.display();
    
  } 
  else 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(40,15);
    display.write("No motion\n");
    display.display();
  }
  delay(1000);
}
