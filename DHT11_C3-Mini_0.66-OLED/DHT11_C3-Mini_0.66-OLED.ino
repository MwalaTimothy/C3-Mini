#include "DHT.h" // DHT Library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_RESET = 7;
Adafruit_SSD1306 display(OLED_RESET);

// Pin to which the DHT11 sensor is connected.
// If using the DHT11 Shield, it's digital Pin D4.
const int DHTPIN = 6;

// Specify the type of DHT sensor being used.
#define DHTTYPE DHT11

// Initialize the sensor with the pin and type.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Begin serial communication at 9600 Baud.
  Wire.begin(8, 10);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay(); 
  dht.begin(); // Start DHT communication.
}

void loop() {
  // The DHT11 sensor provides a new reading every 2 seconds,
  // so there's no need to constantly loop in the program.
  delay(2000);

  // Read humidity value.
  double humidity = dht.readHumidity();
  // Read temperature in Celsius.
  double temperatureC = dht.readTemperature();
  // Read temperature in Fahrenheit.
  // The boolean parameter controls whether
  // the temperature is displayed in Fahrenheit or Celsius.
  double temperatureF = dht.readTemperature(true);

  // Check if the values were read successfully.
  if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
    Serial.println("Error reading data.");
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(32, 8);
  display.println("DHT11");

  display.setCursor(32, 9);
  display.println("_____");

  display.setCursor(32, 17);
  String tempValue = String(temperatureC);
  display.println("T: " + tempValue + "C");

  display.setCursor(32, 25);
  String humValue = String(humidity);
  display.println("H: " + humValue + "%");

  display.display();
  delay(500);
}
