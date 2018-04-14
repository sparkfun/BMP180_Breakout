/*
	SFE_BMP180.h
	---
	Bosch BMP180 pressure sensor library for the Teensy microcontroller.
	unalfaruk.com / A.Faruk UNAL / ahmet@unalfaruk.com || unalfaruk@outlook.com
	This library depends on SparkFUN BMP180 library and https://roboticboat.uk/Teensy/Teensy36/BMP180.html page.

	---
*/

#ifndef Teensy_BMP180_h
#define Teensy_BMP180_h
#include "Wire.h"
class Teensy_BMP180
{
	public:

		Teensy_BMP180(TwoWire *hwWire){
			WireSelected=hwWire;
		} // base type

		void begin();
			// call pressure.begin() to initialize BMP180 before use
			// returns 1 if success, 0 if failure (bad component or I2C bus shorted?)

		char startTemperature(void);
			// command BMP180 to start a temperature measurement
			// returns (number of ms to wait) for success, 0 for fail

		char getTemperature(double &T);
			// return temperature measurement from previous startTemperature command
			// places returned value in T variable (deg C)
			// returns 1 for success, 0 for fail

		char startPressure(void);
			// command BMP180 to start a pressure measurement
			// oversampling: 0 - 3 for oversampling value
			// returns (number of ms to wait) for success, 0 for fail

		char getPressure(double &P, double &T);
			// return absolute pressure measurement from previous startPressure command
			// note: requires previous temperature measurement in variable T
			// places returned value in P variable (mbar)
			// returns 1 for success, 0 for fail

		double altitude(double P, double P0);
			// convert absolute pressure to altitude (given baseline pressure; sea-level, runway, etc.)
			// P: absolute pressure (mbar)
			// P0: fixed baseline pressure (mbar)
			// returns signed altitude in meters



	private:

		char readInt(char address, int16_t &value);
			// read an signed int (16 bits) from a BMP180 register
			// address: BMP180 register address
			// value: external signed int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with result in value

		char readUInt(char address, uint16_t &value);
			// read an unsigned int (16 bits) from a BMP180 register
			// address: BMP180 register address
			// value: external unsigned int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with result in value


		int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
		uint16_t AC4,AC5,AC6;

		double c5,c6,mc,md;
		double xx0,xx1,xx2;
		double yy0,yy1,yy2;
		double p0,p1,p2;

		TwoWire *WireSelected;
};

//Address of the BMP180 address
#define _i2cAddress 0x77

//Registers
#define _Register_CONTROL 0xF4
#define _Register_RESULT 0xF6

//Commands
#define _COMMAND_TEMPERATURE 0x2E
#define _COMMAND_PRESSURE 0xF4

#define _ONE_BYTE 1
#define _TWO_BYTES 2
#define _THREE_BYTES 3

#endif
