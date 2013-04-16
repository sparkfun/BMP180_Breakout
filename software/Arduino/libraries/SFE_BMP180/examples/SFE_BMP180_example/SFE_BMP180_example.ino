#include <SFE_BMP085.h>
#include <Wire.h>

SFE_BMP085 pressure(BMP_ADDR);

void setup()
{
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
}

void loop()
  // put your main code here, to run repeatedly: 
{
}
