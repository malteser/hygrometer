// include the library code
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

int tim = 250;  //the value of delay time
float hLast, tLast;


LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
DHT dht(DHTPIN, DHTTYPE);



void setup()
{
  Serial.begin(9600);
  Serial.println("DHTxx/Display");
  lcd.begin(8, 2);  // set up the LCD's number of columns and rows: 
  dht.begin();
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || t < 0.6*tLast) {
    lcd.setCursor(0,0);  
    lcd.print("E");
    return;
  }

  lcd.setCursor(0,0);  
  lcd.print(" ");
  lcd.print(t,1);
  lcd.print("C");
  lcd.print(indicator(t,tLast));
  lcd.setCursor(1,1);  
  lcd.print(h,1);
  lcd.print("%");
  lcd.print(indicator(h,hLast));

  hLast=h;
  tLast=t;
}

String indicator(float current, float last) {
  float min = last*0.995, max = last*1.005;
  if(current < min) {
    return "-"; 
  }
  if(current > max) {
    return "+";
  }
  return "=";
}

