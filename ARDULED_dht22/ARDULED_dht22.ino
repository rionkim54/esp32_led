#include "kproject_gfx.h"
#include "DHT.h"
 
#define DHTPIN 4     // what digital pin we're connected to
 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#include <SoftwareSerial.h>
SoftwareSerial soft(2,3);

kproject_gfx kproject(soft, 64, 32);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  soft.begin(9600);

  dht.begin();

  kproject.begin();

  kproject.fillScreen(KPROJECT_BLACK);
  
  // delay(0);
  //kproject.fillScreen(KPROJECT_BLACK);
  kproject.setCursor(0, 0);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("제로윈텍");
  kproject.refresh();

}

int i = 0; 

uint16_t Color333(uint8_t r, uint8_t g, uint8_t b) {
  // RRRrrGGGgggBBBbb
  return ((r & 0x7) << 13) | ((r & 0x6) << 10) | ((g & 0x7) << 8) |
         ((g & 0x7) << 5) | ((b & 0x7) << 2) | ((b & 0x6) >> 1);
}


int timeout = 0;

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  
  char temp[16] = { 0x00, };
  
  kproject.fillScreen(KPROJECT_BLACK);

  timeout += 1;

  kproject.setCursor(0, 0);
  kproject.setTextColor(KPROJECT_RED, KPROJECT_BLACK);
  kproject.print_string("온도");

  kproject.setCursor(32, 0);
  kproject.setTextColor(KPROJECT_YELLOW, KPROJECT_BLACK);
  sprintf(temp, "%d'C", (int)t);
  kproject.print_string(temp);
  
  kproject.setCursor(0, 16);
  kproject.setTextColor(KPROJECT_BLUE, KPROJECT_BLACK);
  kproject.print_string("습도"); // "11:11:11");

  kproject.setCursor(32, 16);
  kproject.setTextColor(KPROJECT_WHITE, KPROJECT_BLACK);
  sprintf(temp, "%d%%", (int)h);
  kproject.print_string(temp);

  kproject.refresh();
  
  delay(1000);

}
