#include <Dps368.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

const uint8_t TX = 1;
const uint8_t RX = 0;
const uint8_t FOut = 12;
const uint8_t Dir = 11;

#define MARKING_PERIOD 9 //>8.33ms for standard marking period
const unsigned long TimeoutStandard = 380; //Standard timeout period for most commands is 380ms 

char ReadArray[25] = {0};

const unsigned long period = 1000; //Wait 1 second between logs

// Dps368 Opject
Dps368 Pres1 = Dps368();
Dps368 Pres2 = Dps368();

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_SHT31 RH1 = Adafruit_SHT31();
Adafruit_SHT31 RH2 = Adafruit_SHT31();

void setup() {
	pinMode(TX, OUTPUT);
	pinMode(FOut, OUTPUT);
	pinMode(Dir, OUTPUT);

	digitalWrite(Dir, HIGH); //Set to transmit 
	Serial1.begin(1200, SERIAL_7E1);
	Serial.begin(115200);
	while(!Serial) { //Wait until serial interface is available 
		;
	} 
	Serial.println("HygroVue10");
	Serial.println("Time[s]\tTemp[°C]\tRH[%]\tPres1[mBar]\tTemp1A[°C]\tTemp1B[°C]\tRH1[%]\tPres2[mBar]\tTemp2A[°C]\tTemp2B[°C]\tRH2[%]");

	Pres2.begin(Wire, 0x76);
	//Use the commented line below instead of the one above to use the default I2C address.
	//if you are using the Pressure 3 click Board, you need 0x76
	Pres1.begin(Wire);
	RH1.begin(0x45);
	RH2.begin(0x44);

	// unsigned long startTime = millis();
	
}

void loop() {

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

	ret = Pres2.measureTempOnce(temperature2, oversampling);
	//Pressure measurement behaves like temperature measurement
	//ret = Dps368PressureSensor.measurePressureOnce(pressure);
	ret = Pres2.measurePressureOnce(pressure2, oversampling);
	float t1 = RH1.readTemperature();
	float h1 = RH1.readHumidity();
	float t2 = RH2.readTemperature();
	float h2 = RH2.readHumidity();
	

	SendCommand("0M!");
	delay(100);
	String data = SendCommand("0D0!");
	data = data.substring(1, data.length()); //Trim address val
	// Serial.println(data); //DEBUG!
	float temp, rh;
	// Serial.println(data.substring(0, NextIndexOfSep(data)));
	temp = DataToFloat(data.substring(0, NextIndexOfSep(data))); //Grab first float from data
	data = data.substring(NextIndexOfSep(data) + 1, data.length()); //Trim first chunk off of data
	// Serial.println(data.substring(0, NextIndexOfSep(data)));
	rh = DataToFloat(data.substring(0, NextIndexOfSep(data))); //Grab other float from data
	static unsigned long printTime = millis();
	if(floor(millis()/1000.0) != millis()/1000.0) { //If data out of sync, perform sync
		while(floor(millis()/1000.0) != millis()/1000.0); //Wait for seconds to match
	}
	while((millis() - printTime) < 1000.0); //Wait until time is up
	printTime = millis();
	Serial.print(millis()/1000.0);
	Serial.print('\t');
	Serial.print(temp);
	Serial.print('\t');
	Serial.print(rh);
	Serial.print("\t");

	Serial.print(pressure1/100.0);
	Serial.print("\t");
	Serial.print(temperature1);
	Serial.print("\t");
	Serial.print(t1);
	Serial.print("\t");
	Serial.print(h1);
	Serial.print("\t");

	Serial.print(pressure2/100.0);
	Serial.print("\t");
	Serial.print(temperature2);
	Serial.print("\t");
	Serial.print(t2);
	Serial.print("\t");
	Serial.println(h2);
}

uint8_t IndexOfSep(String val) //Find the first index of the value seperator 
{
	uint8_t pos = val.indexOf('+');
	uint8_t neg = val.indexOf('-');
	if(pos == -1 || neg == -1) return max(pos, neg); //If one of them is not found, return the other one
	else return min(pos, neg); //If both are valid, then return the first

}

