/*
  SFE_BMP085 pressure sensor library for Arduino
	
  Mike Grusin
  http://www.sparkfun.com
	
  Uses floating-point equations from the Weather Station Data Logger project
  http://wmrx00.sourceforge.net/
  http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf

  version 1.2 2012/01/23 update for compatiblity with Arduino 1.0
	
  Example Code:

  #include <SFE_BMP085.h>
  #include <Wire.h>

  SFE_BMP085 pressure(BMP_ADDR);

  char status;
  double T,P,p0,a;

  Serial.begin(9600);
  Serial.println("REBOOT");

  // initialize the sensor (important to get calibration values stored on the device)
  if (pressure.begin())
  {
    Serial.println("BMP085 init success");
    while(1)
    {
      // tell the sensor to start a temperature measurement
      // if request is successful, the number of ms to wait is returned
      // if request is unsuccessful, 0 is returned
      status = pressure.startTemperature();
      if (status != 0)
      {
	// wait for the measurement to complete
	delay(status);
	// retrieve the measurement
	// note that the measurement is stored in the variable T
	// use '&T' to provide the address of T to the function
	// function returns 1 if successful, 0 if failure
	status = pressure.getTemperature(&T);
	if (status != 0)
	{
          // print out the measurement
          Serial.print("temp: ");
          Serial.print(T,2);
          Serial.println(" deg C");

          // tell the sensor to start a pressure measurement
          // the parameter is the oversampling setting, from 0 to 3 (highest res, longest wait)
          // if request is successful, the number of ms to wait is returned
          // if request is unsuccessful, 0 is returned
          status = pressure.startPressure(3);
          if (status != 0)
          {
            // wait for the measurement to complete
            delay(status);
            // retrieve the measurement
            // note that the measurement is stored in the variable P
            // use '&P' to provide the address of P
            // note also that the function requires the previous temperature measurement (T)
            // (if temperature is stable, you can do one temperature measurement for a number of pressure measurements)
            // function returns 1 if successful, 0 if failure
            status = pressure.getPressure(&P,&T);
            if (status != 0)
            {
              // print out the measurement
              Serial.print("pressure: ");
              Serial.print(P,2);
              Serial.println(" mb");

              // the pressure sensor returns abolute pressure, which varies with altitude
              // to remove the effects of altitude, use the sealevel function and your current altitude
              // this number is commonly use in published weather data
              p0 = pressure.sealevel(P,1655.0); // we're at 1655 meters (Boulder, CO)
              Serial.print("sea-level pressure: ");
              Serial.print(p0,2);
              Serial.println(" mb");

              // on the other hand, if you want to determine your altitude from the pressure reading,
              // use the altitude function along with a baseline pressure (sea-level or other)
              a = pressure.altitude(P,p0);
              Serial.print("altitude above sea-level: ");
              Serial.print(a,0);
              Serial.println(" meters");
            }
            else Serial.println("error retrieving pressure measurement\n");
          }
          else Serial.println("error starting pressure measurement\n");
        }
        else Serial.println("error retrieving temperature measurement\n");
      }
      else Serial.println("error starting temperature measurement\n");

      delay(10000);
    }
  }
  else Serial.println("BMP085 init fail\n\n");

*/

#ifndef SFE_BMP085_h
#define SFE_BMP085_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SFE_BMP085
{
	public:
		SFE_BMP085(char i2c_address);

		char begin();
			// call pressure.begin() to initialize BMP085 before use
			// returns 1 if success, 0 if failure (bad component or I2C bus shorted?)
		
		char startTemperature(void);
			// command BMP085 to start a temperature measurement
			// returns n (number of ms to wait) for success, 0 for fail

		char getTemperature(double *T);
			// return temperature measurement from previous startTemperature command
			// places returned value in T variable (deg C)
			// returns 1 for success, 0 for fail

		char startPressure(char oversampling);
			// command BMP085 to start a pressure measurement
			// oversampling: 0 - 3 for oversampling value
			// returns n (number of ms to wait) for success, 0 for fail

		char getPressure(double *P, double *T);
			// return absolute pressure measurement from previous startPressure command
			// note: requires previous temperature measurement in variable T
			// places returned value in P variable (mbar)
			// returns 1 for success, 0 for fail

		double sealevel(double P, double A);
			// convert absolute pressure to sea-level pressure (as used in weather data)
			// P: absolute pressure (mbar)
			// A: current altitude (meters)
			// returns sealevel pressure in mbar

		double altitude(double P, double P0);
			// convert absolute pressure to altitude (given baseline pressure; sea-level, runway, etc.)
			// P: absolute pressure (mbar)
			// P0: fixed baseline pressure (mbar)
			// returns signed altitude in meters

	private:
	
		char readInt(char address, int *value);
			// read an signed int (16 bits) from a BMP085 register
			// address: BMP085 register address
			// *value: pointer to signed int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with read value(s) in *value

		char readUInt(char address, unsigned int *value);
			// read an unsigned int (16 bits) from a BMP085 register
			// address: BMP085 register address
			// *value: pointer to unsigned int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with read value(s) in *value

		char readBytes(unsigned char *values, char length);
			// read a number of bytes from a BMP085 register
			// values: array of char with register address in first location [0]
			// length: number of bytes to read back
			// returns 1 for success, 0 for fail, with read bytes in values[] array
			
		char writeBytes(unsigned char *values, char length);
			// write a number of bytes to a BMP085 register (and consecutive subsequent registers)
			// values: array of char with register address in first location [0]
			// length: number of bytes to write
			// returns 1 for success, 0 for fail
			
		char _i2c_address;
		int AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
		unsigned int AC4,AC5,AC6; 
		double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
};

#define BMP_ADDR 0x77 // 7-bit address

#define	BMP085_CONTROL_REG 0xF4
#define	BMP085_RESULT_REG 0xF6

#define	BMP085_COMMAND_TEMPERATURE 0x2E
#define	BMP085_COMMAND_PRESSURE0 0x34
#define	BMP085_COMMAND_PRESSURE1 0x74
#define	BMP085_COMMAND_PRESSURE2 0xB4
#define	BMP085_COMMAND_PRESSURE3 0xF4

#endif
