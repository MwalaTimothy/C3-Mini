#include <SFE_BMP180.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 22 // GPIO22
Adafruit_SSD1306 display(OLED_RESET);

SFE_BMP180 pressure;

#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters

void setup()
{
  Serial.begin(9600);
  Wire.begin(8, 10);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).
  if (pressure.begin())
    display.println("BMP180 init success");
  else
  {
    display.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }

}

void loop()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("Altitude: ");
  display.print(ALTITUDE, 0);
  display.print(" M, ");
  display.display();
  delay(3000); // 3 seconds

  char status;
  double T, P, p0, a;

  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Temperature: ");
      display.print(T, 2);
      display.print(" deg C, ");
      display.display();
      delay(3000); // 3 seconds

      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          display.clearDisplay();
          display.setCursor(50, 0);
          display.print("Pressure: ");
          display.setCursor(50, 8);
          display.print(P, 2);
          display.print(" mb, ");
          display.setCursor(50, 15);
          display.print(P * 0.0295333727, 2);
          display.println(" Hg");
          display.display();
          delay(3000); // 3 seconds
        }
        else
        {
          display.println("Error retrieving pressure measurement");
          display.display();
        }
      }
      else
      {
        display.println("Error starting pressure measurement");
        display.display();
      }
    }
    else
    {
      display.println("Error retrieving temperature measurement");
      display.display();
    }
  }
  else
  {
    display.println("Error starting temperature measurement");
    display.display();
  }

  delay(5000); // Pause for 5 seconds.
  display.clearDisplay();
}