uint8_t NextIndexOfSep(String val) //Find the NEXT index of the value seperator 
{
	uint8_t pos = val.indexOf('+');
	uint8_t neg = val.indexOf('-');
	if(pos == -1 || neg == -1) return max(pos, neg); //If one of them is not found, return the other one
	else if (pos == 0 || neg == 0) return IndexOfSep(val.substring(1, val.length())); //If the first value is a seperator, call normal IndexOfSep, but give is 1:n as an inpus
	else return max(pos, neg); //If both are valid, AND the first element is not a seperator, then return the LATER one
}

float DataToFloat(String val)
{
	char sign = val.charAt(0); //Grab first char to test for signage
	val = val.substring(1, val.length()); //Trim sign char
	float data = val.toFloat();
	data = (sign == '+') ? data : -1.0*data; //Adjust sign of data if needed
	return data;
}

char GetAddress()
{
	SendBreak(); //Send break to start message
	Mark(MARKING_PERIOD); //Mark for standard period before command
	Serial1.begin(1200, SERIAL_7E1);
	Serial1.print("0I!");
	Serial1.flush(); //Make sure data is transmitted before releasing the bus
	delay(1);
	ReleaseBus(); //Switch bus to recieve 
	// char Var = Serial.re

	unsigned long LocalTime = millis();
	// bool GotData = false;
	while(Serial1.available() < 3 && (millis() - LocalTime) <  TimeoutStandard);
	String Val = Serial1.readStringUntil('\r');
	Serial.println(Val);
	return 0; //DEBUG!
}

void SendBreak()
{
	pinMode(Dir, OUTPUT); //Make sure direction is set to output
	pinMode(FOut, OUTPUT); //Make sure the force out pin is in output mode
	digitalWrite(Dir, HIGH); //Set direction to output
	digitalWrite(FOut, LOW); //Set low to force output high
	delay(13); //Wait for bus to acnowledge action
	digitalWrite(FOut, HIGH); //Stop forcing output
}

void Mark(unsigned long Period)
{
	pinMode(Dir, OUTPUT); //Make sure direction control pin is set as an output
	pinMode(TX, OUTPUT); //Make sure transmit pin is set as output
	digitalWrite(Dir, HIGH); //Set direction to output
	digitalWrite(TX, 1); //Begin marking condition
	delay(Period); //Wait for a given marking period
	digitalWrite(TX, 0); //Stop marking  
}

void Space(unsigned long Period)
{
	pinMode(Dir, OUTPUT); //Make sure direction control pin is set as an output
	pinMode(TX, OUTPUT); //Make sure transmit pin is set as output
	digitalWrite(Dir, HIGH); //Set direction to output
	digitalWrite(TX, 0); //Begin spacing condition
	delay(Period); //Wait for a given marking period
	digitalWrite(TX, 1); //Stop spacing
}

// void SendCommand()

void ReleaseBus() 
{
	pinMode(Dir, OUTPUT); //Make sure direction pin is set as an output
	digitalWrite(Dir, LOW); //Set direction to input
}

String SendCommand(String Command) 
{
	SendBreak(); //Send break to start message
	Mark(MARKING_PERIOD); //Mark for standard period before command
	Serial1.begin(1200, SERIAL_7E1);
	Serial1.print(Command);
	Serial1.flush(); //Make sure data is transmitted before releasing the bus
	delay(1);
	ReleaseBus(); //Switch bus to recieve 
	// char Var = Serial.re

	unsigned long LocalTime = millis();
	char Data[100] = {0}; //Make data array for storage FIX! Change length to not be arbitrary
	bool GotData = false; //Used to keep track of terminating character has been recieved 
	int Pos = 0; //Keep track of position in data array
	while(!GotData && (millis() - LocalTime) <  TimeoutStandard) {
		if(Serial1.available() > 0) {
			Data[Pos] = Serial1.read(); //If byte is available, read it in
			Pos++; //Increment position
		}
		if(Data[Pos] == '\n') GotData = true; //Set flag if end character is read in
	}
	String Val = String(Data); //Convert to String
	Val.trim(); //Get rid of any trailing characters 
	// while(Serial1.available() < 3 && (millis() - LocalTime) <  TimeoutStandard);
	// String Val = Serial1.readStringUntil('\r');
	// Serial.println(Val);
	return Val; 
}