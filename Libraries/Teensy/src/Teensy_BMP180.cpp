/*
	SFE_BMP180.cpp
	---
	Bosch BMP180 pressure sensor library for the Teensy microcontroller.
	unalfaruk.com / A.Faruk UNAL / ahmet@unalfaruk.com || unalfaruk@outlook.com
	This library depends on SparkFUN BMP180 library and https://roboticboat.uk/Teensy/Teensy36/BMP180.html page.

	---
*/
#include <Teensy_BMP180.h>
#include <stdio.h>
#include <Wire.h>
#include <math.h>


void Teensy_BMP180::begin()
// Initialize library for subsequent pressure measurements
{
	//Initialise the pressure library
	double c3,c4,b1;

	//Start the wire library
	WireSelected->begin();

	//Read the BMP180 factory settings
	if (readInt(0xAA,AC1) &&
	readInt(0xAC,AC2) &&
	readInt(0xAE,AC3) &&
	readUInt(0xB0,AC4) &&
	readUInt(0xB2,AC5) &&
	readUInt(0xB4,AC6) &&
	readInt(0xB6,VB1) &&
	readInt(0xB8,VB2) &&
	readInt(0xBA,MB) &&
	readInt(0xBC,MC) &&
	readInt(0xBE,MD))
	{
	// Calculate calibration polynomials

	c3 = 160.0 * pow(2,-15) * AC3;
	c4 = pow(10,-3) * pow(2,-15) * AC4;
	b1 = pow(160,2) * pow(2,-30) * VB1;
	c5 = (pow(2,-15) / 160) * AC5;
	c6 = AC6;

	mc = (pow(2,11) / pow(160,2)) * MC;
	md = MD / 160.0;

	xx0 = AC1;
	xx1 = 160.0 * pow(2,-13) * AC2;
	xx2 = pow(160,2) * pow(2,-25) * VB2;

	yy0 = c4 * pow(2,15);
	yy1 = c4 * c3;
	yy2 = c4 * b1;

	p0 = (3791.0 - 8.0) / 1600.0;
	p1 = 1.0 - 7357.0 * pow(2,-20);
	p2 = 3038.0 * 100.0 * pow(2,-36);

	}
}


char Teensy_BMP180::readInt(char registerAddress, int16_t &value)
// Read a signed integer (two bytes) from device
// address: register to start reading (plus subsequent register)
// value: external variable to store data (function modifies value)
{
	// Read a signed integer from device

	unsigned char byteHigh;
	unsigned char byteLow;

	// Begin communication with BMP180
	WireSelected->beginTransmission(_i2cAddress);

	// Tell register you want some data
	WireSelected->write(registerAddress);

	//If false, endTransmission() sends a restart message after transmission. The bus will not be released,
	//which prevents another master device from transmitting between messages. This allows one master device
	//to send multiple transmissions while in control. The default value is true.
	int nackCatcher = WireSelected->endTransmission(false);

	// Return if we have a connection problem
	if (nackCatcher != 0) {return 0;}

	// Request 2 bytes from BMP180
	WireSelected->requestFrom(_i2cAddress , _TWO_BYTES);

	// Wait for the bytes to arrive
	while(WireSelected->available() < _TWO_BYTES);

	// Read the values
	byteHigh = WireSelected->read();
	byteLow = WireSelected->read();

	value = (((int16_t)byteHigh <<8) + (int16_t)byteLow);

	// Return true as ok
	return(1);
}


char Teensy_BMP180::readUInt(char registerAddress, uint16_t &value)
// Read an unsigned integer (two bytes) from device
// address: register to start reading (plus subsequent register)
// value: external variable to store data (function modifies value)
{
	// Read an unsigned integer from device

	unsigned char byteHigh;
	unsigned char byteLow;

	// Begin communication with BMP180
	WireSelected->beginTransmission(_i2cAddress);

	// Tell register you want some data
	WireSelected->write(registerAddress);

	//If false, endTransmission() sends a restart message after transmission. The bus will not be released,
	//which prevents another master device from transmitting between messages. This allows one master device
	//to send multiple transmissions while in control. The default value is true.
	int nackCatcher = WireSelected->endTransmission(false);

	// Return if we have a connection problem
	if (nackCatcher != 0) {return 0;}

	// Request 2 bytes from BMP180
	WireSelected->requestFrom(_i2cAddress , _TWO_BYTES);

	// Wait for the bytes to arrive
	while(WireSelected->available() < _TWO_BYTES);

	// Read the values
	byteHigh = WireSelected->read();
	byteLow = WireSelected->read();

	value = (((uint16_t)byteHigh <<8) + (uint16_t)byteLow);

	// Return true as ok
	return(1);
}




