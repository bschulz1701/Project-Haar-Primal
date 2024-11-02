#include <Dps368.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

const unsigned long period = 1000; //Wait 1 second between logs

// Dps368 Opject
Dps368 Pres1 = Dps368();
Dps368 Pres2 = Dps368();

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_SHT31 RH1 = Adafruit_SHT31();
Adafruit_SHT31 RH2 = Adafruit_SHT31();

void setup()
{
  Serial.begin(115200);
  while (!Serial);


  //Call begin to initialize Dps368PressureSensor
  //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  Pres2.begin(Wire, 0x76);
  //Use the commented line below instead of the one above to use the default I2C address.
  //if you are using the Pressure 3 click Board, you need 0x76
  Pres1.begin(Wire);
  RH1.begin(0x45);
  RH2.begin(0x44);

  Serial.println("Init complete!");

}



void loop()
{
  float temperature1;
  float pressure1;
  float temperature2;
  float pressure2;
  uint8_t oversampling = 7;
  int16_t ret;
  unsigned long readStart = millis();
  //lets the Dps368 perform a Single temperature measurement with the last (or standard) configuration
  //The result will be written to the paramerter temperature
  //ret = Dps368PressureSensor.measureTempOnce(temperature);
  //the commented line below does exactly the same as the one above, but you can also config the precision
  //oversampling can be a value from 0 to 7
  //the Dps 368 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
  //measurements with higher precision take more time, consult datasheet for more information
  ret = Pres1.measureTempOnce(temperature1, oversampling);
  //Pressure measurement behaves like temperature measurement
  //ret = Dps368PressureSensor.measurePressureOnce(pressure);
  ret = Pres1.measurePressureOnce(pressure1, oversampling);
  float t1 = RH1.readTemperature();
  float h1 = RH1.readHumidity();
  float t2 = RH2.readTemperature();
  float h2 = RH2.readHumidity();
  Serial.print(millis()/1000.0);
  Serial.print("\t");
  Serial.print(pressure1/100.0);
  Serial.print("\t");
  Serial.print(temperature1);
  Serial.print("\t");
  Serial.print(h1);
  Serial.print("\t");
  Serial.println(t1);
  Serial.print(pressure2/100.0);
  Serial.print("\t");
  Serial.print(temperature2);
  Serial.print("\t");
  Serial.print(h2);
  Serial.print("\t");
  Serial.println(t2);

  //Wait some time
  while((millis() - readStart) < period);
  // while((millis() % 1000) != 0); //Wait for next even second
}
