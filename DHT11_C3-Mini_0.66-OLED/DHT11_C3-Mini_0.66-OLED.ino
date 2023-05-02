#include "DHT.h" //DHT Bibliothek
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_RESET = 7;
Adafruit_SSD1306 display(OLED_RESET);

//Pin an welchem der DHT11 Sensor angeschlossen ist.
//Beim DHT11 Shield ist es der digitale Pin D4.
const int DHTPIN = 6;

//Festlegen welcher Typ von DHT Sensor verwendet wird.
#define DHTTYPE DHT11

//Initialisieren des Sensors mit dem Anschluss und dem Typ
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); //Begin der seriellen Kommunikation mit 9600 Baud.
  Wire.begin(8,10);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay(); 
  dht.begin(); //DHT Kommunikation beginnen.
}

void loop() {
  //Der DHT11 Sensor liefert alle 2 Sekunden einen neuen
  //Wert daher lohnt es sich nicht die loop konstant durchlaufen 
  //zu lassen.
  delay(2000);

  //lesen der Luftfeuchtigkeit
  double luftfeuchtigkeit = dht.readHumidity();
  //lesen der Temperatur in Grad Celsius
  double temperaturC = dht.readTemperature();
  //lesen der Temperatur in Grad Fahrenheit
  //mit dem Boolean Parameter wird "gesteuert" ob
  //die Temperatur in Fahrenheit oder Celsius ausgegeben wird.
  double temperaturF = dht.readTemperature(true);

  //Prüfen ob die Werte erfolgreich gelesen wurden.
  if (isnan(luftfeuchtigkeit) || isnan(temperaturC) || isnan(temperaturF)) {
    Serial.println("Fehler beim lesen von Daten.");
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(32,8);
  display.println("DHT11");

  display.setCursor(32,9);
  display.println("_____");

  display.setCursor(32,17);
  String tempValue = String(temperaturC);
  display.println("T: "+tempValue+"C");

  display.setCursor(32,25);
  String humValue = String(luftfeuchtigkeit);
  display.println("H: "+humValue+"%");

  display.display();
  delay(500);
}