char Teensy_BMP180::startTemperature(void)
// Begin a temperature reading.
// Will return delay in ms to wait, or 0 if I2C error
{
	// Begin communication with BMP180
	WireSelected->beginTransmission(_i2cAddress);

	// Tell register an instruction
	WireSelected->write(_Register_CONTROL);
	WireSelected->write(_COMMAND_TEMPERATURE);

	//End transmission and release the bus. The default value is true.
	int nackCatcher = WireSelected->endTransmission();

	// Return if we have a connection problem
	if (nackCatcher != 0) {return 0;}

	// Return true as ok
	return(1);

}


char Teensy_BMP180::getTemperature(double &T)
// Retrieve a previously-started temperature reading.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startTemperature() to have been called prior and sufficient time elapsed.
// T: external variable to hold result.
// Returns 1 if successful, 0 if I2C error.
{
	unsigned char byteHigh;
	unsigned char byteLow;
	double tu, a;

	// Wait for the measurement to complete:
	delay(5);

	// Begin communication with BMP180
	WireSelected->beginTransmission(_i2cAddress);

	// Tell register you want some data
	WireSelected->write(_Register_RESULT);

	//If false, endTransmission() sends a restart message after transmission. The bus will not be released,
	//which prevents another master device from transmitting between messages. This allows one master device
	//to send multiple transmissions while in control. The default value is true.
	int nackCatcher = WireSelected->endTransmission(false);

	// Return if we have a connection problem
	if (nackCatcher != 0) {return 0;}

	// Request 2 bytes from BMP180
	WireSelected->requestFrom(_i2cAddress , _TWO_BYTES);

	// Wait for the bytes to arrive
	while(WireSelected->available() < _TWO_BYTES);

	// Read the values
	byteHigh = WireSelected->read();
	byteLow = WireSelected->read();

	// Calculate the temperature
	tu = (byteHigh << 8) + byteLow;
	a = c5 * (tu - c6);
	T = a + (mc / (a + md));

	// Return true as ok
	return(1);
}


//char Teensy_BMP180::startPressure(char oversampling)
char Teensy_BMP180::startPressure(void)

// Begin a pressure reading.
// Oversampling: 0 to 3, higher numbers are slower, higher-res outputs.
// Will return delay in ms to wait, or 0 if I2C error.
{
	// Begin a pressure reading.
	WireSelected->beginTransmission(_i2cAddress);

	// Tell register an instruction
	WireSelected->write(_Register_CONTROL);
	WireSelected->write(_COMMAND_PRESSURE);

	//End transmission and release the bus. The default value is true.
	int nackCatcher = WireSelected->endTransmission();

	// Return if we have a connection problem
	if (nackCatcher != 0) {return 0;}

	// Return true as ok
	return(1);
}


char Teensy_BMP180::getPressure(double &P, double &T)
// Retrieve a previously started pressure reading, calculate abolute pressure in mbars.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startPressure() to have been called prior and sufficient time elapsed.
// Requires recent temperature reading to accurately calculate pressure.

// P: external variable to hold pressure.
// T: previously-calculated temperature.
// Returns 1 for success, 0 for I2C error.

// Note that calculated pressure value is absolute mbars, to compensate for altitude call sealevel().
{
	unsigned char byteHigh;
	unsigned char byteMid;
	unsigned char byteLow;
	double pu,s,x,y,z;

	// Wait for the measurement to complete:
		delay(26);

	// Begin communication with BMP180
	WireSelected->beginTransmission(_i2cAddress);

	// Tell register you want some data
	WireSelected->write(_Register_RESULT);

	//If false, endTransmission() sends a restart message after transmission. The bus will not be released,
	//which prevents another master device from transmitting between messages. This allows one master device
	//to send multiple transmissions while in control. The default value is true.
	int nackCatcher = WireSelected->endTransmission();

	// Return if we have a connection problem
	if (nackCatcher != 0) {return 0;}

	// Request 3 bytes from BMP180
	WireSelected->requestFrom(_i2cAddress , _THREE_BYTES);

	// Wait for the bytes to arrive
	while(WireSelected->available() < _THREE_BYTES);

	// Read the values
	byteHigh = WireSelected->read();
	byteMid = WireSelected->read();
	byteLow = WireSelected->read();

	// Calculate absolute pressure in mbars.
	pu = (byteHigh * 256.0) + byteMid + (byteLow/256.0);

	s = T - 25.0;
	x = (xx2 * pow(s,2)) + (xx1 * s) + xx0;
	y = (yy2 * pow(s,2)) + (yy1 * s) + yy0;
	z = (pu - x) / y;
	P = (p2 * pow(z,2)) + (p1 * z) + p0;

	return(1);
}

double Teensy_BMP180::altitude(double P, double P0)
// Given a pressure measurement P (mb) and the pressure at a baseline P0 (mb),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}
