#include <Dps368.h>
#include <Adafruit_SHT31.h>

Dps368 pressureSense = Dps368(); //Instantiate DPS368 Pressure sensor
Adafruit_SHT31 rhSense = Adafruit_SHT31(); //Instantiate the SHT31 RH/Temp sensor

const uint8_t dps368_oversampling = 7; //Define the oversampling amount for the DPS368 sensor
unsigned long period = 5000; //Number of ms to wait between sensor readings

void setup() {
	Serial.begin(115200); //Begin serial conunication at high speed 
	// uint8_t error_dps368 = pressureSense.begin(Wire); //Initialize DPS368 sensor
	uint8_t error_dps368 = 0; //DEBUG! FIX! Change library to return stuff properly
	pressureSense.begin(Wire); //Initialize DPS368 sensor //DEBUG! FIX! Change library to return stuff properly
	uint8_t error_sht31 = rhSense.begin(0x44); //Initialize SHT31 sensor
	
	Serial.println("Haar Status:"); //Print resulting sensor status 
	Serial.print("\tDPS368: "); 
	if(error_dps368 == 1) Serial.print("PASS\n"); //Print error grabbed from sensor
	else Serial.print("FAIL!\n"); //Fail if result is not 0
	Serial.print("\tSHT31: ");
	if(error_sht31 == 1) Serial.print("PASS\n"); //Print error grabbed from sensor
	else Serial.print("FAIL!\n"); //Fail if result is 0
}

void loop() {

	float temp_dps368; //Storage for temp measurement from DPS368 
  	float pressure; //Storage for pressure measurment from DPS368
  	

	int16_t error1 = pressureSense.measureTempOnce(temp_dps368, dps368_oversampling); //Grab new temp values [°C]
	int16_t error2 = pressureSense.measurePressureOnce(pressure, dps368_oversampling); //Grab new pressure values [Pa]
	pressure = pressure/100.0f; //Convert from Pa to mBar, because Pa is a stupid unit, and hPa is more stupid. 

	float humidity = rhSense.readHumidity(); //Grab new humidity values [%]
	float temp_sht31 = rhSense.readTemperature(); //Grab new temp values [°C]

	Serial.print("Temp (SHT31): "); Serial.print(temp_sht31, 4); Serial.print(" °C\t"); //Print temp to 4 decimal places
	Serial.print("Temp (DPS368): "); Serial.print(temp_dps368, 2); Serial.print(" °C\t"); //Print temp to 2 decimal places
	Serial.print("Pressure: "); Serial.print(pressure, 2); Serial.print(" mBar\t"); //Print pressure to 2 decimal places
	Serial.print("Humidity: "); Serial.print(humidity, 2); Serial.print(" %\n"); //Print humidity to 2 decimal places
	delay(period); //Wait a specified period before the next sensor reading
}

String printError(uint8_t val) //Print out error result 
{
	if(val != 0) return "FAIL!"; //Return fail in all but 0 case
	else return "PASS"; //Return pass if result == 0
}